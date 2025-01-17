class MyString:
    def __init__(self, value=""):
        # Validate that the value is either an iterable of characters or another MyString
        if isinstance(value, MyString):
            # If it's already a MyString, copy its internal value
            self._value = value._value
        else:
            # Check if value is iterable and contains only single-character strings
            try:
                # Manually iterate over the value to ensure it's iterable
                self._value = ""
                for char in value:
                    # Validate that each element is a single-character string-like value
                    if not (isinstance(char, str) and len(char) == 1):
                        raise TypeError("Value must be an iterable of single-character strings")
                    self._value += char  # Concatenate character to build the string
            except TypeError:
                # Raise an error if the value is not iterable
                raise TypeError("Value must be an iterable of single-character strings")

    def __str__(self):
        return self._value

    def __add__(self, other):
        # Custom concatenation without using "+"
        if isinstance(other, MyString):
            other = other._value
        if not isinstance(other, str):
            raise TypeError("Can only concatenate with a string or MyString")
        result = []
        for char in self._value:
            result.append(char)
        for char in other:
            result.append(char)
        return MyString("".join(result))
    
    def split(self, sep=None):
        # Split the string and return a list of MyString
        if sep is None:
            raise ValueError("Separator must not be None")
        parts, current = [], []
        for char in self._value:
            if char == sep:
                parts.append(MyString("".join(current)))
                current = []
            else:
                current.append(char)
        parts.append(MyString("".join(current)))
        return parts
    
    def join(self, iterable):
        # Join an iterable of strings or MyString instances
        result = []
        first = True
        for item in iterable:
            if not first:
                result.extend(self._value)
            first = False
            result.extend(str(item) if isinstance(item, MyString) else item)
        return MyString("".join(result))
    
    def strip(self):
        # Remove leading and trailing whitespace
        start, end = 0, len(self._value) - 1
        while start <= end and self._value[start].isspace():
            start += 1
        while end >= start and self._value[end].isspace():
            end -= 1
        return MyString(self._value[start:end + 1])

class MyList:
    def __init__(self, initial=None):
        # Initialize the internal storage as an empty array
        self._data = []  # Start with an empty list
        if initial is not None:
            try:
                for item in initial:
                    self.append(item)  # Add items one by one
            except TypeError:
                raise TypeError("The provided initial value must be iterable")

    def __str__(self):
        # Build the string representation using MyString
        result = MyString("[")
        for i, item in enumerate(self._data):
            # Convert each item to MyString
            item_str = MyString(str(item)) if not isinstance(item, MyString) else item
            result += item_str
            if i < len(self._data) - 1:
                result += MyString(", ")
        result += MyString("]")
        return str(result)  # Convert the final MyString to a regular string

    def __iter__(self):
        # Iteration support
        return iter(self._data)

    def append(self, item):
        # Append an item to the end of the list
        self._data += [item]

def process_operations(posts, operations):
    for a, b in operations:
        
        a -= 1 # To start the count of positions in the array from 0
        b -= 1
 
        posts[a] = posts[a] + posts[b]
        posts[b] = ""

        last_modified_index = a

    return posts[last_modified_index]

if __name__ == "__main__":
    n = int(input())
    posts = MyList()

    if n == 1:
        print(input())
    
    else:
        for line in range(n):
            post = str(input())
            posts.append(post)

        operations = MyList()
        for line in range(n - 1):
            a, b = map(int, input().split())
            operations.append((a, b))

        result = process_operations(posts._data, operations)

        print(result)