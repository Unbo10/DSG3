# DATA STRUCTURES

> ADT (Abstract Data Type): An specification of the relations of the information within a set of data and the operations you can do within it. 
>
> It goes all the way back to OOP: and ADT will tell you *what* does the DS need to do and not *how*, since that's part of its implementation. In consequence, an ADT can be seen as a class interface.
>
> For example: if you have the set of seats inside a theater, you have a set of data.
>
> - About the seats (data), you want to know whether there is a person sat on them or not.
> - Regardin the operations you can do with seats (data), you may want to: know how many seats are available in total, how many seats are available in a single row, change the state of a seat (remove or sat a person in it), etc.

# Linear data structures

## Arrays

### Static arrays

> Contiguous and linear memory locations consisting of equal-size elements indexed by contiguous integers.

- Its main advantage is that you can access the elements in constant time (O(1)), since you just compute `arr_adress + (elements_size * index)`, where `index` is the position you are trying to get the element from.
- In contrast, it's costliest operation is adding an element and removing one at the start of the array (O(n)), because you have to move all the elements one position to the 'right' and one to the 'left', respectively.
- It's size is fixed, which is one of its strengths but may be an inconvinience in certain implementations (requires n memory locations)

Implementation in C++ (of an array of integers. If an array of another DS is needed, you should just replace `int` with the data structure required, like `double` for instance):

```cpp
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
```

#### Multi-dimensional static arrays

You can also have an array of arrays that will allow you to create a 2D array (in fact, it can be extended to nD arrays). The way it works is: you store the arrays as `arr_addr = [arr_addr0, arr_addr1, ..., arr_addrn]`.

- To access an element, you would use the `arr_addr[i][j]` notation: `i` denotes the array you want to get the element from, and `j` denotes the index within the `i`-th array were you expect the element you want to get to be in.
- However, to preserve the idea that arrays are elements stored in contiguous positions, what you could do is define an array, say of integers, of size `i * n`, where `i` denotes the number of rows and `n` denotes the number of columns. Then, if you want to access `arr_addr[i][j]`, you would instead use `arr_addr[((i-1)*n) + (j-1)]`, or, equivalently, `*(arr_addr + element_size*((i-1)*n) + (j-1)))` in C or C++.


### Dynamic arrays

Arrays have a huge advantage: you can access any of its elements in constant time. Almost none (if any) other data structure allows for accessing an element in constant time. This is because of the pragmatic mathematical formula to access any element, that is just that, a formula and not a cycle.

However, their Achilles' heel is that they have a fixed size, and so they are not suitable for a ton of cases. This is what dynamic arrays were created for: to make arrays as powerful as possible:

- Just like an static array, they store a reference to the adress of the array, but here comes the twitch: the array is not always the same. Every time the *capacity* of the array is exceeded (when it is equal to its *size*), a new array is initialized with double the capacity of the previous one. Afterwards, all the elements of the previous array are copied to the new one, and just like that, you have a new array with greater capacity.
- In consequence, they must store the *current array's address*, their current *capacity* (current maximum amount of elements), and their current *size* (current total number of elements).
- This way, the cost of most operations is constant. The only ones that are linear are: adding an element when `size == capacity - 1`, adding/removing an element at the *i*-th index (not at the tail), and finding an element with a certain value.
- It's more inefficient, but if you want, every time `size == capacity / 2` (floor), you can create a new array with half the capacity and paste all the elements to that one. But again, it's not worth it, since adding a new element would require to resize it again, and removing an element becomes an O(n^2) operation.

Here's an implementation in C++:

```cpp
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
```


## Linear DS

### Linked lists

#### Nodes

A node is a way to connect data while still being able to access the information. This is because nodes store, at least, a value and another node to which they are related (the previous or the next one, in a linear representation). You could see it as a TransMilenio bus route: each station (node), has a certain amount of people the bus needs to pick up (information or value), and in a certain route, they also have the next station the bus needs to stop in (relation).

The most basic implementation of a Node is this one:

```cpp
#include <iostream>

class Node {
private:
    int value;
    Node* other;

public:
    Node(int val, Node* othr = nullptr) : value(val), other(othr) {}

    int get_value() const {
        return value;
    }

    Node* get_other() const {
        return other;
    }

    void set_other(Node* othr) {
        other = othr;
    }
};
```

Now, we're ready for linked lists (which, as you may have already figured out, are just a set of modified nodes):

#### Singly-linked lists

> "A collection of nodes that store a value and the next node in a a linear represetation"

You can think of as a "move forward and don't look back" implementation.

- It stores the "head" node (or a reference to it), the first node from left to right, and its current size/length/capacity (can vary).
- Each node stores its value (or key) and its immediately-next node.
- It may also store the "tail" node (or a reference to it), the last node from left to right, to append or add an element in constant time (O(1)).
- Its cheapest operations are: adding at *head* (O(1)), removing *head* and getting the value stored in *head*.
- Every other operation is done in linear time, i.e., adding at *tail* (if it's stored, then it's constant), getting the value stored in *tail* (also constant if stored in the list), getting the value of a node that's not the *head* nor the *tail* (linear), removing the tail (linear), finding a node with a certain value (linear), adding after or before a specific node (linear).
- Replacing the tail can be done in constant time if there's a reference to the penultimate node (from L to R).
- It's main strength it's its dynamic size.

Here's a implementation in C++ (with and without tail):

```cpp
#include <iostream>

using namespace std;

#include <iostream>

class Node {
    public:
        int data;
        Node* next;

        Node(int value);

        friend std::ostream& operator<<(std::ostream& os, const Node& node);

        ~Node();
};

Node::Node(int value): data(value), next(nullptr) {}

std::ostream& operator<<(std::ostream& os, const Node& node) {
    os << "Node data: " << node.data;
    if (node.next != nullptr) {
        os << ", Next node at: " << node.next;
    } else {
        os << ", Next node: nullptr";
    }
    os << "\n";
    return os;
};

Node::~Node() {
    next = nullptr;
}


class SinglyLL {
    public:
        Node* head;
        int size;

        SinglyLL();

        virtual void insert_at_end(int data);

        void insert_at_start(int data);

        void remove_at_end();

        void remove_at_start();

        void print();
        
        virtual ~SinglyLL();
};


SinglyLL::SinglyLL(): head(nullptr), size(0) {}


void SinglyLL::insert_at_start(int data) {
    Node* newNode = new Node(data);
    newNode->next = head;
    head = newNode;
    size++;
}


void SinglyLL::insert_at_end(int data) {
    if (head == nullptr) {
        head = new Node(data);
    }
    else {
        Node* newNode = new Node(data);
        Node* current = head;
        int i = 0;
        while (current->next != nullptr) {
            current = current->next;
            i++;
        }
        current->next = newNode; //*Newnode will become the new tail.
    }
    size++;
}


void SinglyLL::remove_at_start() {
    if (head == nullptr) {
        std::cout << "List is empty, nothing to remove.\n";
        return;
    }
    Node* temp = head;
    head = head->next;
    delete temp;
    size--;
}


void SinglyLL::remove_at_end() {
    if (head == nullptr) {
        std::cout << "List is empty, nothing to remove.\n";
        return;
    }
    if (head->next == nullptr) {
        delete head;
        head = nullptr;
    } else {
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        delete current->next;
        current->next = nullptr;
    }
    size--;
}


void SinglyLL::print () {
    std::cout << "[";
    if (size != 0) {
        std::cout << head->data;
        Node* current = head->next;
        while (current != nullptr) {
            std::cout << ", " << current->data;
            current = current->next;
        }
    }
    std::cout << "]\n";
}


SinglyLL::~SinglyLL() {
    Node* current = head;
    Node* temp = nullptr;
    while (current != nullptr) {
        temp = current;
        current = current->next;
        delete temp;
    }
}


class ModifiedSLL: public SinglyLL {
    public:
        Node* tail;


        ModifiedSLL() : tail(nullptr) {}


        void insert_at_end(int data) {
            if (head == nullptr) {
                head = new Node(data);
                tail = head;
            }
            else {
                Node* newNode = new Node(data);
                tail->next = newNode; //* Point the old tail to the new node
                tail = newNode; //* Update the tail to be the new node
            }
            size++;
        }

        void remove_at_end() {
            if (head == nullptr) {
                std::cout << "List is empty, nothing to remove.\n";
                return;
            }
            if (head == tail) {
                delete head;
                head = tail = nullptr;
            } else {
                Node* current = head;
                while (current->next != tail) {
                    current = current->next;
                }
                delete tail;
                tail = current;
                tail->next = nullptr;
            }
            size--;
        }
};
```


#### Doubly-linked lists

> A linear collection of nodes that store their previous and next node, and a value.

You can think of as going up or down a staircase: at a certain step or level, you can only go one step back or one step forward.

- It stores a reference to the *head* node and its current *size* (it may also store a reference to the *tail* node).
- Every node has a reference to its *previous* and *next* nodes (in a linear representation) and a *value* or a key.
- Its cheapest operations are: adding at head (O(1)), removing at head (O(1)), and adding at head (O(1)).
- Its costliest operations are: adding at *tail* (O(n), WT: O(1)), removing at *tail* (O(n), WT: O(1)), adding at *tail* (O(n), WT: O(1)), finding a node with an specified value (O(n)), and removing/adding a node at a certain position (O(n)).
- Just like a singly-linked list, one of its strengths is that its size is dynamic.
- Also, if the list is sorted, searching for an element can be done in (O(n/2)), which is still linear but can be useful for maximum efficiency.
- In contrast, you should bear in mind the nodes require one more memory position each (to store next) than those in linked lists.

Here's an implementation in C++ (with tail):

```cpp
#include <iostream>

class Node {
    public:
        int data;
        Node* next;
        Node* prev;

        Node(int value);

        friend std::ostream& operator<<(std::ostream& os, const Node& node);

        ~Node();
};

Node::Node(int value): data(value), next(nullptr), prev(nullptr) {}

std::ostream& operator<<(std::ostream& os, const Node& node) {
    os << "Node data: " << node.data;
    if (node.next != nullptr) {
        os << ", next node at: " << node.next;
    } else {
        os << ", next node: nullptr";
    }
    if (node.prev != nullptr) {
        os << ", prev node at: " << node.prev;
    } else {
        os << ", prev node: nullptr";
    }
    os << "\n";
    return os;
}

Node::~Node() {
    next = nullptr;
    prev = nullptr;
}

class DoublyLinkedList {
    public:
        Node* head;
        Node* tail;
        int size;

        DoublyLinkedList();
        void insert_at_end(int data);
        void print();
        ~DoublyLinkedList();
};

DoublyLinkedList::DoublyLinkedList(): head(nullptr), tail(nullptr), size(0) {}

void DoublyLinkedList::insert_at_end(int data) {
    Node* newNode = new Node(data);
    if (head == nullptr) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    size++;
}

void DoublyLinkedList::print() {
    std::cout << "[";
    Node* current = head;
    while (current != nullptr) {
        std::cout << current->data;
        if (current->next != nullptr) std::cout << ", ";
        current = current->next;
    }
    std::cout << "]\n";
}

DoublyLinkedList::~DoublyLinkedList() {
    Node* current = head;
    while (current != nullptr) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
}
```

> NOTE: There's a variant of linked lists known as circular linked lists. They can also be singly- or doubly- linked, and the only difference is that the tail points to the head in singly-linked and the head points to the tail and the tail to the head in doubly-linked.


### Stacks (LIFO/FILO queues)

You can think of as bread slices: they are stacked in the bag one after the other, and the first one to be eaten will be the last stacked (excluding ends if you dislike them). Consequentially, the first one to be stacked will be the last one to be eaten (FILO).

In addition, you can know with a peek what's the next bread to be eaten, you can stack one just by opening the bag and remove one just entering your hand and lifting it, and you can know how many slices are left by just counting them as you add them or remove them.

In other words, all the operations you can do with a stack are done in constant time. In fact, stacks were created so that adding/pushing and removing/popping were done as efficiently as possible.

- They can be implemented using an static array or a linked list (depending on whether you want a dynamically-sized stack or a fixed-size stack).
- They generally only have four operations: push or add at top, pop or remove at top, top or peek (returns the latest element added), and return current size (all done in O(1))
- Normally, *top* is the last element of the array or the linked list, so their *tail*.

Here's an implementation in C++ using the `Array` class from earlier:

```cpp
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
```

### Queues (FIFO)

You can picture it as the line that's formed at your favorite coffee shop: you will only get to the cashier once everyone that was already in line gets there too. Also, if people have modals, they will enter the line behind you and not in front of you.

In consequence, multiple actions can be done: the cashier can take the order of the first one in line and remove them from it, a person can enter the coffee shop and do the line, the cashier can know who's the next person to take the order from, and when you enter the shop, you can know how packed or empty it is.

- They can be implemented using an static array or a linked list (depending on whether you want a dynamically-sized stack or a fixed-size stack). However, it is not as straightforward as it is with stacks: if done with arrays, you need to maintain a reference to the first element written (it will move when popping) and to the next empty position (if it reaches the end, then it returns to the start, if not, throws an error); if done with linked lists, then just set the tail to the latest element added.
- You can perform four operations in them: enqueue (add at tail), dequeue (remove at head), peek (returns the element at tail), and get its size (return `size`).

Here's an implementation with linked lists in C++ (taking the same code from earlier):

```cpp
class Queue {
    private:
        ModifiedSLL list;
        int size;
    
    
    public:
        Queue() : list(), size(0) {}


        ~Queue() {}


        void enqueue(int value) {
            list.insert_at_end(value);
            size += 1;
        }


        void dequeue() {
            if (size > 0) {
                list.remove_at_start();
                size -= 1;
            }
            else {
                throw length_error("Queue is empty");
            }
        }


        int peek() {
            return list.head->data;
        }


        int get_size() {
            return size;
        }


        void print() {
            list.print();
        }
};
```


### Priority queues

You can think of as bank-jobs management system: each person fills in a form and depending on their errand, age, etc., they get a certain priority, depending on which they are called to the front desks.

Here's an implementation in C++ with the static array from earlier:

```cpp
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
```


## Trees

Can be traversed in different ways: in-order (Left -> Root -> Right), pre-order (Root -> Left -> Right), post-order (Left -> Right -> Root), and level-order (from top to bottom, left to right).

### Heaps

#### MaxHeap

Smallest elements always at root (leafs are the greatest).


### MinHeap

Greatest elements always at root (leafs are the smallest).

Python implementation:

```py
class MinHeap:
    def __init__(self, arr, n):
        self.heap = arr
        self.size = n
        for i in range((n - 1) // 2, -1, -1):
            self._heapify_down(i)

    def _heapify_down(self, i):
        heap, size = self.heap, self.size
        item = heap[i]
        while True:
            left = 2 * i + 1
            right = left + 1
            smallest = i
            if left < size and heap[left] < heap[smallest]:
                smallest = left
            if right < size and heap[right] < heap[smallest]:
                smallest = right
            if smallest == i:
                break
            heap[i], heap[smallest] = heap[smallest], heap[i]
            i = smallest

    def _heapify_up(self, i):
        heap = self.heap
        item = heap[i]
        while i > 0:
            parent = (i - 1) // 2
            if heap[parent] <= item:
                break
            heap[i], heap[parent] = heap[parent], heap[i]
            i = parent

    def pop(self):
        if self.size == 0:
            return None
        heap = self.heap
        min_elem = heap[0]
        self.size -= 1
        if self.size > 0:
            heap[0] = heap[self.size]
            self._heapify_down(0)
        return min_elem

    def push(self, item):
        if self.size < len(self.heap):
            self.heap[self.size] = item
        else:
            self.heap.append(item)
        self.size += 1
        self._heapify_up(self.size - 1)
```



