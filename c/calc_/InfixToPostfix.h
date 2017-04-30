#ifndef __INFIX_TO_POSTFIX_H__
#define __INFIX_TO_POSTFIX_H__

#include "Queue.h"

void convInfixToPostfix(Queue* infixQ, Queue* postfixQ);
static int cmpOpPrec(Token* t1, Token* t2);
static int getOpPrec(char op);

#endif // __INFIX_TO_POSTFIX_H__
