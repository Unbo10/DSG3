#include <iostream>

class Node {
    public:
        int data;
        Node* next;

        Node(int value);

        friend std::ostream& operator<<(std::ostream& os, const Node& node);

        ~Node();
};

Node::Node(int value): data(value), next(nullptr) {} //* That syntax initializes data and next with the values specified inside the parenthesis.

std::ostream& operator<<(std::ostream& os, const Node& node) {
    os << "Node data: " << node.data;
    if (node.next != nullptr) {
        os << ", Next node at: " << node.next;
    } else {
        os << ", Next node: nullptr";
    }
    os << "\n";
    return os;
};

Node::~Node() {
    next = nullptr;
}

class LinkedList {
    public:
        Node* head;
        int size;

        LinkedList();

        virtual void insert_at_end(int data);

        void print();
        
        virtual ~LinkedList();
};

LinkedList::LinkedList(): head(nullptr), size(0) {}

void LinkedList::insert_at_end(int data) {
    if (head == nullptr) {
        head = new Node(data); //* Since the constructor of LinkedList
    }
    else {
        Node* newNode = new Node(data);
        Node* current = head;
        int i = 0;
        while (current->next != nullptr) {
            current = current->next;
            i++;
        }
        current->next = newNode; //*Newnode will become the new tail.
    }
    size++;
}

void LinkedList::print () {
    std::cout << "[";
    if (size != 0) {
        std::cout << head->data;
        Node* current = head->next;
        while (current != nullptr) {
            std::cout << ", " << current->data;
            current = current->next;
        }
    }
    std::cout << "]\n";
}

LinkedList::~LinkedList() {
    Node* current = head;
    Node* temp = nullptr;
    while (current != nullptr) {
        temp = current;
        current = current->next;
        delete temp;
    }
}

class ModifiedLL: public LinkedList {
    public:
        Node* tail;
        void insert_at_end(int data) {
            if (head == nullptr) {
                head = new Node(data);
                tail = head;
            }
            else {
                Node* newNode = new Node(data);
                tail->next = newNode; //* Point the old tail to the new node
                tail = newNode; //* Update the tail to be the new node
            }
            size++;
        }
};

using namespace std;

int main() {
    int n = 0, temp = 0;
    cin >> n;
    ModifiedLL arr, gis;
    for (int i = 0; i < n; i++) {
        cin >> temp;
        arr.insert_at_end(temp);
    }
    gis.insert_at_end(arr.head->data);
    Node* currentNode = arr.head;
    Node* nextBiggerNode = currentNode;
    while (currentNode != nullptr){
        nextBiggerNode = currentNode->next;
        while (nextBiggerNode != nullptr && nextBiggerNode->data <= currentNode->data) { //* WOn't be equal, but helps understanding
            // cout << currentNode->data << " Vs. " << nextBiggerNode->data << " " << bigger_id_found << " " << j << ", ";
            nextBiggerNode = nextBiggerNode->next;
        }
        if (nextBiggerNode != nullptr) {
            gis.insert_at_end(nextBiggerNode->data);
        }
        currentNode = nextBiggerNode;
    }
    cout << gis.size << "\n";
    int i = 0;
    currentNode = gis.head;
    while (i < gis.size) {
        cout << currentNode->data;
        currentNode = currentNode->next;
        if (i < gis.size - 1) {
            cout << " "; //* To avoid leaving a space at the end.
        }
        i++;
    }
    return 0;
}