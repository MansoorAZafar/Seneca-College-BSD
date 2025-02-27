class DoublyLinked:

    class Node:
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

    def __init__(self, data = None):
        self.head = self.Node(data) if data else None 
        self.tail = self.head

    def get_front(self):
        return self.head

    def get_back(self):
        return self.tail 

    def push_front(self, data):
        if not data: 
            return

        if not self.head:
            self.head = self.Node(data)
            self.tail = self.head 
        else:
            new_front = self.Node(data)
            new_front.next = self.head 
            self.head.prev = new_front
            self.head = new_front 

    def push_back(self, data):
        if not data:
            return 

        if not self.head:
            self.head = self.Node(data)
            self.tail = self.head 
        else:
            new_back = self.Node(data)
            new_back.prev = self.tail 
            self.tail.next = new_back 
            self.tail = new_back

    def pop_front(self):
        if not self.head:
            raise IndexError("pop_front() used on empty list")

        popped_value = self.head.get_data()
        
        new_front = self.head.next
        if new_front:
            new_front.prev = None 
        
        if self.head == self.tail:
            self.tail = new_front

        self.head.next = None
        self.head = new_front

        return popped_value

    def pop_back(self):
        if not self.tail:
            raise IndexError("pop_back() used on empty list")

        popped_value = self.tail.get_data()
        
        new_back = self.tail.prev 
        if new_back:
            new_back.next = None 
        
        if self.tail == self.head:
            self.head = new_back
        
        self.tail.prev = None 
        self.tail = new_back

        return popped_value


class Sentinel:

	class Node:
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

	def __init__(self, data = None):
		self.head = self.Node(None)
		self.tail = self.head

		if data:
			node = self.Node(data)
			node.prev = self.head 
			node.next = self.tail

			self.head.next = node
			self.tail.prev = node 
		else:
			self.head.next = self.tail
			self.tail.prev = self.head

	def get_front(self):
		return None if self.head.next == self.tail else self.head.next

	def get_back(self):
		return None if self.tail.prev == self.head else self.tail.prev

	def push_front(self, data):
		if not data:
			return

		new_front = self.Node(data)
		new_front.next = self.head.next
		new_front.prev = self.head

		self.head.next.prev = new_front
		self.head.next = new_front

	def push_back(self,data):
		if not data:
			return

		new_back = self.Node(data)
		new_back.prev = self.tail.prev
		new_back.next = self.tail

		self.tail.prev.next = new_back
		self.tail.prev = new_back

	def pop_front(self):
		if self.head.next == self.tail:
			raise IndexError("pop_front() used on empty list")

		popped_value = self.head.next.get_data()

		#This will either be the tail or the one next to the one next to the head
		new_front = self.head.next.next 
		if new_front:
			new_front.prev = self.head
		if new_front == self.tail:
			self.tail.prev = self.head

		self.head.next = new_front
		return popped_value

	def pop_back(self):
		if self.tail.prev == self.head:
			raise IndexError("pop_back() used on empty list")		

		popped_value = self.tail.prev.get_data()

		#This will either be the head or the one previous to previous to the tail
		new_back = self.tail.prev.prev
		if new_back:
			new_back.next = self.tail

		if new_back == self.head:
			self.head.next = self.tail

		self.tail.prev = new_back
		return popped_value







