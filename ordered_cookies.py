class Nodo:
    def __init__(self, valor):
        self.valor = valor
        self.siguiente = None

class ListaEnlazada:
    def __init__(self):
        self.cabeza = None
        self.cola = None
        self.longitud = 0
    
    def append(self, valor):
        nuevo_nodo = Nodo(valor)
        if self.cabeza is None:
            self.cabeza = nuevo_nodo
            self.cola = nuevo_nodo
        else:
            self.cola.siguiente = nuevo_nodo
            self.cola = nuevo_nodo
        self.longitud += 1
    
    def pop(self):
        if self.longitud == 0:
            return None
        if self.longitud == 1:
            valor = self.cabeza.valor
            self.cabeza = None
            self.cola = None
            self.longitud = 0
            return valor
        actual = self.cabeza
        while actual.siguiente != self.cola:
            actual = actual.siguiente
        valor = self.cola.valor
        actual.siguiente = None
        self.cola = actual
        self.longitud -= 1
        return valor
    
    def get(self, indice):
        if indice < 0 or indice >= self.longitud:
            return None
        actual = self.cabeza
        for _ in range(indice):
            actual = actual.siguiente
        return actual.valor
    
    def set(self, indice, valor):
        if indice < 0 or indice >= self.longitud:
            return
        actual = self.cabeza
        for _ in range(indice):
            actual = actual.siguiente
        actual.valor = valor
    
    def length(self):
        return self.longitud

class MinHeap:
    def __init__(self):
        self.heap = ListaEnlazada()
    
    def insert(self, valor):
        self.heap.append(valor)
        self._bubble_up(self.heap.length() - 1)
    
    def _bubble_up(self, indice):
        while indice > 0:
            padre = (indice - 1) // 2
            if self.heap.get(padre) > self.heap.get(indice):
                temp_padre = self.heap.get(padre)
                temp_indice = self.heap.get(indice)
                self.heap.set(padre, temp_indice)
                self.heap.set(indice, temp_padre)
                indice = padre
            else:
                break
    
    def extract_min(self):
        if self.heap.length() == 0:
            return None
        min_val = self.heap.get(0)
        ultimo_valor = self.heap.pop()
        if self.heap.length() > 0:
            self.heap.set(0, ultimo_valor)
            self._bubble_down(0)
        return min_val
    
    def _bubble_down(self, indice):
        while True:
            izquierdo = 2 * indice + 1
            derecho = 2 * indice + 2
            minimo = indice
            if izquierdo < self.heap.length() and self.heap.get(izquierdo) < self.heap.get(minimo):
                minimo = izquierdo
            if derecho < self.heap.length() and self.heap.get(derecho) < self.heap.get(minimo):
                minimo = derecho
            if minimo != indice:
                temp_indice = self.heap.get(indice)
                temp_minimo = self.heap.get(minimo)
                self.heap.set(indice, temp_minimo)
                self.heap.set(minimo, temp_indice)
                indice = minimo
            else:
                break
    
    def get_min(self):
        return self.heap.get(0) if self.heap.length() > 0 else None
    
    def size(self):
        return self.heap.length()

def parse_numbers(s):
    numbers = ListaEnlazada()
    current_number_str = ''
    for char in s:
        if char == ' ':
            if current_number_str != '':
                numbers.append(int(current_number_str))
                current_number_str = ''
        else:
            current_number_str += char
    if current_number_str != '':
        numbers.append(int(current_number_str))
    return numbers

def cookies(k, A):
    heap = MinHeap()
    current_node = A.cabeza
    while current_node is not None:
        heap.insert(current_node.valor)
        current_node = current_node.siguiente
    operaciones = 0
    while True:
        minimo_actual = heap.get_min()
        if minimo_actual is None or minimo_actual >= k:
            break
        if heap.size() < 2:
            return -1
        a = heap.extract_min()
        b = heap.extract_min()
        combinado = a + 2 * b
        heap.insert(combinado)
        operaciones += 1
    return operaciones if heap.get_min() is not None else -1

line1 = input().strip()
line2 = input().strip()

n_k = parse_numbers(line1)
if n_k.length() < 2:
    print(-1)
else:
    n = n_k.get(0)
    k = n_k.get(1)
    A = parse_numbers(line2)
    if A.length() != n:
        print(-1)
    else:
        resultado = cookies(k, A)
        print(resultado)