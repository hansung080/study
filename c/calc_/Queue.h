#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "Types.h"
#include "Token.h"

typedef Token* QData;

#pragma pack(push, 1)

typedef struct _QNode {
	QData data;
	struct _QNode* next;
} QNode;

typedef struct _LinkedListBasedQueue {
	QNode* front;
	QNode* rear;
} LinkedListBasedQueue;

#pragma pack(pop)

typedef LinkedListBasedQueue Queue;

void initQ(Queue* q);
Bool isQEmpty(Queue* q);
void enq(Queue* q, QData data);
QData deq(Queue* q);
QData peekq(Queue* q);

#endif // __QUEUE_H__
