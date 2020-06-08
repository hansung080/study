#include <stdio.h>
#include <stdlib.h>
#include "Person.h"
#include "Utility.h"

int getPersonID(PERSON* pstPerson){
	return pstPerson->iID;
}

PERSON* createPersonInfo(int iID, const char* pcName, int iAge){
	PERSON* pstNewPerson = (PERSON*)malloc(sizeof(PERSON));
	
	memorySet(pstNewPerson, 0, sizeof(PERSON));
	
	pstNewPerson->iID = iID;
	memoryCpy(pstNewPerson->vcName, pcName, getStrLen(pcName));
	pstNewPerson->iAge = iAge;
	
	return pstNewPerson;
}

void destroyPersonInfo(PERSON* pstPerson){
	free(pstPerson);
}

void showPersonInfo(PERSON* pstPerson){
	printf("ID=[%d], Name=[%s], Age=[%d]\n", pstPerson->iID, pstPerson->vcName, pstPerson->iAge);
}

