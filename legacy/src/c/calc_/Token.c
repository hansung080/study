#include <stdlib.h>
#include <string.h>
#include "Token.h"

void createToken(Token** t){
	*t = (Token*)malloc(sizeof(Token));
	memset(*t, 0, sizeof(Token));
}

void setToken(Token* t, double number, char symbol, Bool isNumber){
	t->number = number;
	t->symbol = symbol;
	t->isNumber = isNumber;
}

void destroyToken(Token* t){
	free(t);
}
