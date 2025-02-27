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
            
    
tree = Tree()
tree.add_child(101)
tree.add_child(10)
tree.add_child(101)
tree.add_child(10)
tree.add_child(5)
tree.add_child(70)

"""
Added Data
Data already in tree...
Data already in tree...
Added Data
Added Data

=== Code Execution Successful ===
"""

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
  
#github ver  (EHHHH WRONG)
def heapify2(a_node):
    '''Creates a max heapified version of a binary tree.'''
    if a_node.children:
        largest_child = (max(a_node.children, key=lambda n: n.data))
        largest = (largest_child if largest_child.data > a_node.data else a_node)

        # If largest is not root, swap and continue heapifying
        if largest != a_node:
            # Swap data only, want to keep structure the same
            heapify(largest) # Sift it to the top
            a_node.data, largest.data = largest.data, a_node.data

        # Ensure all children are heapified as well
        for child in a_node.children:
            heapify(child)
        
"""
EX. where heapify2 fails:
        4
       / \
      2   3
     /\    \
    1 10    7
    
   TLDR: 
    - because 2 and 3 are smaller than 4, 4 never gets 
    swapped so it always ends up at the top, but if we 
    heapify the children first, 10 will switch with 4 since its bigger 
    SO TLDR:
        -> HEAPIFY CHILDREN FIRST 
"""


if __name__ == "__main__":
    tree = Binary_Tree(4)
    tree.add_node(2)
    tree.add_node(3)
    tree.add_node(1)
    tree.add_node(10)
    tree.display()
    
    print("---------------------------------------")
    print("GitHub ver:")
    heapify2(tree)
    tree.display()
    
    print("---------------------------------------")
    print("My ver:")
    heapify(tree)
    tree.display()

"""
4
├── 2
├── ├── 1
├── └── 10
└── 3
---------------------------------------
GitHub ver:
4
├── 10
├── ├── 1
├── └── 2
└── 3
---------------------------------------
My ver:
10
├── 4
├── ├── 1
├── └── 2
└── 3
"""


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

            
            
            
            
if __name__ == "__main__":
    bst = BST(6)
    bst.insert(7)
    bst.insert(10)
    bst.insert(1)
    bst.insert(3)
    bst.insert(-4)
    bst.insert(19)

    bst.print_tree("")

    print(f"Is 10 in the our BST? {bst.search(10)}")
    print(f"Is -1 in the our BST? {bst.search(-1)}")

    bst.remove(3)
    bst.print_tree("")

    print("Printing the BST with breadth first...")
    bst.breadth_first_print()
    print()

    print("Printing the BST in order...")
    bst.in_order()
    print()

    print("Printing the BST pre-ordered...")
    bst.pre_order()
    print()

    print(f"The height (max depth) of this tree is: {bst.find_height()}")
            
            
"""
|---6
    |__1
    |   |__-4
    |   |---3
    |---7
        |---10
            |---19
Is 10 in the our BST? True
Is -1 in the our BST? False
|---6
    |---7
        |---10
            |---19
Printing the BST with breadth first...
6 7 10 19 
Printing the BST in order...
6 7 10 19 
Printing the BST pre-ordered...
6 7 10 19 
The height (max depth) of this tree is: 4
"""            




""" 
ISSUE CODE:
class Node:
    def __init__(self, data):
        self.data = data
        self.children = [] # Cannot be more than two elements

    def add_node(self, data):
        if len(self.children) < 2:
            self.children.append(Node(data))
            self.children.sort(key=lambda n: n.data) # Just so they're in order
        else:
            if data < self.children[0].data:
                self.children[0].add_node(data)
            elif data > self.children[1].data:
                self.children[1].add_node(data)
            else:
                return # do nothing as the node already exists in the tree

    def display(self, level=0, prefix=""):
        # Print the current node with prefix for the connection
        print(prefix + f"{self.data}")
        
        # Prepare the prefix for children
        if self.children:
            # Set the prefix for the first child
            child_prefix = prefix + "    "
            
            # Iterate through children
            for child in self.children:
                child_prefix = prefix + "|  "
                child.display(level + 1, child_prefix)

class BinaryTree:
    def __init__(self, data):
        self.root = Node(data)

    def add_node(self, data):
        self.root.add_node(data)

    def display(self):
        self.root.display()

    #TODO: Add height calculation
    


def heapify(a_node):
    '''Creates a max heapified version of a binary tree.'''
    if a_node.children:
        largest_child = (max(a_node.children, key=lambda n: n.data))
        largest = (largest_child if largest_child.data > a_node.data else a_node)

        # If largest is not root, swap and continue heapifying
        if largest != a_node:
            # Swap data only, want to keep structure the same
            heapify(largest) # Sift it to the top
            a_node.data, largest.data = largest.data, a_node.data

        # Ensure all children are heapified as well
        for child in a_node.children:
            heapify(child)


if __name__ == "__main__":
    tree = BinaryTree(4)
    tree.add_node(2)
    tree.add_node(3)
    tree.add_node(1)
    tree.add_node(10)
    tree.add_node(7)
    
    
    tree.display()
    print("---------------------------------------")

    heapify(tree.root)
    tree.display()



"""



