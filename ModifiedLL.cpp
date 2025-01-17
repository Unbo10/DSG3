#include "ModifiedLL.h"

void ModifiedLL::insert_at_end(int data) {
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