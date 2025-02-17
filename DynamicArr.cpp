#include <iostream>

using namespace std;

class DynamicArr {
    private:
    int* arr_addr;
    int size;
    int capacity;


    public:
    DynamicArr(int initial_capacity) : size(0), capacity(initial_capacity) {
        arr_addr = (int*)malloc(sizeof(int) * capacity);
        if (!arr_addr) {
            throw bad_alloc();
        }
    }


    ~DynamicArr() {
        free(arr_addr);
    }


    /*Adds an element at `index`, doubling the capacity of the array if necessary and/or shifting every value from `size - 1` to `index` one position to the right and storing value at position `index`.*/
    void add(int value, int index = -1) {
        if (index == -1) {
            index = size;
        }
        if ((0 <= index) && (index <= size)) {
            if (size == capacity) {
                int* current_arr = arr_addr;
                arr_addr = (int*)malloc(sizeof(int) * (capacity * 2));
                if (!arr_addr) {
                    throw bad_alloc();
                }
                capacity *= 2; 
                size += 1;

                for (int i = 0; i < index; i++) {
                    arr_addr[i] = current_arr[i];
                }

                arr_addr[index] = value;

                for (int i = index + 1; i < size; i++) {
                    arr_addr[i] = current_arr[i - 1];
                }
                free(current_arr);
            }
            else {
                //* Shift elements to the right to make space
                for (int i = size; i > index; i--) {
                    arr_addr[i] = arr_addr[i - 1];
                }
                arr_addr[index] = value;
                size += 1;
            }
        }
        else {
            throw out_of_range("Index out of range"); //* It should never throw this exception
        }
    }


    /*Returns value at `index`, starting from 0.*/
    int get(int index) const {
        if ((0 <= index) && (index < size)) {
            return arr_addr[index];
        }
        else {
            throw out_of_range("Index out of range");
        }
    }


    /*Changes value stored at position `index`, starting from 0 (arr_addr[index] = value).*/
    int replace(int index, int value) {
        if ((0 <= index) && (index < size)) {
            arr_addr[index] = value;
        }
        else {
            throw out_of_range("Index out of range");
        }
    }


    /*Removes element at position `index`, starting from 0 (arr_addr[index]).*/
    void remove(int index) {
        if ((0 <= index) && (index < size)) {
            for (int i = index; i < size; i++) {
                arr_addr[i] = arr_addr[i + 1];
            }
            size -= 1;
        }
        else {
            throw out_of_range("Index out of range");
        }
    }


    /*Returns the index at which `value` is stored or `-1` if `value` is not stored in any position of the array.*/
    int find_index(int value) const {
        for (int i = 0; i < size; i++) {
            if (arr_addr[i] == value) {
                return i;
            }
        }
        return -1;
    }


    friend istream& operator>>(istream& is, DynamicArr& arr) {
        int value;
        is >> value;
        arr.add(value);
        return is;
    }


    friend ostream& operator<<(ostream& os, const DynamicArr& arr) {
        os << "[";
        for (int i = 0; i < arr.size - 1; i++) {
            os << arr.arr_addr[i] << ", ";
        }
        if (arr.size > 0) {
            os << arr.arr_addr[arr.size - 1];
        }
        os << "]";

        return os;
    }
};

int main() {
    DynamicArr arr(5);
    cout << "Empty array: " << arr << "\n";
    for (int i = 0; i < 6; i++) {
        arr.add(i);
        cout << arr << "\n";
    }
    arr.remove(3);
    cout << arr << "\n";
    cout << "Five is at " << arr.find_index(5) << "\n";
}