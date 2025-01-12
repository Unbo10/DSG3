#include "iostream"
#include "List.h"

using namespace std;

int main() {
    List arr;
    arr.insert_at_end(5);
    cout << "A \n";
    arr.insert_at_end(9);
    cout << "B \n";
    arr.insert_at_end(10);
    cout << "C \n";
    arr.change_data_at_position(arr.get_value(2), 0);
    cout << "D \n";
    arr.print();
    cout << arr.size;
    return 0;
}