#include <stdio.h>
#include "UnitTest.h"

int main(int argc, const char** argv){
	
	// ArrayList 단위 테스트
	printf("================== Array List Unit Test Start ==================\n");
	printf("\n====>>>> Test Result.................................[%s]\n", (startTestOfArrayList() == TRUE) ? "PASS" : "FAIL");
	printf("================================================================\n");
	printf("\n\n");
	
	// HashMap 단위 테스트
	printf("================== Hash Map Unit Test Start ====================\n");
	printf("\n====>>>> Test Result.................................[%s]\n", (startTestOfHashMap() == TRUE) ? "PASS" : "FAIL");
	printf("================================================================\n");
	
	return 0;
}
