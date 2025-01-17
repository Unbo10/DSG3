#include "iostream"
#include "LinkedList.h"

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

void LinkedList::change_data_at_position(int data, int position) {
    //* Insert data at position, starting from 0 (equivalent to the [] operator)
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

int LinkedList::get_value(int position) {
    int i = 0;
    if ((i > size) || (i < 0)) {
        std::cout << "Invalid position: " << i << "\n";
        std::cout << "The size of the LinkedList is: " << size << "\n";
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

LinkedList::~LinkedList() {
    Node* current = head;
    Node* temp = nullptr;
    while (current != nullptr) {
        temp = current;
        current = current->next;
        delete temp;
    }
}