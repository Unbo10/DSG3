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
        

    def search_element_position(self, element: int) -> int:
        """Returns the position of the element if present. Otherwise, it prints an error message"""
        current = 0
        while ((self.get(current) != element) and (current < self.size)):
            current += 1
        if current == self.capacity:
            print(f"The element {element} is not in {self}")
            return None
        else:
            return current


    def show_elements(self) -> None:
        show_str: str = ""
        for i in range(self.size - 1):
            show_str += str(self.get(i)) + " "
        if self.capacity != 0:
            show_str += str(self.get(self.size - 1))
        print(show_str)

    
    def pretty_print(self, end: int = None, start: int = 0) -> str:
        if end == None: 
            end = self.size
        repr_str: str = "[ "
        if end > start:
            for i in range(start, end):
                repr_str += str(self.get(i)) + " "
        repr_str += "]"
        return repr_str


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


def postorder(ino: MyArray, pre: MyArray, start_ino: int, end_ino: int, start_pre: int, end_pre: int) -> MyArray:
    """Takes into account ino[start_ino:end_ino] and pre[start_pre:end_pre], both exclusive at the end, to make the calculations.
    - ino: Inorder: Left -> Root -> Right
    - pre: Preorder: Root -> Left -> Right
    """
    if (end_ino - start_ino == 1):
        element = MyArray(1)
        element.add(ino.get(start_ino))
        return element
    elif (end_ino - start_ino == 0):
        empty = MyArray(0)
        return empty
    else:
        root: int = pre.get(start_pre)
        root_position: int = ino.search_element_position(root)
        # print(ino.pretty_print(end_ino, start_ino), pre.pretty_print(end_pre, start_pre), root_position, root, start_pre, end_pre)
        root_array = MyArray(1)
        root_array.add(root)
        #* Left + Right + Root
        return postorder(ino, pre, start_ino, root_position, start_pre + 1, start_pre + 1 + (root_position - start_ino)) + postorder(ino, pre, root_position + 1, end_ino, start_pre + 1 + (root_position - start_ino), end_pre) + root_array


def main() -> None:
    n = int(input())
    pre_input = input()
    ino_input = input()
    pre: MyArray = convert_input_to_array(pre_input, n) #* Root -> Left -> Right
    ino: MyArray = convert_input_to_array(ino_input, n) #* Left -> Root -> Right
    pos: MyArray = postorder(ino, pre, 0, n, 0, n)
    pos.show_elements()

if __name__ == "__main__":
    main()