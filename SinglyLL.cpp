#include <iostream>

using namespace std;

#include <iostream>

class Node {
    public:
        int data;
        Node* next;

        Node(int value);

        friend std::ostream& operator<<(std::ostream& os, const Node& node);

        ~Node();
};

Node::Node(int value): data(value), next(nullptr) {}

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


class SinglyLL {
    public:
        Node* head;
        int size;

        SinglyLL();

        virtual void insert_at_end(int data);

        void insert_at_start(int data);

        void remove_at_end();

        void remove_at_start();

        void print();
        
        virtual ~SinglyLL();
};


SinglyLL::SinglyLL(): head(nullptr), size(0) {}


void SinglyLL::insert_at_start(int data) {
    Node* newNode = new Node(data);
    newNode->next = head;
    head = newNode;
    size++;
}


void SinglyLL::insert_at_end(int data) {
    if (head == nullptr) {
        head = new Node(data);
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


void SinglyLL::remove_at_start() {
    if (head == nullptr) {
        std::cout << "List is empty, nothing to remove.\n";
        return;
    }
    Node* temp = head;
    head = head->next;
    delete temp;
    size--;
}


void SinglyLL::remove_at_end() {
    if (head == nullptr) {
        std::cout << "List is empty, nothing to remove.\n";
        return;
    }
    if (head->next == nullptr) {
        delete head;
        head = nullptr;
    } else {
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        delete current->next;
        current->next = nullptr;
    }
    size--;
}


void SinglyLL::print () {
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


SinglyLL::~SinglyLL() {
    Node* current = head;
    Node* temp = nullptr;
    while (current != nullptr) {
        temp = current;
        current = current->next;
        delete temp;
    }
}


class ModifiedSLL: public SinglyLL {
    public:
        Node* tail;


        ModifiedSLL() : tail(nullptr) {}


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

        void remove_at_end() {
            if (head == nullptr) {
                std::cout << "List is empty, nothing to remove.\n";
                return;
            }
            if (head == tail) {
                delete head;
                head = tail = nullptr;
            } else {
                Node* current = head;
                while (current->next != tail) {
                    current = current->next;
                }
                delete tail;
                tail = current;
                tail->next = nullptr;
            }
            size--;
        }
};


int main() {
    ModifiedSLL list;

    // Test inserting at the end
    list.insert_at_end(10);
    list.insert_at_end(20);
    list.insert_at_end(30);

    // Print the list to verify the elements
    std::cout << "List after inserting at the end: ";
    list.print();

    // Verify the tail
    if (list.tail != nullptr) {
        std::cout << "Tail element: " << list.tail->data << "\n";
    } else {
        std::cout << "Tail is null" << "\n";
    }

    // Test inserting at the start
    list.insert_at_start(5);
    std::cout << "List after inserting 5 at the start: ";
    list.print();

    // Test removing from the start
    list.remove_at_start();
    std::cout << "List after removing from the start: ";
    list.print();

    // Test removing from the end
    list.remove_at_end();
    std::cout << "List after removing from the end: ";
    list.print();

    // Verify the tail again
    if (list.tail != nullptr) {
        std::cout << "Tail element: " << list.tail->data << "\n";
    } else {
        std::cout << "Tail is null" << "\n";
    }

    return 0;
}