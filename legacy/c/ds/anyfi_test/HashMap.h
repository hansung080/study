#ifndef __HASH_MAP_H__
#define __HASH_MAP_H__

#include "Types.h"
#include "HashMapEntry.h"
#include "LinkedList.h"

/***** 매크로 정의 *****/
#define HASHMAP_MAXDATACOUNT 100

/***** 타입 정의 *****/
typedef int (*HASHFUNC)(KEY key); // 해쉬 함수의 함수 포인터

/***** 구조체 정의 *****/
#pragma pack(push, 1)

typedef struct HashMapStruct{
	LINKEDLIST vstArray[HASHMAP_MAXDATACOUNT]; // 엔트리 리스트 배열(해쉬맵의 충돌 문제를 해결하기 위해, Linked List를 활용)
	int iCurDataCount;                         // 현재 데이터 개수
	HASHFUNC pfHashFunc;                       // 해쉬 함수
} MAP;

#pragma pack(pop)

/***** 함수 정의 *****/
void initMap(MAP* pstMap, HASHFUNC pfHashFunc); // 해쉬맵 초기화
int getMapCount(MAP* pstMap);                   // 해쉬맵 데이터 건수 취득
void addMap(MAP* pstMap, KEY key, VALUE value); // 해쉬맵에 데이터 추가
VALUE getMap(MAP* pstMap, KEY key);             // 해쉬맵에서 데이터 검색
VALUE removeMap(MAP* pstMap, KEY key);          // 해쉬맵에서 데이터 삭제

#endif // __HASH_MAP_H__
