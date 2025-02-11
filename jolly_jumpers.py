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


class Node:
    def __init__(self, value=None):
        self.value = value
        self.next = None


class Vector:
    def __init__(self, size=0, default_value=None):
        self.data = CustomList()
        for _ in range(size):
            self.data.add(default_value)

    def __getitem__(self, index):
        return self.data[index]

    def __setitem__(self, index, value):
        self.data[index] = value

    def __len__(self):
        return len(self.data)

    def __iter__(self):
        return iter(self.data)


class BooleanVector(Vector):
    def __init__(self, size=0):
        super().__init__(size, False)


def is_jolly_sequence(n, values):
    if n == 1:
        return "Jolly"

    seen = BooleanVector(n)
    for i in range(1, n):
        diff = abs(values[i] - values[i - 1])
        if 1 <= diff < n:
            seen[diff] = True

    for i in range(1, n):
        if not seen[i]:
            return "Not jolly"

    return "Jolly"


def main():
    results = CustomList()

    while True:
        try:
            line = input()
            if not line:
                continue
            
            data = CustomList()
            for char in line:
                data.add(char)
            
            data.strip()
           
            parts = data.split(" ")
            n = int(parts[0])  
            values = CustomList()
            for i in range(1, len(parts)):
                values.add(int(parts[i]))  

            v = Vector(n)
            for i in range(n):
                v[i] = values[i]

            result = is_jolly_sequence(n, v)
            results.add(result)

        except EOFError:
            break

    for result in results:
        print(result)


if __name__ == "__main__":
    main()