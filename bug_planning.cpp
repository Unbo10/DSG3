#include <bits/stdc++.h>
#include "Node.h"
#include "List.h"

using namespace std;

class Node {
    public:
        int data;
        Node* next;

        Node(int value): data(value), next(nullptr) {} //* That syntaz initializes data and next with the values specified inside the parenthesis.

        ~Node() {
            delete next;
        }
};

class List {
    Node* head;
    int size;
    public:
        List() {
            head = nullptr;
            size = 0;
        }

        void insert_at_end(int data) {
            if (head == nullptr) {
                head->data = data; //* Since the constructor of List
            }
            else {
                Node* newNode = new Node(data);
                Node* tail = nullptr;
                Node* current = head;
                while (current->next != nullptr) {
                    current = current->next;
                }
                tail = current;
                tail->next = newNode->next; 
            }
            size++;
        }

        void insert_at_position(int data, int position) {
            //* Insert data at position, starting from 0
            int i = 0;
            Node* current = head;
            Node* node_at_position = nullptr;
            while ((i < position) && (current->next != nullptr)) { //* The second condition could be replaced with size, technically
                current = current->next;
                i++;
            }
            if ((current->next == nullptr) && (i < position)) {
                cout << "Position out of range";
            }
            else {
                current = node_at_position;
                node_at_position->data = data;
            }
        }

        int get_value(int position) {
            int i = 0;
            if ((i > size) || (i < 0)) {
                cout << "Invalid position: " << i << "\n";
                cout << "The size of the list is: " << size << "\n";
            }
            else {
                Node* current = head;
                Node* node_at_position = nullptr;
                while (i < position) {
                    current = current->next;
                    i++;
                }
                return current->data;
            }
        }

        ~List() {
            if (head->next == nullptr) {
                head->~Node();
            }
            else {
                Node* current = head;
                Node* temp = nullptr;
                while (current->next != nullptr) {
                    temp = current;
                    delete current;
                    current = temp->next;
                }
            }
        }
};

int main() {
    int n = 0, temp = 0;
    cin >> n;
    List arr, gis;
    for (int i = 0; i < n; i++) {
        cin >> temp;
        arr.insert_at_end(temp);
    }
    gis.insert_at_position(arr.get_value(0), 0);
    int current = 0;
    int i = 0;
    int j = 0;
    int k = 1;
    bool bigger_id_found = false;
    while (i < n){
        current = arr.get_value(i);
        bigger_id_found = false;
        while (j < n && bigger_id_found == false) {
            if (arr.get_value(j) > current) {
                bigger_id_found = true;
            }
            else {
                j++;
            }
        }
        if (bigger_id_found == true) {
            gis.insert_at_position(arr.get_value(j), k);
            k++; //* Guarantees in the end that it is = to the size of gis
        }
        i = j;
        j++;
    }
    cout << k << "\n"; //*k is the length of the GIS too
    for (int i = 0; i < k; i++) {
        cout << gis.get_value(i) << " ";
    }
    // cout << "\n";
}