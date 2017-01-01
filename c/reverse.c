#include <stdio.h>
#include <string.h>

#define SWAP(x, y, t) ((t)=(x)), ((x)=(y)), ((y)=(t))

int strlen_hs(const char* str);
void reverse_string(char* str);

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

int strlen_hs(const char* str){
	int i;
	
	for(i = 0; str[i] != '\0'; i++){
		;	
	}
	
	return i;
}

void reverse_string(char* str){
	int len = strlen_hs(str);	
	int i;
	int temp;
	
	for(i = 0; i < (len / 2); i++){
		SWAP(str[i], str[len-1-i], temp);
	}
}

