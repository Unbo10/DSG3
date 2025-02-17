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

    
    void add_at_end(int value) {
        if (size < capacity) {
            arr_addr[size++] = value;
        } else {
            throw std::out_of_range("Exceeding capacity");
        }
    }


    void remove_end() {
        arr_addr[size] = 0;
        size--;
    }


    int get(int index) const {
        if (index >= 0 && index < capacity) {
            return arr_addr[index];
        }
        throw std::out_of_range("Index out of range");
    }


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


class Stack {
private:
    Array arr;
    int capacity;
    int size;


public:
    Stack(int capacity) : arr(capacity), capacity(capacity), size(0) {}


    ~Stack() {}


    /*Adds `value` to the top of the stack (the end of the array) if it's not full.*/
    void push(int value) {
        if (size == capacity) {
            throw length_error("Maximum capacity of array reached");
        }
        else {
            arr.add_at_end(value); //* Adds at end.
            size++;
        }
    }


    /*Removes the last element added to the stack if it's not empty.*/
    void pop() {
        if (size > 0) {
            arr.remove_end();
            size--; // Decrement size after removing an element
        } else {
            throw out_of_range("Stack is empty");
        }
    }


    /*Returns top or the last element that was added, or `-1` if the stack is empty.*/
    int peek() const {
        if (size > 0) {
            return arr.get(size - 1);
        }
        else {
            return -1;
        }
    }


    int get_size() const {
        return size;
    }
};

int main() {
    Stack stack(5);

    stack.push(10);
    stack.push(20);
    stack.push(30);
    cout << "Top element: " << stack.peek() << endl;
    stack.pop();
    stack.pop();
    cout << "Top element after removing two elements: " << stack.peek() << endl;

    return 0;
}