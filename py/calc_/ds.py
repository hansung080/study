class Stack():
	def __init__(self):
		self.__list = []

	def is_empty(self):
		return len(self.__list) == 0

	def push(self, data):
		self.__list.append(data)

	def pop(self):
		if self.is_empty():
			return null

		return self.__list.pop(-1)

	def peek(self):
		if self.is_empty():
			return null

		return self.__list[-1]

class Queue():
	def __init__(self):
		self.__list = []

	def is_empty(self):
		return len(self.__list) == 0

	def enq(self, data):
		self.__list.append(data)

	def deq(self):
		if self.is_empty():
			return null

		return self.__list.pop(0)

	def peek(self):
		if self.is_empty():
			return null

		return self.__list[0]
