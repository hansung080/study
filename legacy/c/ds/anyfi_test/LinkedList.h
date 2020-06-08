#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#include "Types.h"
#include "HashMapEntry.h"

/***** 타입 정의 *****/
typedef ENTRY DATA; // 리스트 데이터 => 연결 리스트 데이터를 변경하기 위해서는 이 부분을 수정해야 함(범용 연결 리스트 구현하지 못 했음)

/***** 구조체 정의 *****/
#pragma pack(push, 1)

typedef struct NodeStruct{
	DATA dData;                 // 노드 데이터
	struct NodeStruct* pstNext; // 다음 노드를 가리키는 포인터
} NODE;

typedef struct LinkedListStruct{
	NODE* pstHead;       // 리스트의 머리 노드를 가리키는 포인터
	NODE* pstCur;        // 리스트의 현재 노드를 가리키는 포인터
	NODE* pstBef;        // 리스트의 이전 노드를 가리키는 포인터
	int iCurDataCount;   // 현재 데이터 개수
} LINKEDLIST;

#pragma pack(pop)

/***** 함수 정의 *****/
void initLinkedList(LINKEDLIST* pstList);
int getLinkedListCount(LINKEDLIST* pstList);
void addLinkedList(LINKEDLIST* pstList, DATA dData);
BOOL getFirstDataFromLinkedList(LINKEDLIST* pstList, DATA* pdData);
BOOL getNextDataFromLinkedList(LINKEDLIST* pstList, DATA* pdData);
DATA removeLinkedList(LINKEDLIST* pstList);

#endif // __LINKED_LIST_H__