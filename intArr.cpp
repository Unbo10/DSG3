#include <iostream>

using namespace std;

class Array {
private:
    int* arr_addr;
    int capacity;
    int size;

public:
    Array(int capacity) : capacity(capacity), size(0) {
        arr_addr = (int*)malloc(capacity * sizeof(int));
        if (!arr_addr) {
            throw std::bad_alloc();
        }
    }


    ~Array() {
        free(arr_addr);
    }


    /*Adds `value` at the end of the array if it doesn't exceed its capacity*/
    void add_at_end(int value) {
        if (size < capacity) {
            arr_addr[size++] = value;
        } else {
            throw std::out_of_range("Exceeding capacity");
        }
    }


    /*Removes the last element, setting it to 0 and decreasing the array's size*/
    void remove_end() {
        arr_addr[size] = 0;
        size--;
    }


    /*Removes the first element and decreases the array's size*/
    void remove_start() {
        if (size > 0) {
            for (int i = 0; i < size - 1; i++) {
                arr_addr[i] = arr_addr[i+1];
            }
            size--;
        }
        else {
            throw length_error("Array is empty");
        }
    }


    /*Returns the element at `index` if `index` is a position within the array.*/
    int get(int index) const {
        if (index >= 0 && index < capacity) {
            return arr_addr[index];
        }
        throw std::out_of_range("Index out of range");
    }


    /*Replaces the value at `index` for `value`.*/
    void set(int index, int value) {
        if (index >= 0 && index < capacity) {
            arr_addr[index] = value;
        } else {
            throw std::out_of_range("Index out of range");
        }
    }

    void show_elements_() const {
        for (int i = 0; i < size; ++i) {
            cout << arr_addr[i] << " ";
        }
        cout << "\n";
    }

    int getSize() const { return size; }
};