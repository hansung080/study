#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"

void initQ(Queue* q){
	q->front = NULL;
	q->rear = NULL;
}

Bool isQEmpty(Queue* q){
	if(q->front == NULL){
		return TRUE;
	}
	
	return FALSE;
}

void enq(Queue* q, QData data){
	QNode* newNode = (QNode*)malloc(sizeof(QNode));
	
	newNode->data = data;
	newNode->next = NULL;
	
	if(isQEmpty(q)){
		q->front = newNode;
		q->rear = newNode;
		
	}else{
		q->rear->next = newNode;
		q->rear = newNode;
	}
}

QData deq(Queue* q){
	QData delData;
	QNode* delNode;
	
	if(isQEmpty(q)){
		fprintf(stderr, "[Error]Queue is empty!\n");
		exit(-1);
	}
	
	delData = q->front->data;
	delNode = q->front;
	q->front = q->front->next;
	
	free(delNode);
	
	return delData;
}

QData peekq(Queue* q){
	if(isQEmpty(q)){
		fprintf(stderr, "[Error]Queue is empty!\n");
		exit(-1);
	}
	
	return q->front->data;
}
