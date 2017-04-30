#include "PostfixCalculator.h"
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
double calcPostfix(Queue* postfixQ){
	double result;
	Stack stack;
	Token* token, * popToken1, * popToken2, * newToken;
	Queue destroyQ;
	
	initStack(&stack);
	initQ(&destroyQ);
	
	while(!isQEmpty(postfixQ)){
		token = deq(postfixQ);
		
		if(token->isNumber){
			push(&stack, token);
			
		}else{
			popToken2 = pop(&stack);
			popToken1 = pop(&stack);
			
			switch(token->symbol){
				case '+':
					createToken(&newToken);
					enq(&destroyQ, newToken);
					setToken(newToken, popToken1->number + popToken2->number, 0, TRUE);
					push(&stack, newToken);
					break;
				
				case '-':
					createToken(&newToken);
					enq(&destroyQ, newToken);
					setToken(newToken, popToken1->number - popToken2->number, 0, TRUE);
					push(&stack, newToken);
					break;
				
				case '*':
					createToken(&newToken);
					enq(&destroyQ, newToken);
					setToken(newToken, popToken1->number * popToken2->number, 0, TRUE);
					push(&stack, newToken);
					break;
				
				case '/':
					createToken(&newToken);
					enq(&destroyQ, newToken);
					setToken(newToken, popToken1->number / popToken2->number, 0, TRUE);
					push(&stack, newToken);
					break;
			}
		}
	}
	
	popToken1 = pop(&stack);
	result = popToken1->number;
	
	while(!isQEmpty(&destroyQ)){
		destroyToken(deq(&destroyQ));
	}
	
	return result;
}

