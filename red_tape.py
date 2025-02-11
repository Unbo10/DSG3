class MyArray:
    def __init__(self, capacity):
        self.capacity = capacity
        self.size = 0
        for i in range(self.capacity):
            setattr(self, f'element_{i}', 0)

    def add(self, value):
        try:
            setattr(self, f'element_{self.size}', value)
            self.size += 1
        except IndexError:
            print("Error: Array is full")

    def add_at_index(self, value, index):
        try:
            self.size += 1
            setattr(self, f'element_{index}', value)
        except IndexError:
            print("Error: Index out of bounds")

    def get(self, index):
        if 0 <= index < self.capacity:
            return getattr(self, f'element_{index}')
        else:
            raise IndexError("Index out of bounds")

    def show(self, from_index: int = 0):
        for i in range(from_index, self.capacity):
            print(getattr(self, f'element_{i}'), end=" ")
        print()

if __name__ == "__main__":
    line: str = input()
    k: int = int(input())
    
    arr: MyArray = MyArray(capacity=100)
    arr_size: int = 0
    max_size: int = 0 #* Greatest number of requirements of all people in line
    i: int = 1
    char: str = line[i]
    requirement: str = ""

    #* ---Getting the data into an array of integers
    while (char != "]"):
        if (char == ","):
            i += 1
            char = line[i]
        else:
            while(char != "," and char != "]"):
                requirement += char
                i += 1
                char = line[i]
            if (int(requirement) > max_size):
                max_size = int(requirement)
            arr_size += 1
            arr.add(int(requirement))
            requirement = ""
        
    #* ---Create the arrays to the left and to the right of k (in the order the
    #* ---data was received)
    left_arr: MyArray = MyArray(max_size + 1)
    right_arr: MyArray = MyArray(max_size + 1)
    #* The i-th position will indicate how many people have i-th requirements
    #* e.g. [5,3,2,4,4] with k = 2 will yield right_arr = [0,0,0,0,2,0] and
    #* left_arr = [0,0,0,1,0,1]

    i = 0
    while (i < k):
        # print(left_arr.get(arr.get(i)))
        left_arr.add_at_index(left_arr.get(arr.get(i)) + 1, arr.get(i))
        i += 1
    
    i = k + 1
    while (i < arr_size):
        # print(right_arr.get(arr.get(i)))
        right_arr.add_at_index(right_arr.get(arr.get(i)) + 1, arr.get(i))
        i += 1

    # print("left", left_arr.size)
    # left_arr.show()
    # print("right", right_arr.size)
    # right_arr.show()

    start_index_r: int = 1
    start_index_l: int = 1
    procedures: int = 0
    i = 0
    k_requiremets = arr.get(k)
    # print("k requirements:", k_requiremets)
    while (k_requiremets > 0):
        try:
            procedures += left_arr.size #* Adding the number of pending requirements
            # print("Procedures l:", procedures, left_arr.size)
            # left_arr.show(from_index=start_index_l)
            left_arr.size -= left_arr.get(start_index_l) #* Subtracting the requirements fulfilled
            start_index_l += 1 #* Ignoring the requirements fulfilled
        except IndexError:
            pass
        k_requiremets -= 1
        procedures += 1
        if (k_requiremets == 0): #* In case k_requirements are fulfilled before going to the right
            break
        else:
            try:
                # print("Procedures r:", procedures, right_arr.size, procedures + right_arr.size)
                procedures += right_arr.size
                right_arr.size -= right_arr.get(start_index_r)
                # left_arr.show(from_index=start_index_r)
                start_index_r += 1
            except IndexError:
                pass

    procedures += k_requiremets #* In case the left and right requirements have been fulfilled and only k is missing
    # print("Procedures total:", procedures)
    print(procedures)
    
