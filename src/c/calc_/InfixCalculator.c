#include "InfixCalculator.h"
#include "InfixToPostfix.h"
#include "PostfixCalculator.h"
#include "Queue.h"
#include "ExpTokenizer.h"
#include "Token.h"

double calcInfix(const char* exp){
	double result;
	Queue infixQ, postfixQ, destroyQ;
	
	initQ(&infixQ);
	initQ(&postfixQ);
	initQ(&destroyQ);
	
	tokenizeExp(exp, &infixQ, &destroyQ);
	convInfixToPostfix(&infixQ, &postfixQ);
	result = calcPostfix(&postfixQ);
	
	while(!isQEmpty(&destroyQ)){
		destroyToken(deq(&destroyQ));
	}
	
	return result;
}

