#ifndef __STACK_H__
#define __STACK_H__

#include "Types.h"
#include "Token.h"

typedef Token* SData;

#pragma pack(push, 1)

typedef struct _SNode {
	SData data;
	struct _SNode* next;
} SNode;

typedef struct _LinkedListBasedStack {
	SNode* top;
} LinkedListBasedStack;

#pragma pack(pop)

typedef LinkedListBasedStack Stack;

void initStack(Stack* s);
Bool isStackEmpty(Stack* s);
void push(Stack* s, SData data);
SData pop(Stack* s);
SData peek(Stack* s);

#endif // __STACK_H__
