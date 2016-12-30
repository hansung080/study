#ifndef __UNIT_TEST_H__
#define __UNIT_TEST_H__

#include "Types.h"

/***** 매크로 정의 *****/
#define LIST_MAXDATACOUNT 1024

/***** 함수 정의 *****/
// ArrayList 단위 테스트 관련 함수
BOOL startTestOfArrayList();                // ArrayList 단위 테스트 함수
static BOOL addPersonList();                // 리스트에 사람 정보를 추가
static void showPersonList();               // 사람 정보 리스트 출력
static void removePersonListByID(int iID);  // 리스트에서 사람 정보를 삭제

// HashMap 단위 테스트 관련 함수
BOOL startTestOfHashMap();                  // HashMap 단위 테스트 함수
static int myHashFunc(int key);             // 해쉬 함수
static void addPersonMap();                 // 해쉬맵에 사람 정보를 추가
static void showPersonMap();                // 사람 정보 리스트 출력
static void removePersonMapByID(int iID);   // 해쉬맵에서 사람 정보를 삭제

#endif // __UNIT_TEST_H__
