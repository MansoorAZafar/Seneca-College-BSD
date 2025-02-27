# Basic Tree
class Tree:
    def __init__(self, data=None):
        self.data = data
        self.children = []
    
    def add_child(self, data):
        if not self.data:
            self.data = data
        elif not any(filter(lambda x: x.data == data, self.children)) and data != self.data:
            print("Added Data")
            self.children.append(Tree(data))
            self.children.sort(key=lambda x: x.data)
        else:
            print("Data already in tree...")
            
# Binary Heap
class BinaryHeap:
    def __init__(self):
        self.heap = []
        
    def insert(self, data):
        self.heap.append(data)
        self._bubble_up(len(self.heap) - 1)
        
    def _bubble_up(self, index):
        parent = (index - 1) // 2
        
        while index > 0 and self.heap[parent] < self.heap[index]:
            self.heap[parent], self.heap[index] = self.heap[index], self.heap[parent]
            
            index = parent
            parent = (index - 1) // 2
            
    def remove_max(self):
        if not self.heap:
            return
        
        max_value = self.heap[0]
        last_value = self.heap.pop()
        
        if self.heap:
            self.heap[0] = last_value
            self._bubble_down(0)
            
        return max_value
            
    def _bubble_down(self, index):
        length = len(self.heap)
        
        # Can use range(log(n))
        while True:
            left = 2*index + 1
            rght = 2*index + 2
            
            max_index = index
            
            if left < length and self.heap[left] > self.heap[max_index]:
                max_index = left
            
            if rght < length and self.heap[rght] > self.heap[max_index]:
                max_index = rght
            
            if max_index == index:
                break
            
            self.heap[max_index], self.heap[index] = self.heap[index], self.heap[max_index]
            
            index = max_index

#SampleOutput:
# Heap: [8, 6, 7, 2, 5, 3, 4, 1]
# Max value: 8
# Removing max: 8
# Heap after removal: [7, 6, 4, 2, 5, 3, 1]



# Binary Tree + Heapify
class Binary_Tree:
    def __init__(self, data):
        self.data = data
        self.children = []
        
    def add_node(self, data):
        # Go through each line, and just add to the left and when it has
        # 2 children -> add to the right -> Repeat for sub-trees
        # NOT a BST
        que = [self]
        while que:
            curr = que.pop(0)
            
            if len(curr.children) < 2:
                curr.children.append(Binary_Tree(data))
                curr.children.sort(key=lambda x: x.data)
                que.clear()
            else:
                que.extend(curr.children)
        """
        5
        ├── 7
        ├── ├── 4
        ├── ├── └── 11
        ├── └── 9
        └── 8
        └── ├── -1
        └── └── 10
        """

            
    def display(self, level=0, prefix=""):
        # Print the current node with prefix for the connection
        print(prefix + f"{self.data}")
        
        # Prepare prefix for children nodes
        if self.children:
            for i, child in enumerate(self.children):
                # Use different prefixes for the last child to show branching
                if i == len(self.children) - 1:
                    child_prefix = "└── "
                    sub_prefix = "    "
                else:
                    child_prefix = "├── "
                    sub_prefix = "│   "
                
                # Recursively display each child node
                child.display(level + 1, prefix + child_prefix)

#myver
def heapify(a_node):        
    if a_node.children:
        for child in a_node.children:
            heapify(child)
    
        largest_child = max(a_node.children, key=lambda x: x.data)
        
        if largest_child.data > a_node.data:
            largest_child.data, a_node.data = a_node.data, largest_child.data
            heapify(largest_child)


# BST (Binary Search Tree)
class BST:
    def __init__(self, data=None):
        self.data = data
        self.left = None
        self.right = None
        
    def insert(self, data):
        if not self.data:
            self.data = data
        elif data < self.data:
            if self.left:
                self.left.insert(data)
            else:
                self.left = BST(data)
        elif data > self.data:
            if self.right:
                self.right.insert(data)
            else:
                self.right = BST(data)
    
    
    def find_min(self):
        curr = self.left
        while curr.left:
            curr = curr.left
        return curr
    
    def remove(self, data):
        if not self:
            return self
        
        if data < self.data:
            if self.left:
                self.left = self.left.remove(data)
        elif data > self.data:
            if self.right:
                self.right = self.right.remove(data)
        else:
            if not self.right and not self.left:
                return None
            
            if not self.left:
                return self.right
            if not self.right:
                return self.left
            
            sucessor = self.right.find_min()
            self.data = sucessor.data
            self.right = self.right.remove(self.data)
        
    def find_height(self):
        height = 0
        if self.data:
            left, right = 0, 0
            if self.left:
                left = self.left.find_height()
            if self.right:
                right = self.right.find_height()
            height = max(left, right) + 1
        return height
        
    def search(self, target):
        if self.data:
            if self.data == target:
                return True
            elif target < self.data and self.left:
                return self.left.search(target)
            elif target > self.data and self.right:
                return self.right.search(target)
        
        return False
    
    def in_order(self):
        if self.data:
            if self.left:
                self.left.in_order()
            print(self.data, end = " ")
            if self.right:
                self.right.in_order()
        
    def pre_order(self):
        if self.data:
            print(self.data, end = " ")
            if self.left:
                self.left.pre_order()
            if self.right:
                self.right.pre_order()
        
    def post_order(self):
        if self.data:
            if self.left:
                self.left.post_order()
            if self.right:
                self.right.post_order()
            print(self.data, end = " ")
    
    def breadth_first_print(self):
        import queue
        que = queue.Queue()
        
        if self.data:
            que.put(self)
        
        while not que.empty():
            curr = que.get()
            
            if curr.left:
                que.put(curr.left)
            if curr.right:
                que.put(curr.right)
            
            print(curr.data, end = " ")
    
    def print_tree(self, prefix, is_left=False):
        '''Prints a string representation of the actual tree.'''
        if self.data:
            print(prefix, end="")
            print("|__" if is_left else "|---", end="")
            print(self.data)
            # Enter the next tree level - left and right branch
            if self.left:
                self.left.print_tree(prefix + ("|   " if is_left else "    "), True)
            if self.right:
                self.right.print_tree(prefix + ("|   " if is_left else "    "), False)



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



class HashTable:
    #Constructor for HashTable. Accepts a starting capacity, defaults to 32 if none
    #Assigns default values
    #Returns none
    def __init__(self, capacity=32):
        self._capacity = capacity
        self._size = 0
        self._table = [None] * self._capacity

    #Hash function. Accepts a key 
    #Hashes the key and provides an index for where it should be stored
    #Resturns the index
    def _hash(self, key):
        return hash(key) % self._capacity

    #Returns capacity 
    def capacity(self):
        return self._capacity

    #Returns length
    def __len__(self):
        return self._size

    #Accepts a key and a value
    #Hashes the key to acquire an index then inserts that value-key pair into the table
    #Returns true if successful or false if one of the error conditions was met
    def insert(self, key, value):
        index = self._hash(key)
        initial_index = index

        # Linear probing to find an empty slot or update an existing key
        while self._table[index] is not None:
            if self._table[index][0] == key:  # Key already exists
                return False  # Do not add a new key-value pair
            index = (index + 1) % self._capacity
            if index == initial_index:  # Table is full
                return False

        # Insert new key-value pair
        self._table[index] = (key, value)
        self._size += 1
        
        if self._size / self._capacity > 0.7:# Resize when load factor exceeds 0.7
            self._resize()
        
        return True

    #Search function that accepts a key
    #Hashes the key and then searches for it with in the table. 
    #If successful, return the value
    def search(self, key):
        index = self._hash(key)
        initial_index = index

        while self._table[index] is not None:
            if self._table[index][0] == key:
                return self._table[index][1]
            index = (index + 1) % self._capacity
            if index == initial_index:
                break

        return None
    
    #Modify function that accepts a key and a value
    #Searches for a key within the table and replaced with the new value
    #Returns true if successful or false if key was not found
    def modify(self, key, value):
        index = self._hash(key)
        initial_index = index

        while self._table[index] is not None:
            if self._table[index][0] == key:
                self._table[index] = (key, value)
                return True
            index = (index + 1) % self._capacity
            if index == initial_index:
                break

        return False

    #Remove function that accepts a key
    #Searches through the table for a matching key, removes it, adjusts size, and then rehashes the section
    #Returns true if successful, false if not
    def remove(self, key):
        index = self._hash(key)
        initial_index = index

        while self._table[index] is not None:
            if self._table[index][0] == key:
                self._table[index] = None
                self._size -= 1
                # Rehash elements in the same cluster to avoid breaking the chain
                next_index = (index + 1) % self._capacity
                while self._table[next_index] is not None:
                    rehash_key, rehash_val = self._table[next_index]
                    self._table[next_index] = None
                    self._size -= 1
                    self.insert(rehash_key, rehash_val)
                    next_index = (next_index + 1) % self._capacity
                return True
            index = (index + 1) % self._capacity
            if index == initial_index:
                break

        return False

    #Resizes the current table
    #Doubles the capacity of the table, resets the size, remakes the table with the new capacity, and copies the old table into the new.
    #Does not return anything
    def _resize(self):
        old_table = self._table
        self._capacity *= 2  # Double the capacity
        self._size = 0  # Reset size
        self._table = [None] * self._capacity  # Create a new table with the new capacity

        for item in old_table:
            if item is not None:
                self.insert(item[0], item[1])  # Reinsert the items into the new table






import math
def evaluate(start, end, g_n):
    return g_n + foo(start, end)
def foo(start, end):
    return math.sqrt((end.x - start.x)**2 + (end.y - start.y))

def IDAStar(start: Vertex, end: Vertex):
    threshold = foo(start, end)
    while True:
        stack = [start, 0, [start]]
        min_f = float('inf')

        while stack:
            n, g, p = stack.pop(0)

            f = evaluate(n, end, g)
            if f > threshold:
                min_f = min(f, min_f)
                continue
            if n == end:
                return g, p 
            
            for neighbor, weight in n.adjacencies:
                if neighbor not in p:
                    stack.append((neighbor, g + weight, p + [neighbor]))

        if min_f == float('inf'):
            return None
        threshold = min_f
