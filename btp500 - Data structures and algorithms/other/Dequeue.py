class Deque:
    def __init__(self, cap = 10):
        self.cap = cap
        self.size = 0

        self.deque = [None] * self.cap
        
        self.front = 0
        self.back = 0

    def capacity(self):
        return self.cap
    
    def push_front(self, data):
        if self.size == self.cap:
            self.__resize()

        # [... _ _ _ _ <- x]
        self.front = (self.front - 1) % self.cap
        self.deque[self.front] = data

        self.size += 1

    def push_back(self, data):
        if self.size == self.cap:
            self.__resize()

        # [x -> _ _ _ _ ...]
        self.deque[self.back] = data
        self.back = (self.back + 1) % self.cap
        
        self.size += 1

    def __resize(self):
        self.cap *= 2
        temporary_deque = [None] * self.cap

        for i in range(self.size):
            temporary_deque[i] = self.deque[(self.front + i) % self.size]

        self.deque = temporary_deque
        self.front = 0
        self.back = self.size

    def pop_front(self):
        if self.is_empty():
            raise IndexError("pop_front() used on empty deque")
        
        data = self.deque[self.front]
        self.deque[self.front] = None 
        self.front = (self.front + 1) % self.cap

        self.size -= 1
        return data
    
    def pop_back(self):
        if self.is_empty():
            raise IndexError("pop_back() used on empty deque")

        self.back = (self.back - 1) % self.cap
        data = self.deque[self.back]
        self.deque[self.back] = None


        self.size -= 1
        return data

    
    def get_front(self):
        return self.deque[self.front]
    
    def get_back(self):
        return self.deque[(self.back - 1) % self.cap]
    
    def is_empty(self):
        return self.size == 0
    
    def __len__(self):
        return self.size
    
    def __getitem__(self, k):
        if k < 0 or k >= self.size:
            raise IndexError("Index out of range")
        
        return self.deque[(self.front + k) % self.cap]
