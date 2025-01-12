#include <iostream>
#include "Node.h"
#include "List.h"

using namespace std;

int main() {
    int n = 0, temp = 0;
    cin >> n;
    List arr, gis;
    for (int i = 0; i < n; i++) {
        cin >> temp;
        arr.insert_at_end(temp);
    }
    gis.insert_at_end(arr.get_value(0));
    int current = 0;
    int i = 0;
    int j = 0;
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
            gis.insert_at_end(arr.get_value(j));
        }
        i = j;
        j++;
    }
    cout << gis.size << "\n";
    i = 0;
    while (i < gis.size) {
        cout << gis.get_value(i);
        if (i < gis.size - 1) {
            cout << " "; //* To avoid leaving a space at the end.
        }
        i++;
    }
    // cout << "\n";
    return 0;
}