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
    arr.print();
    cout << arr.size;
    std::cout << "Hello!";
    return 0;
}