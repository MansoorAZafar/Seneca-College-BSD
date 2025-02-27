from test import Queue
import unittest

class A1CTestCase(unittest.TestCase):
	def test_queue_init(self):
		the_queue = Queue()
		self.assertEqual(len(the_queue), 0)
		self.assertEqual(the_queue.is_empty(), True)
		self.assertEqual(the_queue.get_front(), None)
		self.assertEqual(the_queue.capacity(), 10)


		second_queue = Queue(8)
		self.assertEqual(len(second_queue), 0)
		self.assertEqual(second_queue.is_empty(), True)
		self.assertEqual(second_queue.get_front(), None)
		self.assertEqual(second_queue.capacity(), 8)


	def test_queue_enqueue(self):
		the_queue = Queue(5)
		self.assertEqual(the_queue.capacity(), 5)
		the_queue.enqueue(1)
		self.assertEqual(the_queue.is_empty(), False)
		self.assertEqual(len(the_queue), 1)
		self.assertEqual(the_queue.get_front(), 1)

		the_queue.enqueue(5)
		self.assertEqual(the_queue.capacity(), 5)
		self.assertEqual(the_queue.is_empty(), False)
		self.assertEqual(len(the_queue), 2)
		self.assertEqual(the_queue.get_front(), 1)

		the_queue.enqueue(10)
		self.assertEqual(the_queue.capacity(), 5)
		self.assertEqual(the_queue.is_empty(), False)
		self.assertEqual(len(the_queue), 3)
		self.assertEqual(the_queue.get_front(), 1)

		the_queue.enqueue(8)
		self.assertEqual(the_queue.capacity(), 5)
		self.assertEqual(the_queue.is_empty(), False)
		self.assertEqual(len(the_queue), 4)
		self.assertEqual(the_queue.get_front(), 1)

		for i in range(1000):
			the_queue.enqueue(i)
			self.assertEqual(the_queue.is_empty(), False)
		self.assertEqual(len(the_queue), 1004)
		self.assertEqual(the_queue.get_front(), 1)
		self.assertEqual(the_queue.capacity(), 1280)


	def test_queue_dequeue(self):
		the_queue = Queue(5)
		the_queue.enqueue(1)
		the_queue.enqueue(5)
		the_queue.enqueue(10)
		the_queue.enqueue(8)

		rc = the_queue.dequeue()
		self.assertEqual(the_queue.is_empty(), False)
		self.assertEqual(len(the_queue), 3)
		self.assertEqual(the_queue.get_front(), 5)
		self.assertEqual(rc, 1)
		self.assertEqual(the_queue.capacity(), 5)


		rc = the_queue.dequeue()
		self.assertEqual(the_queue.is_empty(), False)
		self.assertEqual(len(the_queue), 2)
		self.assertEqual(the_queue.get_front(), 10)
		self.assertEqual(rc, 5)
		self.assertEqual(the_queue.capacity(), 5)


		rc = the_queue.dequeue()
		self.assertEqual(the_queue.is_empty(), False)
		self.assertEqual(len(the_queue), 1)
		self.assertEqual(the_queue.get_front(), 8)
		self.assertEqual(rc, 10)
		self.assertEqual(the_queue.capacity(), 5)

		rc = the_queue.dequeue()
		self.assertEqual(the_queue.is_empty(), True)
		self.assertEqual(len(the_queue), 0)
		self.assertEqual(the_queue.get_front(), None)
		self.assertEqual(rc, 8)
		self.assertEqual(the_queue.capacity(), 5)


		with self.assertRaises(IndexError) as cm:
			rc = the_queue.dequeue()
		self.assertEqual(str(cm.exception), 'dequeue() used on empty queue')


	def test_queue_resizing(self):
		the_queue = Queue(2)

		self.assertEqual(the_queue.capacity(), 2)

		the_queue.enqueue(1)
		the_queue.enqueue(5)
		self.assertEqual(the_queue.capacity(), 2)

		the_queue.enqueue(10)
		self.assertEqual(the_queue.capacity(), 4)
		the_queue.enqueue(8)
		self.assertEqual(the_queue.capacity(), 4)

		rc = the_queue.dequeue()
		self.assertEqual(the_queue.is_empty(), False)
		self.assertEqual(len(the_queue), 3)
		self.assertEqual(the_queue.get_front(), 5)
		self.assertEqual(rc, 1)
		self.assertEqual(the_queue.capacity(), 4)


		rc = the_queue.dequeue()
		self.assertEqual(the_queue.is_empty(), False)
		self.assertEqual(len(the_queue), 2)
		self.assertEqual(the_queue.get_front(), 10)
		self.assertEqual(rc, 5)
		self.assertEqual(the_queue.capacity(), 4)


		the_queue.enqueue(23)
		self.assertEqual(the_queue.is_empty(), False)
		self.assertEqual(len(the_queue), 3)
		self.assertEqual(the_queue.get_front(), 10)
		self.assertEqual(the_queue.capacity(), 4)


		the_queue.enqueue(52)
		self.assertEqual(the_queue.is_empty(), False)
		self.assertEqual(len(the_queue), 4)
		self.assertEqual(the_queue.get_front(), 10)
		self.assertEqual(the_queue.capacity(), 4)



		the_queue.enqueue(55)
		self.assertEqual(the_queue.is_empty(), False)
		self.assertEqual(len(the_queue), 5)
		self.assertEqual(the_queue.get_front(), 10)
		self.assertEqual(the_queue.capacity(), 8)


		the_queue.enqueue(1)
		self.assertEqual(the_queue.is_empty(), False)
		self.assertEqual(len(the_queue), 6)
		self.assertEqual(the_queue.get_front(), 10)
		self.assertEqual(the_queue.capacity(), 8)


		rc = the_queue.dequeue()
		self.assertEqual(the_queue.is_empty(), False)
		self.assertEqual(len(the_queue), 5)
		self.assertEqual(the_queue.get_front(), 8)
		self.assertEqual(rc, 10)
		self.assertEqual(the_queue.capacity(), 8)


		rc = the_queue.dequeue()
		self.assertEqual(the_queue.is_empty(), False)
		self.assertEqual(len(the_queue), 4)
		self.assertEqual(the_queue.get_front(), 23)
		self.assertEqual(rc, 8)
		self.assertEqual(the_queue.capacity(), 8)


		rc = the_queue.dequeue()
		self.assertEqual(the_queue.is_empty(), False)
		self.assertEqual(len(the_queue), 3)
		self.assertEqual(the_queue.get_front(), 52)
		self.assertEqual(rc, 23)
		self.assertEqual(the_queue.capacity(), 8)


		rc = the_queue.dequeue()
		self.assertEqual(the_queue.is_empty(), False)
		self.assertEqual(len(the_queue), 2)
		self.assertEqual(the_queue.get_front(), 55)
		self.assertEqual(rc, 52)
		self.assertEqual(the_queue.capacity(), 8)


		rc = the_queue.dequeue()
		self.assertEqual(the_queue.is_empty(), False)
		self.assertEqual(len(the_queue), 1)
		self.assertEqual(the_queue.get_front(), 1)
		self.assertEqual(rc, 55)
		self.assertEqual(the_queue.capacity(), 8)

		curr_len = 1
		curr_cap = 8
		for i in range(2,1000):
			the_queue.enqueue(i)
			curr_len += 1
			self.assertEqual(the_queue.is_empty(), False)
			self.assertEqual(len(the_queue), curr_len)
			self.assertEqual(the_queue.get_front(), 1)
			self.assertEqual(the_queue.capacity(), curr_cap)
			if curr_len == curr_cap:
				curr_cap = curr_cap * 2

		for i in range(1,999):
			rc = the_queue.dequeue()
			self.assertEqual(rc, i)
			curr_len -= 1
			self.assertEqual(the_queue.is_empty(), False)
			self.assertEqual(len(the_queue), curr_len)
			self.assertEqual(the_queue.get_front(), i + 1)
			self.assertEqual(the_queue.capacity(), curr_cap)

		rc = the_queue.dequeue()
		self.assertEqual(rc, 999)
		self.assertEqual(the_queue.is_empty(), True)
		self.assertEqual(len(the_queue), 0)
		self.assertEqual(the_queue.get_front(), None)
		self.assertEqual(the_queue.capacity(), curr_cap)

if __name__ == "__main__":
	  unittest.main()