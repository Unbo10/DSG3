#include <iostream>
#include "Node.h"
#include "ModifiedLL.h"

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