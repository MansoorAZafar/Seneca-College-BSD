class Tree:
    def __init__(self, data):
        self.data = data
        self.children = []
    
    def add_node(self, data):
        if not self.data:
            self.data
        elif not any(filter(lambda x: x.data == data, self.children)) and self.data != data:
            self.children.append(Tree(data))
            self.children.sort(key=lambda x: x.data)

class Binary_Tree:
    def __init__(self, data):
        self.data = data
        self.children = []
    
    def add_node(self, data):
        que = [self]

        while que:
            curr = que.pop(0)

            if len(curr.children) < 2:
                curr.children.append(Binary_Tree(data))
                curr.children.sort(key=lambda x: x.data)
                que.clear()                
            else:
                que.extend(curr.children)

class Binary_Search_Tree:
    def __init__(self, data=None):
        self.data = data
        self.left = None
        self.right = None
    
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

            successor = self.right.find_min()
            self.data = successor.data 
            self.right = self.right.remove(self.data)

        return self
    
    def insert(self, data):
        if not self.data:
            self.data = data
        elif data < self.data:
            if self.left:
                self.left.insert(data)
            else:
                self.left = Binary_Search_Tree(data)
        elif data > self.data:
            if self.right:
                self.right.insert(data)
            else:
                self.right = Binary_Search_Tree(data)

    def breadth_first_search(self):
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
    
    def search(self, data):
        if self.data:
            if self.data == data:
                return True
            elif self.data > data and self.left:
                return self.left.search(data)
            elif self.data < data and self.right:
                return self.right.search(data)
        
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
            print(self.data, end=" ")
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
            print(self.data, end=" ")

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

class Binary_Heap:
    def __init__(self):
        self.heap = []
    
    def insert(self, data):
        self.heap.append(data)
        self._bubble_up(len(self.heap) - 1)

    def _bubble_up(self, index):
        parent = (index - 1) // 2

        while index > 0 and self.heap[parent] < self.heap[index]:
            self.heap[index], self.heap[parent] = self.heap[parent], self.heap[index]

            index = parent
            parent = (index - 1) // 2

    def _bubble_down(self, index):
        length = len(self.heap)

        while True:
            left = 2*index + 1
            rght = 2*index + 2
            max_index = index 

            if left < length and self.heap[left] > self.heap[max_index]:
                max_index = left
            if rght < length and self.heap[rght] > self.heap[max_index]:
                max_index = rght

            if index == max_index:
                break

            self.heap[max_index], self.heap[index] = self.heap[index], self.heap[max_index]
            index = max_index

    def remove_max(self):
        if not self.heap:
            return 

        max_value = self.heap[0]
        last_value = self.heap.pop()

        if self.heap:
            self.heap[0] = last_value
            self._bubble_down(0)

        return max_value

    
def heapify(a_node):
    if a_node.children:
        for child in a_node.children:
            heapify(child)
        
        largest_child = max(a_node.children, key=lambda x: x.data)
        if largest_child.data > a_node.data:
            a_node.data, largest_child.data = largest_child.data, a_node.data
            heapify(largest_child)
        

def heapify_BST(a_node):
    if a_node.left:
        heapify_BST(a_node.left)
    if a_node.right:
        heapify_BST(a_node.right)
    
    max_n = a_node
    if a_node.left:
        max_n = max_n if max_n.data > a_node.left.data else a_node.left
    if a_node.right:
        max_n = max_n if max_n.data > a_node.right.data else a_node.right
    
    if max_n.data > a_node.data:
        max_n.data, a_node.data = a_node.data, max_n.data
        heapify_BST(max_n)