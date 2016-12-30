#ifndef __UTILITY_H__
#define __UTILITY_H__

#include "Types.h"

/***** 함수 정의 *****/
void memorySet(void* pvDest, BYTE bData, int iSize);
int memoryCpy(void* pvDest, const void* pvSrc, int iSize);
int memoryCmp(const void* pvDest, const void* pvSrc, int iSize);
int getStrLen(const char* pcBuffer);

#endif // __UTILITY_H__
