from token import tokenize_exp
from ds import Queue, Stack
from token import Token

def calc_infix(exp):

	infix_q = tokenize_exp(exp)
	postfix_q = infix2postfix(infix_q)
	result = calc_postfix(postfix_q)

	return result
	
#==================================================================================
# 중위 표기법(Infix Notation)을 후위 표기법(Postfix Notation)으로 변환하는 방법
#  및 후위 표기법(Postfix Notation) 계산 방법
#----------------------------------------------------------------------------------
# ex) Infix   : ( 1 + 2 * 3 ) / 4
#     Postfix : 1 2 3 * + 4 /
#     Result  : 1 2 3 * + 4 / -> 1 6 + 4 / -> 7 4 / -> 1.75
#==================================================================================
def infix2postfix(infix_q):
	postfix_q = Queue()
	stack = Stack()

	while not infix_q.is_empty():
		token = infix_q.deq()

		if token.is_number:
			postfix_q.enq(token)

		else:
			if token.data == '(':
				stack.push(token)

			elif token.data == ')':
				while not stack.is_empty():
					pop_token = stack.pop()

					if pop_token.data == '(':
						break

					postfix_q.enq(pop_token)

			elif token.data == '+' or\
				 token.data == '-' or\
				 token.data == '*' or\
				 token.data == '/':
				while not stack.is_empty() and cmp_op_prec(stack.peek(), token) >= 0:
					postfix_q.enq(stack.pop())

				stack.push(token)

	while not stack.is_empty():
		postfix_q.enq(stack.pop())

	return postfix_q

def cmp_op_prec(token1, token2):
	op1_prec = get_op_prec(token1.data)
	op2_prec = get_op_prec(token2.data)

	if op1_prec > op2_prec:
		return 1

	elif op1_prec < op2_prec:
		return -1

	else:
		return 0

def get_op_prec(op):
	if op == '*' or op == '/':
		return 3

	elif op == '+' or op == '-':
		return 2

	# - stack에 push시에는 연산자 우선순위를 비교하지 않고 무조건 push하고, pop시에는 연산자 우선순위를 바교한 후 pop함.
	# - pop시 '('연산자는 ')'연산자가 등장할 때까지 stack에 남아있어야 하기 때문에 다른 연산자들 보다 연산자 우선순위가 낮다고 간주함.
	elif op == '(':
		return 1

	else:
		return -1


def calc_postfix(postfix_q):
	stack = Stack()

	while not postfix_q.is_empty():
		token = postfix_q.deq()

		if token.is_number:
			stack.push(token)

		else:
			pop_token2 = stack.pop()
			pop_token1 = stack.pop()

			if token.data == '+':
				stack.push(pop_token1 + pop_token2)

			elif token.data == '-':
				stack.push(pop_token1 - pop_token2)

			elif token.data == '*':
				stack.push(pop_token1 * pop_token2)

			elif token.data == '/':
				stack.push(pop_token1 / pop_token2)

	return stack.pop().data
