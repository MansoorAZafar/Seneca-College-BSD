class Stack:
    def __init__(self, cap = 10):
        self.cap = cap
        self.size = 0
        self.stack = [None] * cap

    def capacity(self):
        return self.cap
    
    def push(self, data):
        if self.size == self.cap:
            self.__resize()
        
        self.stack[self.size] = data
        self.size += 1
        
    def __resize(self):
        self.cap *= 2
        self.stack.extend([None] * self.size)

    def pop(self):
        if self.is_empty():
            raise IndexError("pop() used on empty stack")
        
        self.size -= 1
        return self.stack[self.size]
    
    def get_top(self):
        return self.stack[self.size - 1]
    
    def is_empty(self) -> bool:
        return self.size == 0
    
    def __len__(self):
        return self.size