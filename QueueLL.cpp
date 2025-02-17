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

class Queue {
    private:
        ModifiedSLL list;
        int size;
    
    
    public:
        Queue() : list(), size(0) {}


        ~Queue() {}


        void enqueue(int value) {
            list.insert_at_end(value);
            size += 1;
        }


        void dequeue() {
            if (size > 0) {
                list.remove_at_start();
                size -= 1;
            }
            else {
                throw length_error("Queue is empty");
            }
        }


        int peek() {
            return list.head->data;
        }


        int get_size() {
            return size;
        }


        void print() {
            list.print();
        }
};


int main() {
    Queue queue;

    // Test enqueue
    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);
    std::cout << "Queue after enqueueing 10, 20, 30: ";
    queue.print();


    // Test peek
    std::cout << "Front element: " << queue.peek() << "\n";


    // Test dequeue
    queue.dequeue();
    std::cout << "Queue after dequeueing: ";
    queue.print(); // Should print 20 30


    std::cout << "Queue size: " << queue.get_size() << "\n";
    queue.dequeue();
    queue.dequeue();
    std::cout << "Queue after dequeueing all elements: ";
    queue.print();

    // Test dequeue on empty queue (should throw an exception)
    try {
        queue.dequeue();
    } catch (const std::exception& e) {
        std::cout << "Exception caught: " << e.what() << "\n"; // Should print "Queue is empty"
    }

    return 0;
}