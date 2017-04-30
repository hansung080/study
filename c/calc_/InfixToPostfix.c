#include "InfixToPostfix.h"
#include "Stack.h"
#include "Token.h"

/**
 *==================================================================================
 * 중위 표기법(Infix Notation)을 후위 표기법(Postfix Notation)으로 변환하는 방법
 *  및 후위 표기법(Postfix Notation) 계산 방법
 *----------------------------------------------------------------------------------
 * ex) Infix   : ( 1 + 2 * 3 ) / 4
 *     Postfix : 1 2 3 * + 4 /
 *     Result  : 1 2 3 * + 4 / -> 1 6 + 4 / -> 7 4 / -> 1.75
 *==================================================================================
 */
void convInfixToPostfix(Queue* infixQ, Queue* postfixQ){
	Stack stack;
	Token* token, * popToken;
	
	initStack(&stack);
	
	while(!isQEmpty(infixQ)){
		token = deq(infixQ);
		
		if(token->isNumber){
			enq(postfixQ, token);
			
		}else{
			switch(token->symbol){
				case '(':
					push(&stack, token);
					break;
				
				case ')':
					while(!isStackEmpty(&stack)){
						popToken = pop(&stack);
						
						if(popToken->symbol == '('){
							break;
						}
						
						enq(postfixQ, popToken);
					}
					
					break;
				
				case '+': 
				case '-': 
				case '*': 
				case '/':
					while(!isStackEmpty(&stack) && cmpOpPrec(peek(&stack), token) >= 0){
						enq(postfixQ, pop(&stack));
					}
					
					push(&stack, token);
					break;
			}
		}
	}
	
	while(!isStackEmpty(&stack)){
		enq(postfixQ, pop(&stack));
	}
}

static int cmpOpPrec(Token* t1, Token* t2){
	int op1Prec = getOpPrec(t1->symbol);
	int op2Prec = getOpPrec(t2->symbol);
	
	if(op1Prec > op2Prec){
		return 1;
		
	}else if(op1Prec < op2Prec){
		return -1;
		
	}else{
		return 0;
	}
}

static int getOpPrec(char op){
	switch(op){
		case '*':
		case '/':
			return 3;
		
		case '+':
		case '-':
			return 2;
		
		// - stack에 push시에는 연산자 우선순위를 비교하지 않고 무조건 push하고, pop시에는 연산자 우선순위를 바교한 후 pop함.
		// - pop시 '('연산자는 ')'연산자가 등장할 때까지 stack에 남아있어야 하기 때문에 다른 연산자들 보다 연산자 우선순위가 낮다고 간주함.
		case '(':
			return 1;
	}
	
	return -1;
}
