#include <stdio.h>
#include <pthread.h>
#include "UnitTest.h"
#include "ArrayList.h"
#include "Utility.h"
#include "Person.h"
#include "HashMap.h"

/***** 전역 변수 선언 *****/
// ArrayList 관련 전역 변수
static LIST gs_stList;                             // 리스트
static PERSON gs_stArrayBuffer[LIST_MAXDATACOUNT]; // 리스트 저장용 배열

// HashMap 관련 전역 변수
static MAP gs_stMap; // 해쉬맵

// 스레드 동기화 관련 전역 변수
//static pthread_mutex_t gs_stMutex = PTHREAD_MUTEX_INITIALIZER; // 뮤텍스 초기화

//==================================================================================================
// ArrayList 단위 테스트 관련 함수
//==================================================================================================
BOOL startTestOfArrayList(){
	
	// 리스트 초기화
	initList(&gs_stList, gs_stArrayBuffer, sizeof(PERSON), LIST_MAXDATACOUNT);
	
	// 리스트에 사람 정보를 추가
	if(addPersonList() == FALSE){
		return FALSE;
	}
	
	// 사람 정보 리스트 출력
	printf("====>>>> After Adding Person Info (Count=%d).\n", getListCount(&gs_stList));
	showPersonList();
	
	// 리스트에서 ID=19860003인 사람 정보를 삭제
	removePersonListByID(19860003);
	
	// 사람 정보 리스트 출력
	printf("\n====>>>> After Removing Person(ID=19860003) Info (Count=%d).\n", getListCount(&gs_stList));
	showPersonList();
	
	// 뮤텍스 종료
	//pthread_mutex_destroy(&gs_stMutex);
	
	return TRUE;
}

static BOOL addPersonList(){
	PERSON* pstPerson1;
	PERSON* pstPerson2;
	PERSON* pstPerson3;
	PERSON* pstPerson4;
	PERSON* pstPerson5;
	
	// 사람 정보 생성
	pstPerson1 = createPersonInfo(19840001, "Kwon", 33);
	pstPerson2 = createPersonInfo(19850002, "Kim", 32);
	pstPerson3 = createPersonInfo(19860003, "Lee", 31);
	pstPerson4 = createPersonInfo(19870004, "Choi", 30);
	pstPerson5 = createPersonInfo(19880005, "Kang", 29);
	
	// 스레드 동기화(잠금 생성)
	//pthread_mutex_lock(&gs_stMutex);
	
	// 리스트에 추가
	if(addList(&gs_stList, pstPerson1) == FALSE){
		return FALSE;
	}
	
	if(addList(&gs_stList, pstPerson2) == FALSE){
		return FALSE;
	}
	
	if(addList(&gs_stList, pstPerson3) == FALSE){
		return FALSE;
	}
	
	if(addList(&gs_stList, pstPerson4) == FALSE){
		return FALSE;
	}
	
	if(addList(&gs_stList, pstPerson5) == FALSE){
		return FALSE;
	}
	
	// 스레드 동기화(잠금 해제)
	//pthread_mutex_unlock(&gs_stMutex);
	
	// 사람 정보 메모리 해제
	destroyPersonInfo(pstPerson1);
	destroyPersonInfo(pstPerson2);
	destroyPersonInfo(pstPerson3);
	destroyPersonInfo(pstPerson4);
	destroyPersonInfo(pstPerson5);
	
	return TRUE;
}

static void showPersonList(){
	PERSON stPerson;
	
	// 스레드 동기화(잠금 생성)
	//pthread_mutex_lock(&gs_stMutex);
	
	while(isNextDataExist(&gs_stList) == TRUE){
		getNextData(&gs_stList, &stPerson);
		showPersonInfo(&stPerson);
	}
	
	// 스레드 동기화(잠금 해제)
	//pthread_mutex_unlock(&gs_stMutex);
}

static void removePersonListByID(int iID){
	PERSON stPerson;
	
	// 스레드 동기화(잠금 생성)
	//pthread_mutex_lock(&gs_stMutex);
	
	while(isNextDataExist(&gs_stList) == TRUE){
		getNextData(&gs_stList, &stPerson);
		
		if(stPerson.iID == iID){
			removeNextData(&gs_stList, &stPerson);
		}
	}
	
	// 스레드 동기화(잠금 해제)
	//pthread_mutex_unlock(&gs_stMutex);
}

//==================================================================================================
// HashMap 단위 테스트 관련 함수
//==================================================================================================
BOOL startTestOfHashMap(){
	
	// 해쉬맵 초기화
	initMap(&gs_stMap, myHashFunc);
	
	// 해쉬맵에 사람 정보를 추가
	addPersonMap();
	
	// 사람 정보 리스트 출력
	printf("====>>>> After Adding Person Info (Count=%d).\n", getMapCount(&gs_stMap));
	showPersonMap();
	
	// 해쉬맵에서 ID=19860003인 사람 정보를 삭제
	removePersonMapByID(19860003);
	
	// 사람 정보 리스트 출력
	printf("\n====>>>> After Removing Person(ID=19860003) Info (Count=%d).\n", getMapCount(&gs_stMap));
	showPersonMap();
	
	// 뮤텍스 종료
	//pthread_mutex_destroy(&gs_stMutex);
	
	return TRUE;
}

static int myHashFunc(int key){
	return key % HASHMAP_MAXDATACOUNT;
}

static void addPersonMap(){
	PERSON* pstPerson1;
	PERSON* pstPerson2;
	PERSON* pstPerson3;
	PERSON* pstPerson4;
	PERSON* pstPerson5;
	
	// 사람 정보 생성
	pstPerson1 = createPersonInfo(19840001, "Kwon", 33);
	pstPerson2 = createPersonInfo(19850002, "Kim", 32);
	pstPerson3 = createPersonInfo(19860003, "Lee", 31);
	pstPerson4 = createPersonInfo(19870004, "Choi", 30);
	pstPerson5 = createPersonInfo(19880001, "Kang", 29); // 해쉬맵 충돌 테스트를 위해, '19840001' 와 '19880001'의 Hash Value를 같게 설정.
	
	// 스레드 동기화(잠금 생성)
	//pthread_mutex_lock(&gs_stMutex);
	
	// 해쉬맵에 추가
	addMap(&gs_stMap, pstPerson1->iID, pstPerson1);
	addMap(&gs_stMap, pstPerson2->iID, pstPerson2);
	addMap(&gs_stMap, pstPerson3->iID, pstPerson3);
	addMap(&gs_stMap, pstPerson4->iID, pstPerson4);
	addMap(&gs_stMap, pstPerson5->iID, pstPerson5);
	
	// 스레드 동기화(잠금 해제)
	//pthread_mutex_unlock(&gs_stMutex);
}

static void showPersonMap(){
	PERSON* pstPerson1;
	PERSON* pstPerson2;
	PERSON* pstPerson3;
	PERSON* pstPerson4;
	PERSON* pstPerson5;
	
	// 스레드 동기화(잠금 생성)
	//pthread_mutex_lock(&gs_stMutex);
	
	// 키(주민 등록 번호)를 통해 해쉬맵 검색
	pstPerson1 = getMap(&gs_stMap, 19840001);
	if(pstPerson1 != NULL){
		showPersonInfo(pstPerson1);
	}
	
	pstPerson2 = getMap(&gs_stMap, 19850002);
	if(pstPerson2 != NULL){
		showPersonInfo(pstPerson2);
	}
	
	
	pstPerson3 = getMap(&gs_stMap, 19860003);
	if(pstPerson3 != NULL){
		showPersonInfo(pstPerson3);
	}
	
	pstPerson4 = getMap(&gs_stMap, 19870004);
	if(pstPerson4 != NULL){
		showPersonInfo(pstPerson4);
	}
	
	pstPerson5 = getMap(&gs_stMap, 19880001);
	if(pstPerson5 != NULL){
		showPersonInfo(pstPerson5);
	}
	
	// 스레드 동기화(잠금 해제)
	//pthread_mutex_unlock(&gs_stMutex);
}

static void removePersonMapByID(int iID){
	PERSON* pstPerson;
	
	// 스레드 동기화(잠금 생성)
	//pthread_mutex_lock(&gs_stMutex);
	
	// 키(주민 등록 번호)를 통해 해쉬맵 삭제
	pstPerson = removeMap(&gs_stMap, iID);
	if(pstPerson != NULL){
		destroyPersonInfo(pstPerson);
	}
	
	// 스레드 동기화(잠금 해제)
	//pthread_mutex_unlock(&gs_stMutex);
}

