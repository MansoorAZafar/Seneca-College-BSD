#    Main Author(s): 
#    Main Reviewer(s):



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

	def is_empty(self):
		return self.size == 0

	def __len__(self):
		return self.size


class Queue:


	def __init__(self, cap = 10):
		self.cap = cap
		self.size = 0
		self.queue = [None] * cap

		self.front = 0
		# Used to keep track of the current index for circular queue
		self.index = 0
	

	def capacity(self):
		return self.cap

	def enqueue(self, data):
		if self.size == self.cap:
			self.__resize()

		self.queue[self.index] = data
		self.index = (self.index + 1) % self.cap
		self.size += 1
	
	def __resize(self):
		self.cap *= 2
		new_queue = [None] * self.cap
		
		for i in range(self.size):
			new_queue[i] = self.queue[(self.front + i) % self.size]

		self.queue = new_queue
		# Front is moved to 0th index
		self.front = 0
		# Coninue from the end
		self.index = self.size
		
	
	def dequeue(self):
		if self.is_empty():
			raise IndexError("dequeue() used on empty queue")

		data = self.queue[self.front]
		# Keep front within range
		self.front = (self.front + 1) % self.cap
		self.size -= 1
		
		return data

	def get_front(self):
		return self.queue[self.front]

	def is_empty(self):
		return self.size == 0

	def __len__(self):
		return self.size



class Deque:

	def __init__(self, cap = 10):
		self.cap = cap
		self.size = 0
		self.deque = [None] * cap

		self.front = 0
		self.back = 0

		# Front will go from the end of the queue to the back
		# Back will go from the start of the queue to the front
		# [back -> _ _ _ <- Front]

	def capacity(self):
		return self.cap

	def __resize(self):
		self.cap *= 2
		new_deque = [None] * self.cap

		for i in range(self.size):
			new_deque[i] = self.deque[(self.front + i) % self.size]

		self.deque = new_deque
		self.front = 0
		self.back = self.size
	
	def push_front(self, data):
		if self.size == self.cap:
			self.__resize()
	
		# We want front to start at the end
		self.front = (self.front - 1 + self.cap) % self.cap
		self.deque[self.front] = data
		self.size += 1
	
	def push_back(self, data):
		if self.size == self.cap:
			self.__resize()

		# We want back to start at the start
		# At the end, The back pointer will be 1 above the index 
		self.deque[self.back] = data
		self.back = (self.back + 1) % self.cap
		self.size += 1

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

		# Because back is 1 ahead, we move it back one
		self.back = (self.back - 1) % self.cap
		data = self.deque[self.back]

		self.deque[self.back] = None
		self.size -= 1
		return data

	def get_front(self):
		return self.deque[self.front]

	def get_back(self):
		# Back is 1 ahead of the back item
		# We ensure back is within range by moduling it
		return self.deque[(self.back - 1) % self.cap]

	def is_empty(self):
		return self.size == 0

	def __len__(self):
		return self.size

	def __getitem__(self, k):
		if k < 0 or k >= self.size:
			raise IndexError("Index out of range")
		# The start is considered the front not 0 
		# So the position of the item is relative to the front
		return self.deque[(self.front + k) % self.cap]