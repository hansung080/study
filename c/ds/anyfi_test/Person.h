#ifndef __PERSON_H__
#define __PERSON_H__

#define PERSON_NAME_LEN   50

/***** 자료구조 정의 *****/
#pragma pack(push, 1)

typedef struct PersonStruct{
	int iID;                      // 주민 등록 번호
	char vcName[PERSON_NAME_LEN]; // 이름
	int iAge;                     // 나이
} PERSON; // 사람 정보(ArrayList 단위 테스트용)

#pragma pack(pop)

/***** 함수 정의 *****/
int getPersonID(PERSON* pstPerson);
PERSON* createPersonInfo(int iID, const char* pcName, int iAge);
void destroyPersonInfo(PERSON* pstPerson);
void showPersonInfo(PERSON* pstPerson);

#endif // __PERSON_H__
