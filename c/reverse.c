#include <stdio.h>
#include <string.h>

#define SWAP(x, y, t) ((t)=(x)), ((x)=(y)), ((y)=(t))

int get_strlen(const char* str);
void reverse_string(char* str);

int main(int argc, const char** argv){
	if(argc != 2){
		fprintf(stderr, "Usage: reverse <string>\n");
		return 1;
	}	
	
	int len = get_strlen(argv[1]);
	char str[len+1];
	
	memset(str, 0, len+1);
	memcpy(str, argv[1], len);
	
	reverse_string(str);
	
	printf("[%s]\n", str);
	
	return 0;
}

int get_strlen(const char* str){
	int i;
	
	for(i = 0; str[i] != '\0'; i++){
		;	
	}
	
	return i;
}

void reverse_string(char* str){
	int len = get_strlen(str);	
	int i;
	int temp;
	
	for(i = 0; i < (len / 2); i++){
		SWAP(str[i], str[len-1-i], temp);
	}
}

