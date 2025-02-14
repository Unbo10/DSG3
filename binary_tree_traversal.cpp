#include <iostream>

using namespace std;

class Array {
private:
    int* elements;
    int capacity;
    int size;

public:
    Array(int capacity) : capacity(capacity), size(0) {
        elements = (int*)malloc(capacity * sizeof(int));
        if (!elements) {
            throw std::bad_alloc();
        }
    }

    ~Array() {
        free(elements);
    }

    void add(int value) {
        if (size < capacity) {
            elements[size++] = value; //* Not an array, just an operation with a pointer (essentially, pointer + size)
        } else {
            throw std::out_of_range("Exceeding capacity");
        }
    }

    int get(int index) const {
        if (index >= 0 && index < capacity) {
            return elements[index];
        }
        throw std::out_of_range("Index out of range");
    }

    void set(int index, int value) {
        if (index >= 0 && index < capacity) {
            elements[index] = value;
        } else {
            throw std::out_of_range("Index out of range");
        }
    }

    void showElements() const {
        for (int i = 0; i < size; ++i) {
            cout << elements[i] << " ";
        }
        cout << "\n";
    }

    int getSize() const { return size; }
};

void postorder(const Array& ino, const Array& pre, int startIno, int endIno, int startPre, int endPre, Array& result, const Array& inoPos) {
    if (endIno <= startIno) {
        return;
    }
    if (endIno - startIno == 1) {
        result.add(ino.get(startIno)); //* Start building the posorder adding the roots
        //* Whenever it enters this if, the root is actually the left-most element
        //* of the tree being analyzed (it's a leaf, in fact).
        return;
    }

    int root = pre.get(startPre);
    int rootPosition = inoPos.get(root);

    //* Left subtree (take all to the left of the root being aware of where to start from)
    //* i.e., when getting the left subtree of a right tree, you have to start from
    //* the previous rootPosition
    postorder(ino, pre, startIno, rootPosition, startPre + 1, startPre + 1 + (rootPosition - startIno), result, inoPos);
    
    //* Right subtree (take all the elements to the right of the root), bearing in mind
    //* where to end, since sometimes you may end before the previous root.
    postorder(ino, pre, rootPosition + 1, endIno, startPre + 1 + (rootPosition - startIno), endPre, result, inoPos);
    
    //* Add root at the end
    result.add(root);
}

int main() {
    int n;
    cin >> n;

    int temp = 0;
    Array pre(n), ino(n);
    for (int i = 0; i < n; i++) {
        cin >> temp;
        pre.add(temp);
    }
    for (int i = 0; i < n; i++) {
        cin >> temp;
        ino.add(temp);
    }

    //* Make a key-value map to search the elements in constant time
    Array inoPos(100001); //* Since 1 <= n <= 10^5
    for (int i = 0; i < n; i++) {
        inoPos.set(ino.get(i), i); //* This means inoPos.get(i) = position of i in ino
    }

    Array pos(n);
    postorder(ino, pre, 0, n, 0, n, pos, inoPos);
    pos.showElements();
    
    return 0;
}
