from test import Deque
import unittest

class A1CTestCase(unittest.TestCase):
    def test_deque_init(self):
        the_deque = Deque()
        self.assertEqual(len(the_deque), 0)
        self.assertEqual(the_deque.is_empty(), True)
        self.assertEqual(the_deque.get_front(), None)
        self.assertEqual(the_deque.get_back(), None)
        self.assertEqual(the_deque.capacity(), 10)

        second_deque = Deque(25)
        self.assertEqual(len(second_deque), 0)
        self.assertEqual(second_deque.is_empty(), True)
        self.assertEqual(second_deque.get_front(), None)
        self.assertEqual(second_deque.get_back(), None)
        self.assertEqual(second_deque.capacity(), 25)


    def test_deque_push_front(self):
        the_deque = Deque(5)
        the_deque.push_front(1)
        self.assertEqual(the_deque.capacity(), 5)
        self.assertEqual(the_deque.is_empty(), False)
        self.assertEqual(len(the_deque), 1)
        self.assertEqual(the_deque.get_front(), 1)
        self.assertEqual(the_deque.get_back(), 1)

        the_deque.push_front(5)
        self.assertEqual(the_deque.capacity(), 5)
        self.assertEqual(the_deque.is_empty(), False)
        self.assertEqual(len(the_deque), 2)
        self.assertEqual(the_deque.get_front(), 5)
        self.assertEqual(the_deque.get_back(), 1)

        the_deque.push_front(10)
        self.assertEqual(the_deque.capacity(), 5)
        self.assertEqual(the_deque.is_empty(), False)
        self.assertEqual(len(the_deque), 3)
        self.assertEqual(the_deque.get_front(), 10)
        self.assertEqual(the_deque.get_back(), 1)

        the_deque.push_front(8)
        self.assertEqual(the_deque.capacity(), 5)
        self.assertEqual(the_deque.is_empty(), False)
        self.assertEqual(len(the_deque), 4)
        self.assertEqual(the_deque.get_front(), 8)
        self.assertEqual(the_deque.get_back(), 1)

        for i in range(1000):
            the_deque.push_front(i)
            self.assertEqual(the_deque.is_empty(), False)
            self.assertEqual(the_deque.get_front(), i)
            self.assertEqual(the_deque.get_back(), 1)

        self.assertEqual(len(the_deque), 1004)
        self.assertEqual(the_deque.capacity(), 1280)


    def test_deque_push_back(self):
        the_deque = Deque(5)
        the_deque.push_back(1)
        self.assertEqual(the_deque.capacity(), 5)
        self.assertEqual(the_deque.is_empty(), False)
        self.assertEqual(len(the_deque), 1)
        self.assertEqual(the_deque.get_front(), 1)
        self.assertEqual(the_deque.get_back(), 1)

        the_deque.push_back(5)
        self.assertEqual(the_deque.capacity(), 5)
        self.assertEqual(the_deque.is_empty(), False)
        self.assertEqual(len(the_deque), 2)
        self.assertEqual(the_deque.get_back(), 5)
        self.assertEqual(the_deque.get_front(), 1)

        the_deque.push_back(10)
        self.assertEqual(the_deque.capacity(), 5)
        self.assertEqual(the_deque.is_empty(), False)
        self.assertEqual(len(the_deque), 3)
        self.assertEqual(the_deque.get_front(), 1)
        self.assertEqual(the_deque.get_back(), 10)

        the_deque.push_back(8)
        self.assertEqual(the_deque.capacity(), 5)
        self.assertEqual(the_deque.is_empty(), False)
        self.assertEqual(len(the_deque), 4)
        self.assertEqual(the_deque.get_front(), 1)
        self.assertEqual(the_deque.get_back(), 8)

        for i in range(1000):
            the_deque.push_back(i)
            self.assertEqual(the_deque.is_empty(), False)
            self.assertEqual(the_deque.get_back(), i)
            self.assertEqual(the_deque.get_front(), 1)

        self.assertEqual(len(the_deque), 1004)
        self.assertEqual(the_deque.capacity(), 1280)


    def test_deque_pop_front(self):

        the_deque = Deque(5)
        the_deque.push_front(1)
        the_deque.push_back(5)
        the_deque.push_front(10)
        the_deque.push_back(8)

        rc = the_deque.pop_front()
        self.assertEqual(the_deque.capacity(), 5)
        self.assertEqual(the_deque.is_empty(), False)
        self.assertEqual(len(the_deque), 3)
        self.assertEqual(the_deque.get_front(), 1)
        self.assertEqual(the_deque.get_back(), 8)
        self.assertEqual(rc, 10)

        rc = the_deque.pop_front()
        self.assertEqual(the_deque.capacity(), 5)
        self.assertEqual(the_deque.is_empty(), False)
        self.assertEqual(len(the_deque), 2)
        self.assertEqual(the_deque.get_front(), 5)
        self.assertEqual(the_deque.get_back(), 8)
        self.assertEqual(rc, 1)

        rc = the_deque.pop_front()
        self.assertEqual(the_deque.capacity(), 5)
        self.assertEqual(the_deque.is_empty(), False)
        self.assertEqual(len(the_deque), 1)
        self.assertEqual(the_deque.get_front(), 8)
        self.assertEqual(the_deque.get_back(), 8)
        self.assertEqual(rc, 5)

        rc = the_deque.pop_front()
        self.assertEqual(the_deque.capacity(), 5)
        self.assertEqual(the_deque.is_empty(), True)
        self.assertEqual(len(the_deque), 0)
        self.assertEqual(the_deque.get_front(), None)
        self.assertEqual(the_deque.get_back(), None)
        self.assertEqual(rc, 8)
        with self.assertRaises(IndexError) as cm:
            rc = the_deque.pop_front()
        self.assertEqual(str(cm.exception), 'pop_front() used on empty deque')


    def test_deque_pop_back(self):
        the_deque = Deque(5)
        the_deque.push_front(1)
        the_deque.push_back(5)
        the_deque.push_front(10)
        the_deque.push_back(8)

        rc = the_deque.pop_back()
        self.assertEqual(the_deque.capacity(), 5)
        self.assertEqual(the_deque.is_empty(), False)
        self.assertEqual(len(the_deque), 3)
        self.assertEqual(the_deque.get_front(), 10)
        self.assertEqual(the_deque.get_back(), 5)
        self.assertEqual(rc, 8)

        rc = the_deque.pop_back()
        self.assertEqual(the_deque.capacity(), 5)
        self.assertEqual(the_deque.is_empty(), False)
        self.assertEqual(len(the_deque), 2)
        self.assertEqual(the_deque.get_front(), 10)
        self.assertEqual(the_deque.get_back(), 1)
        self.assertEqual(rc, 5)

        rc = the_deque.pop_back()
        self.assertEqual(the_deque.capacity(), 5)
        self.assertEqual(the_deque.is_empty(), False)
        self.assertEqual(len(the_deque), 1)
        self.assertEqual(the_deque.get_front(), 10)
        self.assertEqual(the_deque.get_back(), 10)
        self.assertEqual(rc, 1)

        rc = the_deque.pop_back()
        self.assertEqual(the_deque.capacity(), 5)
        self.assertEqual(the_deque.is_empty(), True)
        self.assertEqual(len(the_deque), 0)
        self.assertEqual(the_deque.get_front(), None)
        self.assertEqual(the_deque.get_back(), None)
        self.assertEqual(rc, 10)
        with self.assertRaises(IndexError) as cm:
            rc = the_deque.pop_back()
        self.assertEqual(str(cm.exception), 'pop_back() used on empty deque')


    def test_deque_resize(self):

        the_deque = Deque(2)
        self.assertEqual(the_deque.capacity(), 2)

        the_deque.push_back(1)
        the_deque.push_back(5)
        self.assertEqual(the_deque.capacity(), 2)

        the_deque.push_back(10)
        self.assertEqual(the_deque.capacity(), 4)
        the_deque.push_back(8)
        self.assertEqual(the_deque.capacity(), 4)

        rc = the_deque.pop_front()
        self.assertEqual(the_deque.is_empty(), False)
        self.assertEqual(len(the_deque), 3)
        self.assertEqual(the_deque.get_front(), 5)
        self.assertEqual(the_deque.get_back(), 8)
        self.assertEqual(rc, 1)
        self.assertEqual(the_deque.capacity(), 4)


        rc = the_deque.pop_front()
        self.assertEqual(the_deque.is_empty(), False)
        self.assertEqual(len(the_deque), 2)
        self.assertEqual(the_deque.get_front(), 10)
        self.assertEqual(the_deque.get_back(), 8)
        self.assertEqual(rc, 5)
        self.assertEqual(the_deque.capacity(), 4)


        the_deque.push_back(23)
        self.assertEqual(the_deque.is_empty(), False)
        self.assertEqual(len(the_deque), 3)
        self.assertEqual(the_deque.get_back(), 23)
        self.assertEqual(the_deque.get_front(), 10)
        self.assertEqual(the_deque.capacity(), 4)


        the_deque.push_back(52)
        self.assertEqual(the_deque.is_empty(), False)
        self.assertEqual(len(the_deque), 4)
        self.assertEqual(the_deque.get_back(), 52)
        self.assertEqual(the_deque.get_front(), 10)
        self.assertEqual(the_deque.capacity(), 4)



        the_deque.push_back(55)
        self.assertEqual(the_deque.is_empty(), False)
        self.assertEqual(len(the_deque), 5)
        self.assertEqual(the_deque.get_front(), 10)
        self.assertEqual(the_deque.get_back(), 55)
        self.assertEqual(the_deque.capacity(), 8)

        the_deque.push_front(63)
        self.assertEqual(the_deque.is_empty(), False)
        self.assertEqual(len(the_deque), 6)
        self.assertEqual(the_deque.get_front(), 63)
        self.assertEqual(the_deque.get_back(), 55)
        self.assertEqual(the_deque.capacity(), 8)

        the_deque.push_back(1)
        self.assertEqual(the_deque.is_empty(), False)
        self.assertEqual(len(the_deque), 7)
        self.assertEqual(the_deque.get_front(), 63)
        self.assertEqual(the_deque.capacity(), 8)
        self.assertEqual(the_deque.get_back(), 1)

        the_deque.push_back(35)
        self.assertEqual(the_deque.is_empty(), False)
        self.assertEqual(len(the_deque), 8)
        self.assertEqual(the_deque.get_front(), 63)
        self.assertEqual(the_deque.capacity(), 8)
        self.assertEqual(the_deque.get_back(), 35)


        rc = the_deque.pop_front()
        self.assertEqual(the_deque.is_empty(), False)
        self.assertEqual(len(the_deque), 7)
        self.assertEqual(the_deque.get_front(), 10)
        self.assertEqual(the_deque.get_back(), 35)
        self.assertEqual(rc, 63)
        self.assertEqual(the_deque.capacity(), 8)


        rc = the_deque.pop_front()
        self.assertEqual(the_deque.is_empty(), False)
        self.assertEqual(len(the_deque), 6)
        self.assertEqual(the_deque.get_back(), 35)
        self.assertEqual(the_deque.get_front(), 8)
        self.assertEqual(rc, 10)
        self.assertEqual(the_deque.capacity(), 8)


        rc = the_deque.pop_back()
        self.assertEqual(the_deque.is_empty(), False)
        self.assertEqual(len(the_deque), 5)
        self.assertEqual(the_deque.get_front(), 8)
        self.assertEqual(the_deque.get_back(), 1)
        self.assertEqual(rc, 35)
        self.assertEqual(the_deque.capacity(), 8)



        the_deque.push_front(16)
        self.assertEqual(the_deque.is_empty(), False)
        self.assertEqual(len(the_deque), 6)
        self.assertEqual(the_deque.get_front(), 16)
        self.assertEqual(the_deque.get_back(), 1)
        self.assertEqual(the_deque.capacity(), 8)


        the_deque.push_front(17)
        self.assertEqual(the_deque.is_empty(), False)
        self.assertEqual(len(the_deque), 7)
        self.assertEqual(the_deque.get_front(), 17)
        self.assertEqual(the_deque.capacity(), 8)
        self.assertEqual(the_deque.get_back(), 1)


        the_deque.push_back(18)
        self.assertEqual(the_deque.is_empty(), False)
        self.assertEqual(len(the_deque), 8)
        self.assertEqual(the_deque.get_front(), 17)
        self.assertEqual(the_deque.get_back(), 18)
        self.assertEqual(the_deque.capacity(), 8)


        the_deque.push_front(19)
        self.assertEqual(the_deque.is_empty(), False)
        self.assertEqual(len(the_deque), 9)
        self.assertEqual(the_deque.get_front(), 19)
        self.assertEqual(the_deque.capacity(), 16)
        self.assertEqual(the_deque.get_back(), 18)


        rc = the_deque.pop_front()
        self.assertEqual(the_deque.is_empty(), False)
        self.assertEqual(len(the_deque), 8)
        self.assertEqual(the_deque.get_front(), 17)
        self.assertEqual(the_deque.get_back(), 18)
        self.assertEqual(rc, 19)
        self.assertEqual(the_deque.capacity(), 16)


        rc = the_deque.pop_front()
        self.assertEqual(the_deque.is_empty(), False)
        self.assertEqual(len(the_deque), 7)
        self.assertEqual(the_deque.get_front(), 16)
        self.assertEqual(the_deque.get_back(), 18)
        self.assertEqual(rc, 17)
        self.assertEqual(the_deque.capacity(), 16)


        rc = the_deque.pop_front()
        self.assertEqual(the_deque.is_empty(), False)
        self.assertEqual(len(the_deque), 6)
        self.assertEqual(the_deque.get_front(), 8)
        self.assertEqual(the_deque.get_back(), 18)
        self.assertEqual(rc, 16)
        self.assertEqual(the_deque.capacity(), 16)


        rc = the_deque.pop_front()
        self.assertEqual(the_deque.is_empty(), False)
        self.assertEqual(len(the_deque), 5)
        self.assertEqual(the_deque.get_front(), 23)
        self.assertEqual(the_deque.get_back(), 18)
        self.assertEqual(rc, 8)
        self.assertEqual(the_deque.capacity(), 16)


        rc = the_deque.pop_front()
        self.assertEqual(the_deque.is_empty(), False)
        self.assertEqual(len(the_deque), 4)
        self.assertEqual(the_deque.get_front(), 52)
        self.assertEqual(the_deque.get_back(), 18)
        self.assertEqual(rc, 23)
        self.assertEqual(the_deque.capacity(), 16)


        rc = the_deque.pop_front()
        self.assertEqual(the_deque.is_empty(), False)
        self.assertEqual(len(the_deque), 3)
        self.assertEqual(the_deque.get_front(), 55)
        self.assertEqual(the_deque.get_back(), 18)
        self.assertEqual(rc, 52)
        self.assertEqual(the_deque.capacity(), 16)

        rc = the_deque.pop_back()
        self.assertEqual(the_deque.is_empty(), False)
        self.assertEqual(len(the_deque), 2)
        self.assertEqual(the_deque.get_front(), 55)
        self.assertEqual(the_deque.get_back(), 1)
        self.assertEqual(rc, 18)
        self.assertEqual(the_deque.capacity(), 16)

        rc = the_deque.pop_front()
        self.assertEqual(the_deque.is_empty(), False)
        self.assertEqual(len(the_deque), 1)
        self.assertEqual(the_deque.get_front(), 1)
        self.assertEqual(the_deque.get_back(), 1)
        self.assertEqual(rc, 55)
        self.assertEqual(the_deque.capacity(), 16)


        curr_len = 1
        curr_cap = 16
        for i in range(2,1000):
            the_deque.push_back(i)
            curr_len += 1
            self.assertEqual(the_deque.is_empty(), False)
            self.assertEqual(len(the_deque), curr_len)
            self.assertEqual(the_deque.get_front(), 1)
            self.assertEqual(the_deque.get_back(), i)
            self.assertEqual(the_deque.capacity(), curr_cap)
            if curr_len == curr_cap:
                curr_cap = curr_cap * 2

        for i in range(1,999):
            rc = the_deque.pop_front()
            self.assertEqual(rc, i)
            curr_len -= 1
            self.assertEqual(the_deque.is_empty(), False)
            self.assertEqual(len(the_deque), curr_len)
            self.assertEqual(the_deque.get_front(), i+1)
            self.assertEqual(the_deque.get_back(), 999)
            self.assertEqual(the_deque.capacity(), curr_cap)

        rc = the_deque.pop_front()
        self.assertEqual(rc, 999)
        self.assertEqual(the_deque.is_empty(), True)
        self.assertEqual(len(the_deque), 0)
        self.assertEqual(the_deque.get_front(), None)
        self.assertEqual(the_deque.get_back(), None)
        self.assertEqual(the_deque.capacity(), curr_cap)


    def test_getitem(self):
        the_deque = Deque(5)
        the_deque.push_back(1)
        the_deque.push_front(15)
        the_deque.push_back(24)
        the_deque.push_front(31)
        the_deque.push_back(9)

        stored_data = [31,15, 1, 24, 9]

        for i in range(5):
            self.assertEqual(the_deque[i], stored_data[i])

        the_deque.pop_front()
        the_deque.pop_front()
        the_deque.push_back(23)
        the_deque.push_back(42)
        stored_data = [1,24,9,23,42]

        for i in range(5):
            self.assertEqual(the_deque[i], stored_data[i])



        with self.assertRaises(IndexError) as cm:
            rc = the_deque[5]
        self.assertEqual(str(cm.exception), 'Index out of range')

if __name__ == "__main__":
    unittest.main()