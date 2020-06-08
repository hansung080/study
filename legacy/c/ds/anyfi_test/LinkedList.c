#include <stdlib.h>
#include "LinkedList.h"

void initLinkedList(LINKEDLIST* pstList){
	
	// 연결 리스트 초기화
	pstList->pstHead = (NODE*)malloc(sizeof(NODE)); // 더미 노드 생성(더미 노드 기반의 연결 리스트 구현)
	pstList->pstHead->pstNext = NULL;
	pstList->iCurDataCount = 0;
}

int getLinkedListCount(LINKEDLIST* pstList){
	return pstList->iCurDataCount;
}

void addLinkedList(LINKEDLIST* pstList, DATA dData){
	NODE* pstNew;
	
	pstNew = (NODE*)malloc(sizeof(NODE));
	
	// 리스트의 머리에 새 노드 추가
	pstNew->dData = dData;
	pstNew->pstNext = pstList->pstHead->pstNext;
	pstList->pstHead->pstNext = pstNew;
	
	pstList->iCurDataCount++;
}

BOOL getFirstDataFromLinkedList(LINKEDLIST* pstList, DATA* pdData){
	if(pstList->pstHead->pstNext == NULL){
		return FALSE;
	}

	pstList->pstBef = pstList->pstHead;
	pstList->pstCur = pstList->pstHead->pstNext;

	*pdData = pstList->pstCur->dData;

	return TRUE;
}

BOOL getNextDataFromLinkedList(LINKEDLIST* pstList, DATA* pdData){
	if(pstList->pstCur->pstNext == NULL){
		return FALSE;
	}

	pstList->pstBef = pstList->pstCur;
	pstList->pstCur = pstList->pstCur->pstNext;

	*pdData = pstList->pstCur->dData;

	return TRUE;
}

DATA removeLinkedList(LINKEDLIST* pstList){
	NODE* pstRemoveNode;
	DATA dRemoveData;
	
	pstRemoveNode = pstList->pstCur;
	dRemoveData = pstList->pstCur->dData;
	
	pstList->pstBef->pstNext = pstList->pstCur->pstNext;
	pstList->pstCur = pstList->pstBef;

	free(pstRemoveNode);
	pstList->iCurDataCount--;

	return dRemoveData;
}

