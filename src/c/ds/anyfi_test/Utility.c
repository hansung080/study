#include "Utility.h"

void memorySet(void* pvDest, BYTE bData, int iSize){
	int i;

	for(i = 0; i < iSize; i++){
		((char*)pvDest)[i] = bData;
	}
}

int memoryCpy(void* pvDest, const void* pvSrc, int iSize){
	int i;

	for(i = 0; i < iSize; i++){
		((char*)pvDest)[i] = ((char*)pvSrc)[i];
	}

	return iSize;
}

int memoryCmp(const void* pvDest, const void* pvSrc, int iSize){
	int i;
	char cTemp;

	for(i = 0; i < iSize; i++){
		cTemp = ((char*)pvDest)[i] - ((char*)pvSrc)[i];
		
		if(cTemp != 0){
			return (int)cTemp;
		}
	}

	return 0;
}

int getStrLen(const char* pcBuffer){
	int i;

	for(i = 0; ; i++){
		if(pcBuffer[i] == '\0'){
			break;
		}
	}

	return i;
}

