#include "ArrayList.h"
#include "Utility.h"

void initList(LIST* pstList, void* pvArray, int iDataSize, int iMaxDataCount){
	// 리스트 초기화
	pstList->pvArray = pvArray;
	pstList->iDataSize = iDataSize;
	pstList->iMaxDataCount = iMaxDataCount;
	pstList->iCurDataCount = 0;
	pstList->iCurIndex = -1;
}

BOOL isListEmpty(LIST* pstList){
	if(pstList->iCurDataCount == 0){
		return TRUE;
	}
	
	return FALSE;
}

BOOL isListFull(LIST* pstList){
	if(pstList->iCurDataCount >= pstList->iMaxDataCount){
		return TRUE;
	}
	
	return FALSE;
}

int getListCount(LIST* pstList){
	return pstList->iCurDataCount;
}

BOOL addList(LIST* pstList, const void* pvData){
	
	// 리스트가 가득 찼을 경우, FALSE 리턴
	if(isListFull(pstList) == TRUE){
		return FALSE;
	}
	
	memoryCpy((char*)pstList->pvArray + (pstList->iCurDataCount * pstList->iDataSize), pvData, pstList->iDataSize);
	pstList->iCurDataCount++;
	
	return TRUE;
}

BOOL isNextDataExist(LIST* pstList){
	
	// 리스트가 비었을 경우, 또는 리스트의 마지막 데이터까지 검색했을 경우, FALSE 리턴
	if((isListEmpty(pstList) == TRUE) || (pstList->iCurIndex >= (pstList->iCurDataCount - 1))){
		pstList->iCurIndex = -1;
		return FALSE;
	}
	
	pstList->iCurIndex++;
	return TRUE;
}

void getNextData(LIST* pstList, void* pvData){
	memoryCpy(pvData, (char*)pstList->pvArray + (pstList->iCurIndex * pstList->iDataSize), pstList->iDataSize);
}

void removeNextData(LIST* pstList, void* pvData){
	int iRemoveIndex;
	int i;
	
	iRemoveIndex = pstList->iCurIndex;
	memoryCpy(pvData, (char*)pstList->pvArray + (iRemoveIndex * pstList->iDataSize), pstList->iDataSize);
	
	
	// 삭제될 데이터를 메우기 위한 데이터 이동
	for(i = iRemoveIndex; i < (pstList->iCurDataCount - 1); i++){
		memoryCpy((char*)pstList->pvArray + (i * pstList->iDataSize), (char*)pstList->pvArray + ((i + 1) * pstList->iDataSize), pstList->iDataSize);
	}
	
	pstList->iCurDataCount--;
	pstList->iCurIndex--;
}
