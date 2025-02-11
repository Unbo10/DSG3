#include <iostream>
using namespace std;

// Node for the LinkedList
struct Node {
    int data;
    Node* next;

    Node(int val) : data(val), next(nullptr) {}
};

// Custom LinkedList class to store adjacency list
class LinkedList {
public:
    Node* head;

    LinkedList() : head(nullptr) {}

    // Function to add a new node at the end
    void append(int val) {
        Node* newNode = new Node(val);
        if (!head) {
            head = newNode;
            return;
        }
        Node* current = head;
        while (current->next) {
            current = current->next;
        }
        current->next = newNode;
    }

    // Getter of the head of the list
    Node* getHead() {
        return head;
    }
};

// Recursive function to print concatenated strings
void printRecursively(LinkedList* adj, char** strings, int idx) {
    int i = 0;
    while (strings[idx][i] != '\0') {
        cout << strings[idx][i];
        i++;
    }
    Node* current = adj[idx].getHead();
    while (current) {
        printRecursively(adj, strings, current->data);
        current = current->next;
    }
}

int main() {
    int n;
    cin >> n;

    // Arrays for strings and adjacency list
    char** strings = new char*[n];
    LinkedList* adj = new LinkedList[n];

    for (int i = 0; i < n; i++) {
        string str;
        cin >> str;
        strings[i] = new char[str.length() + 1];
        for (int j = 0; j < (int(str.length()) + 1); j++) {
            strings[i][j] = str[j];
        } 
    }

    int lastIdx = 0; // Track the root of the List

    for (int i = 0; i < n - 1; i++) {
        int idx1, idx2;
        cin >> idx1 >> idx2;
        idx1--; // Convert to 0-based indexing
        idx2--;
        adj[idx1].append(idx2); // Add idx2 as a child of idx1
        lastIdx = idx1; // Update the root
    }

    printRecursively(adj, strings, lastIdx);
    cout << endl;

    // Delete dynamically-allocated memory
    delete[] strings;
    delete[] adj;

    return 0;
}