#ifndef __HASH_MAP_ENTRY_H__
#define __HASH_MAP_ENTRY_H__

#include "Person.h"

/***** 타입 정의 *****/
typedef int KEY;       // 해쉬맵 키
typedef PERSON* VALUE; // 해쉬맵 데이터 => 해쉬맵 데이터를 변경하기 위해서는 이 부분을 수정해야 함(범용 해쉬맵으로 구현하지 못 했음)

/***** 구조체 정의 *****/
#pragma pack(push, 1)

typedef struct HashMapEntryStruct{
	KEY key;
	VALUE value;
} ENTRY;

#pragma pack(pop)

#endif // __HASH_MAP_ENTRY_H__
