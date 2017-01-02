#include "reverse.h"

int main(int argc, const char** argv){
	if(argc != 2){
		fprintf(stderr, "Usage: reverse <string>\n");
		return 1;
	}	
	
	int len = strlen_hs(argv[1]);
	char str[len+1];
	
	memset(str, 0, len+1);
	memcpy(str, argv[1], len);
	
	reverse_string(str);
	
	printf("[%s]\n", str);
	
	return 0;
}

