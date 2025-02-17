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
            throw bad_alloc();
        }
    }

    ~Array() {
        free(arr_addr);
    }

    void add_at_end(int value) {
        if (size < capacity) {
            arr_addr[size++] = value;
        } else {
            throw out_of_range("Exceeding capacity");
        }
    }

    void remove_end() {
        if (size > 0) {
            arr_addr[--size] = 0;
        } else {
            throw out_of_range("Array is empty");
        }
    }

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

    int get(int index) const {
        if (index >= 0 && index < size) {
            return arr_addr[index];
        }
        throw out_of_range("Index out of range");
    }

    void set(int index, int value) {
        if (index >= 0 && index < size) {
            arr_addr[index] = value;
        } else {
            throw out_of_range("Index out of range");
        }
    }

    void show_elements() const {
        for (int i = 0; i < size; ++i) {
            cout << arr_addr[i] << " ";
        }
        cout << "\n";
    }

    int getSize() const { return size; }
};

class PriorityQueue {
private:
    Array arr;


public:
    PriorityQueue(int capacity) : arr(capacity) {}


    void enqueue(int value) {
        if (arr.getSize() == 0) {
            arr.add_at_end(value);
        } else {
            int i;
            // Shift elements to the right to make space for the new value
            for (i = arr.getSize() - 1; (i >= 0) && (arr.get(i) < value); i--) {
                if (i + 1 < arr.getSize()) {
                    arr.set(i + 1, arr.get(i));
                } else {
                    arr.add_at_end(arr.get(i));
                }
            }
            // Insert the new value at the correct position
            if (i + 1 < arr.getSize()) {
                arr.set(i + 1, value);
            } else {
                arr.add_at_end(value);
            }
        }
    }


    void dequeue() {
        if (arr.getSize() > 0) {
            arr.remove_start();
        } else {
            throw out_of_range("Priority queue is empty");
        }
    }


    int peek() const {
        if (arr.getSize() > 0) {
            return arr.get(0);
        } else {
            throw out_of_range("Priority queue is empty");
        }
    }


    int get_size() const {
        return arr.getSize();
    }


    void print() const {
        arr.show_elements();
    }
};

int main() {
    PriorityQueue pq(10);

    // Test enqueue
    pq.enqueue(30);
    pq.enqueue(20);
    pq.enqueue(50);
    pq.enqueue(40);
    std::cout << "Priority queue after enqueueing 30, 20, 50, 40: ";
    pq.print(); // Should print 50 40 30 20

    // Test peek
    std::cout << "Front element: " << pq.peek() << "\n"; // Should print 50

    // Test dequeue
    pq.dequeue();
    std::cout << "Priority queue after dequeueing: ";
    pq.print(); // Should print 40 30 20

    std::cout << "Priority queue size: " << pq.get_size() << "\n"; // Should print 3

    // Test dequeue until empty
    pq.dequeue();
    pq.dequeue();
    pq.dequeue();
    std::cout << "Priority queue after dequeueing all elements: ";
    pq.print(); // Should print nothing

    // Test dequeue on empty queue (should throw an exception)
    try {
        pq.dequeue();
    } catch (const std::exception& e) {
        std::cout << "Exception caught: " << e.what() << "\n"; // Should print "Priority queue is empty"
    }

    return 0;
}