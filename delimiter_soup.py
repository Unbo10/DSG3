
class Node:
    def __init__(self, value=None):
        self.value = value
        self.next = None

class CustomList:
    def __init__(self):
        self.head = None
        self.tail = None
        self.size = 0

    def add(self, value):
        new_node = Node(value)
        if self.tail:
            self.tail.next = new_node
        else:
            self.head = new_node
        self.tail = new_node
        self.size += 1

    def __getitem__(self, index):
        current = self.head
        for _ in range(index):
            current = current.next
        return current.value

    def __setitem__(self, index, value):
        current = self.head
        for _ in range(index):
            current = current.next
        current.value = value

    def __len__(self):
        return self.size

    def __iter__(self):
        current = self.head
        while current:
            yield current.value
            current = current.next

    def split(self, separator):
        result = CustomList()
        current_value = ""
        for char in self:
            if char == separator:
                if current_value:
                    result.add(current_value)
                    current_value = ""
            else:
                current_value += char
        if current_value:
            result.add(current_value)
        return result

    def strip(self):
        current = self.head
        while current and current.value == " ":
            current = current.next
        self.head = current
        
        if self.head:
            current = self.head
            while current.next:
                current = current.next
            self.tail = current
        
        self.size = 0
        current = self.head
        while current:
            self.size += 1
            current = current.next

class MyArray:
    def __init__(self, capacity):
        self.capacity = capacity
        self.size = 0
        for i in range(self.capacity):
            setattr(self, f'element_{i}', None)

    def add(self, value):
        if self.size < self.capacity:
            setattr(self, f'element_{self.size}', value)
            self.size += 1
        else:
            print("Error: Array is full")

    def get(self, index):
        if 0 <= index < self.size:
            return getattr(self, f'element_{index}')
        else:
            return "Error: Index out of range"

    def show(self):
        for i in range(self.size):
            print(getattr(self, f'element_{i}'), end=" ")
        print()


class MyStack:
    def __init__(self, capacity):
        self.array = MyArray(capacity)
    
    def push(self, value):
        self.array.add(value)
    
    def pop(self):
        if self.array.size > 0:
            last_element = self.array.get(self.array.size - 1)
            setattr(self.array, f'element_{self.array.size - 1}', None)
            self.array.size -= 1
            return last_element
        else:
            print("Error: Stack is empty")
            return None
    
    def peek(self):
        if self.array.size > 0:
            return self.array.get(self.array.size - 1)
        else:
            print("Error: Stack is empty")
            return None
    
    def is_empty(self):
        return self.array.size == 0
    
    def show(self):
        self.array.show()

def check_parentheses(input_str: CustomList):
    stack = MyStack(len(input_str))
    delimiters = {
        '(': ')',
        '[': ']',
        '{': '}'
    }
    i = 0
    for char in input_str:
        if char in delimiters:
            stack.push((char, i))
        elif char in delimiters.values():
            if stack.is_empty():
                return f"{char} {i}"
            top, index = stack.pop()
            if delimiters[top] != char:
                return f"{char} {i}"
        i += 1
    
    if not stack.is_empty():
        return "ok so far"
    
    return "ok so far"


def process_input():
    n_chars = int(input())
    n_line = input()
    string = CustomList()
    for char in n_line:
        string.add(char)
    result = check_parentheses(string)
    print(result)


if __name__ == "__main__":
    process_input()