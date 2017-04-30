#ifndef __TOKEN_H__
#define __TOKEN_H__

#include "Types.h"

#pragma pack(push, 1)

typedef struct _Token {
	double number;
	char symbol;
	Bool isNumber;
} Token;

#pragma pack(pop)

void createToken(Token** t);
void setToken(Token* t, double number, char symbol, Bool isNumber);
void destroyToken(Token* t);

#endif // __TOKEN_H__
