#include <iostream>
#include <cstdlib>

using namespace std;

class Array {
public:
    int* elements;
    int capacity;
    int size;

    Array(int capacity) : capacity(capacity), size(0) {
        elements = (int*)malloc(capacity * sizeof(int));
        if (elements == nullptr) {
            throw std::bad_alloc();
        }
    }

    //* Copy constructor for deep copy
    Array(const Array& other) : capacity(other.capacity), size(other.size) {
        elements = (int*)malloc(capacity * sizeof(int));
        if (elements == nullptr) {
            throw std::bad_alloc();
        }
        for (int i = 0; i < size; i++) {
            elements[i] = other.elements[i];
        }
    }

    //* Assignment operator for deep copy
    Array& operator=(const Array& other) {
        if (this == &other) {
            return *this;
        }
        free(elements);
        capacity = other.capacity;
        size = other.size;
        elements = (int*)malloc(capacity * sizeof(int));
        if (elements == nullptr) {
            throw std::bad_alloc();
        }
        for (int i = 0; i < size; i++) {
            elements[i] = other.elements[i];
        }
        return *this;
    }

    ~Array() {
        delete[] elements;
    }

    void add(int value) {
        if (size < capacity) {
            *(elements + size) = value; //* Using pointer arithmetic to add the element
            size++;
        } else {
            throw std::out_of_range("Trying to add element when capacity of array is exceeded");
        }
    }

    int get(int index) {
        if (index >= 0 && index < size) {
            return *(elements + index); //* Using pointer arithmetic to access the i-th element
        } else {
            throw std::out_of_range("Index out of range");
        }
    }

    Array slice(int start, int end) {
        int new_capacity = end - start;
        Array new_arr(new_capacity);
        for (int i = start; i < end && i < size; i++) {
            new_arr.add(get(i));
        }
        return new_arr;
    }

    void show_elements() {
        for (int i = 0; i < size; i++) {
            std::cout << get(i) << " ";
        }
        std::cout << std::endl;
    }

    int search_element(int element) {
    for (int i = 0; i < size; i++) {
        if (get(i) == element) {
            return i;
        }
    }
    cerr << "Error: Element not found" << endl;
    return -1;
    }

    Array operator+(const Array other) const {
        Array new_array(size + other.size);
        for (int i = 0; i < size; i++) {
            new_array.add(elements[i]);
        }
        for (int i = 0; i < other.size; i++) {
            new_array.add(other.elements[i]);
        }
        return new_array;
    }

    friend std::istream& operator>>(std::istream& is, Array array) {
        int value;
        is >> value;
        array.add(value);
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, Array array) {
        for (int i = 0; i < array.size; i++) {
            os << array.get(i) << " ";
        }
        return os;
    }
};

Array find_subtrees_ino(Array ino, Array pre) {
    int root_position = ino.search_element(pre.get(0));
    int root = ino.get(root_position);
    Array left_inorder = ino.slice(0, root_position);
    Array right_inorder = ino.slice(root_position + 1, ino.capacity);
    Array left_preorder = pre.slice(1, root_position + 1);
    Array right_preorder = pre.slice(root_position + 1, pre.capacity);

    Array subtrees_orders(5);
    subtrees_orders.add(left_inorder.capacity);
    subtrees_orders.add(right_inorder.capacity);
    subtrees_orders.add(left_preorder.capacity);
    subtrees_orders.add(right_preorder.capacity);
    subtrees_orders.add(root);

    return subtrees_orders;
}

Array postorder(Array ino, Array pre) {
    if (ino.capacity <= 1) {
        return ino;
    } 
    else {
        cout << "A";
        Array subtrees = find_subtrees_ino(ino, pre);
        Array subtree_root(1);
        subtree_root.add(subtrees.get(4));
        return postorder(subtrees.get(0), subtrees.get(2)) + postorder(subtrees.get(1), subtrees.get(3)) + subtree_root;
    }
}

int main() {
    int n = 0;
    cin >> n;
    Array pre(n), ino(n);
    for (int i = 0; i < n; i++) {
        int value;
        cin >> value;
        pre.add(value);
    }
    for (int i = 0; i < n; i++) {
        int value;
        cin >> value;
        ino.add(value);
    }
    // cout << pre << "|" << ino << "\n";
    
    postorder(ino, pre);
    
    return 0;
}
