#include "HashMap.h"

void initMap(MAP* pstMap, HASHFUNC pfHashFunc){
	int i;
	
	// 해쉬맵의 모든 엔트리 리스트 초기화
	for(i = 0; i < HASHMAP_MAXDATACOUNT; i++){
		initLinkedList(&(pstMap->vstArray[i]));
	}
	
	// 현재 데이터 개수 초기화
	pstMap->iCurDataCount = 0;
	
	// 해쉬 함수 설정
	pstMap->pfHashFunc = pfHashFunc;
}

int getMapCount(MAP* pstMap){
	return pstMap->iCurDataCount;
}

void addMap(MAP* pstMap, KEY key, VALUE value){
	int iHashValue;
	ENTRY stEntry;
	
	iHashValue = pstMap->pfHashFunc(key);
	stEntry.key = key;
	stEntry.value = value;
	
	// 키(Hash Value)가 중복된 경우, 종료
	if(getMap(pstMap, key) != NULL){
		return;
	}
	
	// 연결 리스트에 엔트리 추가
	addLinkedList(&(pstMap->vstArray[iHashValue]), stEntry);
	
	pstMap->iCurDataCount++;
}

VALUE getMap(MAP* pstMap, KEY key){
	int iHashValue;
	ENTRY stEntry;
	
	iHashValue = pstMap->pfHashFunc(key);
	
	if(getFirstDataFromLinkedList(&(pstMap->vstArray[iHashValue]), &stEntry) == TRUE){
		if(stEntry.key == key){
			return stEntry.value;
		}
		
		while(getNextDataFromLinkedList(&(pstMap->vstArray[iHashValue]), &stEntry) == TRUE){
			if(stEntry.key == key){
				return stEntry.value;
			}
		}
	}
	
	return NULL;
}

VALUE removeMap(MAP* pstMap, KEY key){
	int iHashValue;
	ENTRY stEntry;
	
	iHashValue = pstMap->pfHashFunc(key);
	
	if(getFirstDataFromLinkedList(&(pstMap->vstArray[iHashValue]), &stEntry) == TRUE){
		if(stEntry.key == key){
			removeLinkedList(&(pstMap->vstArray[iHashValue]));
			pstMap->iCurDataCount--;
			return stEntry.value;
		}
		
		while(getNextDataFromLinkedList(&(pstMap->vstArray[iHashValue]), &stEntry) == TRUE){
			if(stEntry.key == key){
				removeLinkedList(&(pstMap->vstArray[iHashValue]));
				pstMap->iCurDataCount--;
				return stEntry.value;
			}
		}
	}
	
	return NULL;
}
