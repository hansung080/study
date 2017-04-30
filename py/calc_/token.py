from ds import Queue

class Token():
	def __init__(self, data, is_number):
		self.__data = data
		self.__is_number = is_number

	@property
	def data(self):
		return self.__data

	@data.setter
	def data(self, data):
		self.__data = data

	@property
	def is_number(self):
		return self.__is_number

	@is_number.setter
	def is_number(self, is_number):
		self.__is_number = is_number

	def __add__(self, other):
		if not self.__is_number or not other.__is_number:
			return null

		return Token(self.__data + other.__data, True)

	def __sub__(self, other):
		if not self.__is_number or not other.__is_number:
			return null

		return Token(self.__data - other.__data, True)

	def __mul__(self, other):
		if not self.__is_number or not other.__is_number:
			return null

		return Token(self.__data * other.__data, True)

	def __truediv__(self, other):
		if not self.__is_number or not other.__is_number:
			return null

		return Token(self.__data / other.__data, True)

# 수식을 토큰으로 구분한 후 큐에 삽입
# ex) exp : -10 * ( -100 + 200 ) + ( 22345.678 / ( 20 - 10 ) )
def tokenize_exp(exp):
	infix_q = Queue()
	i = 0
	sc = 0
	number = 0.0
	divisor = 1.0
	flag_number = False
	flag_minus = False
	flag_point = False

	while i < len(exp):
		ch = exp[i]

		if ch == ' ':
			sc += 1

		elif '0123456789'.count(ch) == 1:
			sc = 0
			flag_number = True

			if not flag_point:
				number *= 10.0
				number += int(ch)

			else:
				divisor *= 10.0
				number += (int(ch) / divisor)


		elif (ch == '-' and (i-sc) == 0) or (ch == '-' and (i-sc-1) >= 0 and exp[i-sc-1] == '('):
			sc = 0
			flag_minus = True

		elif ch == '.' and flag_number:
			sc = 0
			flag_point = True

		else:
			sc = 0
			if flag_number:
				flag_number = False
				flag_point = False

				if flag_minus:
					flag_minus = False
					number = -number

				infix_q.enq(Token(number, True))
				number = 0.0
				divisor = 1.0

			infix_q.enq(Token(ch, False))

		i += 1

	if flag_number:
		if flag_minus:
			number = -number

		infix_q.enq(Token(number, True))

	return infix_q
