#region Graphs
class Vertex:
    def __init__(self, data):
        self.data = data
        self.adjacencies = []
    
    def add_adjacency(self, other, weight):
        self.adjacencies.append((other, weight))

    def __lt__(self, other):
        return self.data < other.data

class Graph:
    def __init__(self):
        self.verticies = set()
        self.edges = set() # For Kruskals NOT prims 

    def add_edge(self, u, v, weight):
        in_edges = False
        
        # Find if the edge already exists
        for edge in self.edges:
            if ((edge[0] == u) and (edge[1] == v)) or ((edge[0] == v) and (edge[1] == u)):
                in_edges = True
        
        if not in_edges:
            self.edges.add((u,v,weight))

            if u not in self.verticies:
                self.verticies.add(u)
            if v not in self.verticies:
                self.verticies.add(v)
            
            u.add_adjacency(v, weight)
            v.add_adjacency(u, weight)
            pass
    
    def dijkstra(self, start):
        distances = {v: float('inf') for v in self.nodes}
        distances[start] = 0
        que = [(0, start)]

        while que:
            curr_dis, curr_node = que.pop(0)
            if curr_dis > distance[curr_node]:
                continue
            
            for neighbor, weight in curr_node.edges:
                distance = curr_dis + weight
                if distance < distances[neighbor]:
                    distances[neighbor] = distance
                    que.add(0, (distance, neighbor))

    def prims(self):
        # Need Heapq
        import heapq

        # Min-Heap priority Queue
        #   (Lowest weight is prioritized)
        #   next(iter(self.verticies)) -> gets first vertex (random)
        pq = [(0, next(iter(self.verticies)), None)]

        mst = []
        visited = set()
        min_cost = 0

        while pq:
            weight, curr_vertex, prev_vertex = heapq.heappop(pq)

            # Skip past any already visitied verticies
            if curr_vertex in visited:
                continue
            
            # Add the cost onto the min_cost
            min_cost += weight
            # Add the prev, current vertex and weight into the MST
            mst.append((prev_vertex, curr_vertex, weight))
            # Mark this vertex as visited
            visited.add(curr_vertex)

            for neighbor, weight in curr_vertex.adjacencies:
                # If we haven't visited the neighbor, add it onto the priority queue
                if neighbor not in visited:
                    heapq.heappush(pq, (weight, neighbor, curr_vertex))

        return (mst, min_cost)
        
simple = True
    
if simple:
    graph = Graph()
    
    # Constructing some nodes
    a = Vertex('A')
    b = Vertex('B')
    c = Vertex('C')
    d = Vertex('D')
    
    # Connecting them in the graph
    graph.add_edge(a, b, 1)
    graph.add_edge(a, c, 4)
    graph.add_edge(b, c, 2)
    graph.add_edge(b, d, 5)
    graph.add_edge(c, d, 1)
    
    mst, min_cost = graph.prims()
    print("The minimum spanning tree for this graph is:\n")
    
    for v in mst:
        print(f"{str(v[0])} <---> {str(v[1])}  |  Weight: {v[2]}")
    
    print(f"\nthe min cost is: {min_cost}")

else: 
    graph = Graph()
    
    a = Vertex('0')
    b = Vertex('1')
    c = Vertex('2')
    d = Vertex('3')
    e = Vertex('4')
    f = Vertex('5')
    g = Vertex('6')
    h = Vertex('7')
    i = Vertex('8')
    
    # Adding '0's weights 
    graph.add_edge(a, b, 4)
    graph.add_edge(a, h, 8)
    
    # Adding '1's weights 
    graph.add_edge(b, h, 11)
    graph.add_edge(b, c, 8)
    
    # Adding '2's weights 
    graph.add_edge(c, d, 7)
    graph.add_edge(c, i, 2)
    graph.add_edge(c, f, 4)
    
    # Adding '3's weights 
    graph.add_edge(d, e, 9)
    graph.add_edge(d, f, 14)
    
    # Adding '4's weights 
    graph.add_edge(e, f, 10)
    
    # Adding '5's weights 
    graph.add_edge(f, g, 2)
    
    # Adding '6's weights 
    graph.add_edge(g, h, 1)
    graph.add_edge(g, i, 6)
    
    # Adding '7's weights 
    graph.add_edge(h, i, 7)
    
    print("\n")
    
    mst, min_cost = graph.prims()
    print("The minimum spanning tree for this graph is:\n")
    for v in mst:
        print(f"{str(v[0])} <---> {str(v[1])}  |  Weight: {v[2]}")
    print(f"\nthe min cost is: {min_cost}")


#endregion Graphs






#region LinkedList
class NodeList:
    def __init__(self, data, next = None, prev = None):
        self.data = data
        self.next = next
        self.prev = prev
    
    def get_data(self):
        return self.data
    
    def get_next(self):
        return self.next
    
    def get_previous(self):
        return self.prev

class LinkedList:
    def __init__(self, data = None):
        if data:
            self.tail = self.head = NodeList(data)
        else:
            self.tail = self.head = None

    def push_front(self, data):
        if not self.head:
            self.tail = self.head = NodeList(data)
        else:
            node = NodeList(data)
            node.next = self.head
            self.head.prev = node
            self.head = node

    def __iter__(self):
        return ListIterator(self)

    def push_back(self, data):
        if not self.tail:
            self.head = self.tail = NodeList(data)
        else:
            node = NodeList(data)
            node.prev = self.tail
            self.tail.next = node
            self.tail = node

    def pop_front(self):
        if not self.head:
            raise IndexError("pop_front() used on empty LinkedList")
        
        popped_value = self.head
        new_head = self.head.next
        if new_head:
            new_head.prev = None
        
        if self.head == self.tail:
            self.tail = new_head

        self.head = new_head
        return popped_value

    def pop_back(self):
        if not self.tail:
            raise IndexError("pop_back() used on empty LinkedList")
        
        popped_value = self.tail
        new_back = self.tail.prev
        if new_back:
            new_back.next = None
        
        if self.tail == self.head:
            self.head = new_back
        
        self.tail = new_back
        return popped_value

    def get_front(self):
        return self.head

    def get_back(self):
        return self.tail

    def __str__(self) -> str:
        words = "[ "
        curr = self.head
        while curr: 
            words += str(curr.data) + (", " if curr.next != None else " ")
            curr = curr.next
        return words + "]" 

class ListIterator:
    def __init__(self, linked_list):
        self.current = linked_list.head
    
    def __iter__(self):
        return self

    def __next__(self):
        if self.current == None:
            raise StopIteration
        
        data = self.current.get_data()
        self.current = self.current.next
        return data

ll = LinkedList()
ll.push_back(808)
ll.push_front(10)
ll.push_front(15)
ll.push_front(-4)
ll.push_back(2)
ll.push_front(40)
ll.push_back(10)
ll.push_back(100)
ll.pop_front()
ll.push_back(40)
ll.pop_back()
ll.push_back(40)
# [40, -4, 15, 10, 808, 2, 10, 100]
print('LinkedList:')
print(ll)

print('\nPrinting from iterator...')
for data in ListIterator(ll):
    print(data, end = ', ')

#endregion LinkedList






#region Stack

class Stack:
    def __init__(self):
        self.stack = LinkedList()
        self.size = 0

    def pop(self):
        if self.size == 0:
            raise IndexError("pop() used on empty stack")
        self.stack.pop_back()
        self.size -= 1 

    def peek(self):
        if (n:= self.stack.get_back()):
            return n.get_data()
        else:
            return None
    
    def push(self, data):
        self.size += 1
        self.stack.push_back(data)
    
    def is_empty(self):
        return self.size == 0

    def __str__(self) -> str:
        return str(self.stack)
         
print('\n\nStack')
stack = Stack()
print(stack.peek())
stack.push(10)
stack.push(3)
stack.push(23)
stack.push(65)
stack.pop()
stack.push(15515)
print(stack)

#endregion Stack






#region Queue
class Queue:
    def __init__(self):
        self.queue = LinkedList()
        self.size = 0

    def is_empty(self):
        return self.size == 0
    
    def enqueue(self, data):
        if data:
            self.queue.push_back(data)
            self.size += 1
    
    def dequeue(self):
        if self.is_empty():
            raise IndexError("dequeue() used on empty stack")
        
        self.size -= 1
        return self.queue.pop_front().get_data()

    def peek(self):
        if (n:= self.queue.get_front()):
            return n.get_data()
        else:
            return None

    def __str__(self) -> str:
        return str(self.queue)

print('\nQueue')
queue = Queue()
print(queue.peek())
queue.enqueue(10)
queue.enqueue(3)
queue.enqueue(23)
queue.enqueue(65)
print(queue.dequeue())
queue.enqueue(15515)

print(queue)


#endregion Queue







#region Sorting

#region Quick Sort
def QuickSort(arr):
    if (n:= len(arr)) > 1:
        pivot = arr[n // 2]

        left  = [x for x in arr if x < pivot]
        mid   = [x for x in arr if x == pivot]
        right = [x for x in arr if x > pivot]

        return QuickSort(left) + mid + QuickSort(right)
    return arr
#endregion Quick Sort

#region Merge Sort
def merge_sort(arr):
    if (n:= len(arr)) > 1:
        mid = n // 2

        left  = arr[:mid]
        right = arr[mid:]

        merge_sort(left)
        merge_sort(right)

        i = j = k = 0
        while i < len(left) and j < len(right):
            if left[i] < right[j]:
                arr[k] = left[i]
                i += 1
            else:
                arr[k] = right[j]
                j += 1
            k += 1

        while i < len(left):
            arr[k] = left[i]
            i += 1
            k += 1

        while j < len(right):
            arr[k] = right[j]
            j += 1
            k += 1
    return arr
#endregion Merge Sort

#region Insertion Sort
def insertion_sort(arr):
    for i in range(1, len(arr)):
        key = arr[i]
        j = i - 1
        while j >= 0 and arr[j] > key:
            arr[j + 1] = arr[j]
            j -= 1
        arr[j+1] = key
    return arr        
#endregion Insertion Sort

#region Selection Sort
def selection_sort(arr):
    for i in range(len(arr) - 1):
        min_index = i
        for j in range(i+1, len(arr)):
            if arr[j] < arr[min_index]:
                min_index = j
        arr[min_index], arr[i] = arr[i], arr[min_index]
    
    return arr
#endregion Selection Sort

#region Bubble Sort
def bubble_sort(arr):
    for i in range(len(arr)):
        for j in range(len(arr) - i - 1):
            if arr[j] > arr[j+1]:
                arr[j], arr[j+1] = arr[j+1], arr[j]
    
    return arr
#endregion Bubble Sort

print('\n\nSorting...')
arr = [6,-1,4,0,3,88,5,3,5,2]
print('\nUnsorted Array:\t', arr)
print('Quick-Sort:\t', QuickSort(arr))
print('Merge-Sort:\t', merge_sort(arr))
print('Insertion-Sort:\t', insertion_sort(arr))
print('Selection-Sort:\t', selection_sort(arr))
print('Bubble-Sort:\t', bubble_sort(arr))

#endregion Sorting








#region Search

def linear_search(arr, key):
    found_index = None
    for i in range(len(arr)):
        if arr[i] == key:
            found_index = i
            i = len(arr) # end loop prematurly 
    
    return found_index

def binary_search(arr, key):
    left  = 0
    right = len(arr) - 1
    
    found_index = None


    while left <= right:
        mid = (left + right) // 2

        if arr[mid] == key:
            found_index = mid
            left = right + 1
        elif arr[mid] > key:
            right = mid - 1
        else:
            left = mid + 1

    return found_index

print('\n\nSearching...')
arr = merge_sort(arr)
print('array: ', arr)
print('\nlinear-search(5):\t', linear_search(arr, 5))
print('linear-search(-1):\t',  linear_search(arr, -1))
print('linear-search(1):\t',  linear_search(arr, 1))
print('\nBinary-search(5):\t', binary_search(arr, 5))
print('Binary-search(-1):\t',  binary_search(arr, -1))
print('Binary-search(1):\t',  binary_search(arr, 1))

#endregion Search







#region Hash-Tables

#region chaining hashmap
class chaining_hashmap:
    def __init__(self, cap = 10):
        self.cap = cap
        self.buckets = [[] for _ in range(cap)]

    def hash_function(self, data):
        return hash(hash(data)) % self.cap

    def insert(self, key, value):
        index = self.hash_function(key)
        self.buckets[index].append((key, value))

    def find(self, key):
        index = self.hash_function(key)
        for n in self.buckets[index]:
            if n and n[0] == key:
                return n
        return None
    
    def __getitem__(self, key):
        return self.find(key)

    def __setitem__(self, key, value):
        self.insert(key, value)
  

print('\n\nHashMaps...')
hashmap = chaining_hashmap()
hashmap.insert('A', 1)
hashmap.insert('B', 2)
hashmap.insert('C', 3)
hashmap.insert('D', 8)
hashmap.insert('A', 100)
print(hashmap.find('A'))
print(hashmap.find('B'))
print(hashmap.find('D'))
print(hashmap.find('G'))
print(hashmap['A'])
hashmap['G'] = 2222
print(hashmap['G'])
#endregion chaining hashmap

#region linear probing
class linear_probing:
    def __init__(self, cap = 32):
        self.size = 0
        self.cap = cap
        self.buckets = [None] * cap
        self.tombstone = "Dead"
    
    def hash_function(self, key):
        return id(key) % self.cap
    
    def insert(self, key, value):
        original_index = self.hash_function(key)
        index = original_index

        while self.buckets[index]:
            index = (index + 1) % self.cap

            if original_index == index:
                return False # Hash table is full

        self.buckets[index] = (key, value)
        self.size += 1
        return True
        
    def __str__(self) -> str:
        return str(self.buckets)


lp = linear_probing()
lp.insert("apple")
lp.insert("banana")
lp.insert("orange")
print(lp)
lp.insert("andy")
lp.insert("apple")
print(lp) 

#endregion linear probing

#endregion Hash-Tables