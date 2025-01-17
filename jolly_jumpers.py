class CustomList:
    def __init__(self):
        self.data = []

    def append(self, value):
        self.data.append(value) #TODO: Make the method from scratch

    def __getitem__(self, index):
        return self.data[index]

    def __setitem__(self, index, value):
        self.data[index] = value

    def __len__(self):
        return len(self.data)

    def __iter__(self):
        return iter(self.data)


class Vector:
    def __init__(self, size=0, default_value=None):
        self.data = [default_value] * size

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

            v = Vector(0)

            data = line.split() #TODO: Make the method from scratch
            n = int(data[0])
            values = CustomList()
            for i in range(1, len(data)):
                values.append(int(data[i]))

            v = Vector(n)
            for i in range(n):
                v[i] = values[i]

            result = is_jolly_sequence(n, v)
            results.append(result)

        except EOFError:
            break

    for result in results:
        print(result)


if __name__ == "__main__":
    main()