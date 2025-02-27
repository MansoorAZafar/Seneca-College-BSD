class Queue:
    def __init__(self, cap = 10):
        self.cap   = cap
        self.size  = 0
        self.queue = [None] * cap

        self.front = 0
        self.index = 0 #Used to keep track of the index for a circular queue

    def capacity(self):
        return self.cap
    
    def enqueue(self, data):
        if self.size == self.cap:
            self.__resize()

        self.queue[self.index] = data
        #If there are open spaces at the front, we will loop back
        # Looping back will only happen if open spaces because size < cap
        self.index = (self.index + 1) % self.cap 
        self.size += 1

    def __resize(self):
        self.cap *= 2
        temporary_queue = [None] * self.cap
        for i in range(self.size):
            temporary_queue[i] = self.queue[(self.front + i) % self.size]

        self.queue = temporary_queue

        #Front is moved back to 0th index
        self.front = 0
        #Index pointer is now adding to the end
        self.index = self.size

    def dequeue(self):
        if self.is_empty():
            raise IndexError("dequeue() used on empty queue")

        data = self.queue[self.front]
        self.front = (self.front + 1) % self.cap
        self.size -= 1

        return data

    def get_front(self):
        return self.queue[self.front]
    
    def is_empty(self):
        return self.size == 0
    
    def __len__(self):
        return self.size
