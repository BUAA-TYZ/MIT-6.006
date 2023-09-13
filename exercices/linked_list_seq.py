'This module provides a forward-list, which supports all basic operations of the list.'
import unittest

class LinkedListNode:
    'This is the node of forward-list.'
    def __init__(self, node_val) -> None:
        self.item = node_val
        self.next = None
    def later_node(self, i):
        'Return the i-th next node'
        if i == 0:
            return self
        assert i > 0
        return self.next.later_node(i - 1)
    def print(self):
        'print the value of node'
        print(self.item, end='')

class LinkedListSeq:
    'This is the forward-list, which implements the Seq interface.'
    def __init__(self) -> None:
        self.size = 0
        self.head = None
    def __len__(self):
        return self.size

    def __eq__(self, X):
        'For test'
        if self.size != len(X):
            return False
        for i in range(0, self.size):
            if self.get_at(i) != X[i]:
                return False
        return True

    def build(self, X):
        'Build the forward-list.'
        for i in X:
            self.insert_first(i)

    def get_at(self, i):
        'Get ith element in forward-list.'
        if i >= self.size:
            return None
        return self.head.later_node(i).item

    def set_at(self, i, new_val):
        'Set ith element to new value.'
        if i >= self.size:
            return
        self.head.later_node(i).item = new_val

    def insert_first(self, x):
        'Insert x at the head of list.'
        x = LinkedListNode(x)
        x.next = self.head
        self.head = x
        self.size += 1

    def delete_first(self):
        'Delete the head of list.'
        if self.size == 0:
            return
        self.head = self.head.next
        self.size -= 1

    def insert_last(self, x):
        'Insert at the tail of list.'
        if self.size == 0:
            self.insert_first(x)
            return
        x = LinkedListNode(x)
        self.head.later_node(self.size - 1).next = x
        self.size += 1

    def delete_last(self):
        'Delete the tail of list.'
        if self.size <= 1:
            self.delete_first()
            return
        self.head.later_node(self.size - 2).next = None
        self.size -= 1

    def insert_at(self, i, x):
        'Insert x at ith position of list.'
        if i == 0:
            self.insert_first(x)
            return
        if i == self.size:
            self.insert_last(x)
            return
        if i > self.size:
            return
        x = LinkedListNode(x)
        front = self.head.later_node(i - 1)
        back = front.next
        front.next = x
        x.next = back
        self.size += 1

    def delete_at(self, i):
        'Delete ith element.'
        if i == 0:
            self.delete_first()
        elif i == self.size - 1:
            self.delete_last()
        elif i < self.size - 1:
            front = self.head.later_node(i - 1)
            front.next = front.next.next
            self.size -= 1

class TestLinkedList(unittest.TestCase):
    'Test Class'
    def test_build(self):
        'Test build and insert_first'
        my_list = LinkedListSeq()
        test_list = list(range(8, 0, -1))
        my_list.build(test_list)
        self.assertEqual(len(my_list), 8)
        self.assertTrue(my_list == list(range(1, 9)))

    def test_insert_delete(self):
        'Test insert_last and delete'
        my_list = LinkedListSeq()
        for i in range(1, 101):
            my_list.insert_last(i)

        self.assertEqual(len(my_list), 100)
        self.assertTrue(my_list == list(range(1, 101)))

        for _ in range(0, 50):
            my_list.delete_first()
        for _ in range(0, 50):
            my_list.delete_last()
        self.assertEqual(len(my_list), 0)

    def test_at(self):
        'Test insert_at and delete_at'
        my_list = LinkedListSeq()
        for i in range(1, 50):
            my_list.insert_last(i)
        for i in range(100, 49, -1):
            my_list.insert_at(49, i)
        self.assertEqual(len(my_list), 100)
        self.assertTrue(my_list == list(range(1, 101)))

        for _ in range(0, 100):
            my_list.delete_at(0)
        self.assertEqual(len(my_list), 0)

if __name__ == '__main__':
    unittest.main()
