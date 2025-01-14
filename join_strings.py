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
    '''
    def __repr__(self):
        return f"MyString({self._value!r})"

    def __len__(self):
        return len(self._value)

    def __getitem__(self, index):
        # Support indexing and slicing
        if isinstance(index, slice):
            return MyString(self._value[index.start:index.stop:index.step])
        return self._value[index]
    '''
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
    '''
    def __contains__(self, substring):
        # Custom implementation of `in`
        if isinstance(substring, MyString):
            substring = substring._value
        if not isinstance(substring, str):
            raise TypeError("Can only check containment for a string or MyString")

        # Naive substring search
        for i in range(len(self._value) - len(substring) + 1):
            if self._value[i:i+len(substring)] == substring:
                return True
        return False

    def to_upper(self):
        # Convert to uppercase
        return MyString("".join(chr(ord(char) - 32) if 'a' <= char <= 'z' else char for char in self._value))

    def to_lower(self):
        # Convert to lowercase
        return MyString("".join(chr(ord(char) + 32) if 'A' <= char <= 'Z' else char for char in self._value))

    def find(self, substring):
        # Find a substring; return -1 if not found
        if isinstance(substring, MyString):
            substring = substring._value
        for i in range(len(self._value) - len(substring) + 1):
            if self._value[i:i+len(substring)] == substring:
                return i
        return -1

    def replace(self, old, new):
        # Replace a substring with another
        result = []
        i = 0
        while i < len(self._value):
            if self._value[i:i+len(old)] == old:
                result.append(new)
                i += len(old)
            else:
                result.append(self._value[i])
                i += 1
        return MyString("".join(result))
    '''
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
    '''
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
    '''
    def strip(self):
        # Remove leading and trailing whitespace
        start, end = 0, len(self._value) - 1
        while start <= end and self._value[start].isspace():
            start += 1
        while end >= start and self._value[end].isspace():
            end -= 1
        return MyString(self._value[start:end + 1])
    '''
    def count(self, substring):
        # Count occurrences of a substring
        count, i = 0, 0
        while i <= len(self._value) - len(substring):
            if self._value[i:i+len(substring)] == substring:
                count += 1
                i += len(substring)
            else:
                i += 1
        return count
    '''

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
    '''
    def __repr__(self):
        # Debug representation
        return f"MyList({self._data!r})"
    
    def __len__(self):
        # Length of the list
        return len(self._data)

    def __getitem__(self, index):
        # Get item at index or slice
        if isinstance(index, slice):
            return MyList(self._data[index])
        return self._data[index]

    def __setitem__(self, index, value):
        # Set item at index
        self._data[index] = value

    def __delitem__(self, index):
        # Delete item at index
        del self._data[index]
    '''
    def __iter__(self):
        # Iteration support
        return iter(self._data)
    '''
    def __contains__(self, item):
        # Check if item is in the list
        for element in self._data:
            if element == item:
                return True
        return False
    '''
    def append(self, item):
        # Append an item to the end of the list
        self._data += [item]
    '''
    def extend(self, iterable):
        # Extend the list with another iterable
        for item in iterable:
            self.append(item)

    def insert(self, index, item):
        # Insert an item at a specific index
        if index < 0:
            index += len(self._data)
        if index < 0:
            index = 0
        elif index > len(self._data):
            index = len(self._data)

        self._data = self._data[:index] + [item] + self._data[index:]

    def remove(self, item):
        # Remove the first occurrence of an item
        for i, element in enumerate(self._data):
            if element == item:
                del self._data[i]
                return
        raise ValueError(f"{item} not in list")

    def pop(self, index=-1):
        # Remove and return an item at a specific index
        if index < 0:
            index += len(self._data)
        if index < 0 or index >= len(self._data):
            raise IndexError("pop index out of range")
        item = self._data[index]
        del self._data[index]
        return item

    def clear(self):
        # Clear the list
        self._data = []

    def index(self, item, start=0, end=None):
        # Return the index of the first occurrence of an item
        if end is None:
            end = len(self._data)
        for i in range(start, min(end, len(self._data))):
            if self._data[i] == item:
                return i
        raise ValueError(f"{item} is not in list")

    def count(self, item):
        # Count occurrences of an item
        count = 0
        for element in self._data:
            if element == item:
                count += 1
        return count

    def reverse(self):
        # Reverse the list in place
        n = len(self._data)
        for i in range(n // 2):
            self._data[i], self._data[n - 1 - i] = self._data[n - 1 - i], self._data[i]

    def sort(self):
        self._data = self._merge_sort(self._data)

    def _merge_sort(self, data):
        if len(data) <= 1:
            return data

        # Divide the list into halves
        mid = len(data) // 2
        left = self._merge_sort(data[:mid])
        right = self._merge_sort(data[mid:])

        # Merge the sorted halves
        return self._merge(left, right)

    def _merge(self, left, right):
        result = []
        i = j = 0

        # Merge the two lists while sorting
        while i < len(left) and j < len(right):
            if left[i] < right[j]:
                result.append(left[i])
                i += 1
            else:
                result.append(right[j])
                j += 1

        # Append any remaining elements
        result.extend(left[i:])
        result.extend(right[j:])
        
        return result
    
    def copy(self):
        # Return a shallow copy of the list
        return MyList(self._data)
    '''

def process_operations(posts, operations):
    for a, b in operations:
        
        a -= 1
        b -= 1
 
        posts[a] = posts[a] + posts[b]
        posts[b] = MyString()

        last_modified_index = a

    return MyString(posts[last_modified_index])

n = int(input())
posts = MyList()

for line in range(n):
    post = MyString(input().strip())
    posts.append(post)

operations = MyList()
for line in range(n - 1):
    a, b = map(int, input().split())
    operations.append((a, b))

result = process_operations(posts._data, operations)

print(result)