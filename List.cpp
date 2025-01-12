#include "iostream"
#include "List.h"

List::List(): head(nullptr), size(0) {}

void List::insert_at_end(int data) {
    if (head == nullptr) {
        head = new Node(data); //* Since the constructor of List
        std::cout << *head;
    }
    else {
        Node* newNode = new Node(data);
        Node* tail = nullptr;
        Node* current = head;
        int i = 0;
        while (current->next != nullptr) {
            std::cout << *current;
            current = current->next;
            std::cout << "i:" << i << "\n";
            i++;
        }
        tail = current;
        tail->next = newNode; //*Newnode will become the new tail.
        std::cout << "TAIL " << tail->next;
    }
    size++;
}

void List::change_data_at_position(int data, int position) {
    //* Insert data at position, starting from 0
    int i = 0;
    Node* current = head;
    while ((i < position) && (current->next != nullptr)) { //TODO: Test if the second condition could be replaced with size, technically
        current = current->next;
        i++;
    }
    if ((current->next == nullptr) && (i < position)) {
        std::cout << "Position out of range";
    }
    else {
        current->data = data;
    }
}

void List::print () {
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

int List::get_value(int position) {
    int i = 0;
    if ((i > size) || (i < 0)) {
        std::cout << "Invalid position: " << i << "\n";
        std::cout << "The size of the list is: " << size << "\n";
    }
    else {
        Node* current = head;
        while (i < position) {
            current = current->next;
            i++;
        }
        return current->data;
    }
    return 0;
}

List::~List() {head->~Node();}