#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"

void initStack(Stack* s){
	s->top = NULL;
}

Bool isStackEmpty(Stack* s){
	if(s->top == NULL){
		return TRUE;
	}
	
	return FALSE;
}

void push(Stack* s, SData data){
	SNode* newNode = (SNode*)malloc(sizeof(SNode));
	
	newNode->data = data;
	newNode->next = s->top;
	s->top = newNode;
}

SData pop(Stack* s){
	SData delData;
	SNode* delNode;
	
	if(isStackEmpty(s)){
		fprintf(stderr, "[Error]Stack is empty!\n");
		exit(-1);
	}
	
	delData = s->top->data;
	delNode = s->top;
	s->top = s->top->next;
	
	free(delNode);
	
	return delData;
}

SData peek(Stack* s){
	if(isStackEmpty(s)){
		fprintf(stderr, "[Error]Stack is empty!\n");
		exit(-1);
	}
	
	return s->top->data;
}
