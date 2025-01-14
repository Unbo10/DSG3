    #include <iostream>

    class Node {
        public:
            int data;
            Node* next;

            Node(int value);

            // friend std::ostream& operator<<(std::ostream& os, const Node& node);

            ~Node();
    };

    Node::Node(int value): data(value), next(nullptr) {} //* That syntaz initializes data and next with the values specified inside the parenthesis.

    Node::~Node() {}

    // std::ostream& operator<<(std::ostream& os, const Node& node) {
    //     os << "Node data: " << node.data;
    //     if (node.next != nullptr) {
    //         os << ", Next node at: " << node.next;
    //     } else {
    //         os << ", Next node: nullptr";
    //     }
    //     os << "\n";
    //     return os;
    // };

    class List {
        public:
            Node* head;
            int size;

            List();

            virtual void insert_at_end(int data);

            // void change_data_at_position(int data, int position);

            // void print();

            // int get_value(int position);
            
            virtual ~List();
    };

    List::List(): head(nullptr), size(0) {}

    void List::insert_at_end(int data) {
        if (head == nullptr) {
            head = new Node(data); //* Since the constructor of List
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

    // void List::change_data_at_position(int data, int position) {
    //     //* Insert data at position, starting from 0 (equivalent to the [] operator)
    //     int i = 0;
    //     Node* current = head;
    //     while ((i < position) && (current->next != nullptr)) { //TODO: Test if the second condition could be replaced with size, technically
    //         current = current->next;
    //         i++;
    //     }
    //     if ((current->next == nullptr) && (i < position)) {
    //         std::cout << "Position out of range";
    //     }
    //     else {
    //         current->data = data;
    //     }
    // }

    // void List::print () {
    //     std::cout << "[";
    //     if (size != 0) {
    //         std::cout << head->data;
    //         Node* current = head->next;
    //         while (current != nullptr) {
    //             std::cout << ", " << current->data;
    //             current = current->next;
    //         }
    //     }
    //     std::cout << "]\n";
    // }

    // int List::get_value(int position) {
    //     int i = 0;
    //     if ((i > size) || (i < 0)) {
    //         std::cout << "Invalid position: " << i << "\n";
    //         std::cout << "The size of the list is: " << size << "\n";
    //     }
    //     else {
    //         Node* current = head;
    //         while (i < position) {
    //             current = current->next;
    //             i++;
    //         }
    //         return current->data;
    //     }
    //     return 0;
    // }



    List::~List() {
        Node* current = head;
        Node* temp = nullptr;
        while (current != nullptr) {
            temp = current;
            current = current->next;
            temp->next = nullptr; //* To break the link between the current and the next node, so a segmentation fault doesn't appear in consequence. May be unnecessary.
            delete temp;
        }
    }

    class ModifiedList: public List {
        public:
            Node* tail;
            void insert_at_end(int data) {
                if (head == nullptr) {
                    head = new Node(data);
                    tail = head;
                }
                else {
                    Node* newNode = new Node(data);
                    //*TODO: Check if it doesn't need a condition to check for the nulity of previous_to_tail
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
        ModifiedList arr, gis;
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
        // cout << "\n";
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
        // cout << "\n";
        return 0;
    }