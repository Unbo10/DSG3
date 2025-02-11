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
            raise IndexError(f"Trying to add {self.capacity + 1}-th element when capacity of array is {self.capacity}")


    def get(self, index):
        if 0 <= index < self.size:
            return getattr(self, f'element_{index}')
        else:
            return "Error: Index out of range"
        

    def search_element(self, element) -> int:
        """Returns the position of the element if present. Otherwise, it prints an error message"""
        current = 0
        while (self.get(current) != element and (current < self.capacity)):
            current += 1
        if current == self.capacity:
            print(f"The element {element} is not in {self}")
        else:
            return current


    def show_elements(self) -> None:
        show_str: str = ""
        for i in range(self.size - 1):
            show_str += str(self.get(i)) + " "
        if self.capacity != 0:
            show_str += str(self.get(self.size - 1))
        print(show_str)


    def slice(self, start: int = -1, end: int = -1) -> "MyArray":
        """returns self[start: end).
        
        Parameters: - start: int (defaults to 0).
        - end: int (defaults to self.capacity)"""

        if (start == -1):
            start = 0
        if (end == -1):
            end = self.capacity

        new_array = MyArray(end - start)
        for i in range(start, end):
            new_array.add(self.get(i))
        return new_array


    def __add__(self, other):
        if not isinstance(other, MyArray):
            return NotImplemented
        new_capacity = self.size + other.size
        new_array = MyArray(new_capacity)
        for i in range(self.size):
            new_array.add(self.get(i))
        for i in range(other.size):
            new_array.add(other.get(i))
        return new_array
    
    
    def __len__(self):
        return self.capacity
    
    
    def __repr__(self) -> str:
        print(self.capacity, end= " ")
        repr_str: str = "["
        for i in range(self.size - 1):
            repr_str += str(self.get(i)) + " "
        if self.capacity != 0:
            repr_str += str(self.get(self.size - 1))
        repr_str += "]"
        return repr_str


def convert_input_to_array(input: str, array_capacity: int) -> MyArray:
    array: MyArray = MyArray(array_capacity)
    temp: str = ""
    j: int = 0
    for i in range(0, array_capacity):
        temp = ""
        try:
            while (input[j] != " "):
                temp += input[j]
                j += 1
            j += 1
        except IndexError:
            pass
        array.add(int(temp))
        i += 1
    return array


def find_subtrees_ino(ino: MyArray, pre:MyArray) -> MyArray:
    root_position: int = ino.search_element(pre.get(0))
    left_inorder = ino.slice(0, root_position)
    right_inorder = ino.slice(root_position + 1, len(ino))
    left_preorder = pre.slice(1, root_position + 1)
    right_preorder = pre.slice(root_position + 1, len(pre))
    root: int = ino.get(root_position)
    subtrees_orders: MyArray = MyArray(5)
    subtrees_orders.add(left_inorder)
    subtrees_orders.add(right_inorder)
    subtrees_orders.add(left_preorder)
    subtrees_orders.add(right_preorder)
    subtrees_orders.add(root)

    # print(f"Left Inorder: {left_inorder}")
    # print(f"Right Inorder: {right_inorder}")
    # print(f"Left Preorder: {left_preorder}")
    # print(f"Right Preorder: {right_preorder}")
    # print(f"Root: {root}")

    return subtrees_orders

def postorder(ino: MyArray, pre:MyArray) -> MyArray:
    # print("count:", count, ino, pre)
    if (len(ino) <= 1):
        return ino
    else:
        subtrees = find_subtrees_ino(ino, pre)
        subtree_root = MyArray(1)
        subtree_root.add(subtrees.get(4))
        return postorder(subtrees.get(0), subtrees.get(2)) + postorder(subtrees.get(1), subtrees.get(3)) + subtree_root


def main() -> None:
    n = int(input())
    pre_input = input()
    ino_input = input()
    pre: MyArray = convert_input_to_array(pre_input, n)
    ino: MyArray = convert_input_to_array(ino_input, n)
    pos: MyArray = postorder(ino, pre)
    pos.show_elements()

if __name__ == "__main__":
    main()