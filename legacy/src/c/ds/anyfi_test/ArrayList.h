#ifndef __ARRAY_LIST_H__
#define __ARRAY_LIST_H__

#include "Types.h"

/***** 구조체 정의 *****/
#pragma pack(push, 1)

typedef struct ArrayListStruct{
	void* pvArray;     // 배열의 주소값(범용 리스트 구현을 위해, 배열의 주소값을 리스트 초기화시 넘겨 받음)
	int iDataSize;     // 데이터 크기(범용 리스트 구현을 위해, 데이터 크기를 리스트 초기화시 넘겨 받음)
	int iMaxDataCount; // 최대 테이터 개수(범용 리스트 구현을 위해, 최대 테이터 개수를 리스트 초기화시 넘겨 받음)
	int iCurDataCount; // 현재 데이터 개수
	int iCurIndex;     // 현재 검색 데이터의 인덱스
} LIST;

#pragma pack(pop)

/***** 함수 정의 *****/
void initList(LIST* pstList, void* pvArray, int iDataSize, int iMaxDataCount); // 리스트 초기화
BOOL isListEmpty(LIST* pstList);                                               // 리스트가 비었는지 여부 확인
BOOL isListFull(LIST* pstList);                                                // 리스트가 가득 찼는지 여부 확인
int getListCount(LIST* pstList);                                               // 리스트 데이터 건수 취득
BOOL addList(LIST* pstList, const void* pvData);                               // 리스트에 데이터 추가
BOOL isNextDataExist(LIST* pstList);                                           // 다음 데이터가 존재하는지 여부 확인
void getNextData(LIST* pstList, void* pvData);                                 // 다음 데이터 취득
void removeNextData(LIST* pstList, void* pvData);                              // 다음 데이터 삭제

#endif // __ARRAY_LIST_H__
