#include <stdio.h>
#include <string.h>
#include "util.h"

#define PY_BUF_LEN  4096
#define S_SPACE     " "
#define S_ASTERIST  "*"
#define S_LINE_FEED "\n"

void make_pyramid(char* pyramid, int height);
void make_pyramid_rev(char* pyramid, int height);

void make_pyramid(char* pyramid, int height){
	int i, j, k;

	for(i = 1; i <= height; i++){
		for(j = 0; j < height - i; j++){
			strcat(pyramid, S_SPACE);
		}

		for(k = 0; k < i * 2 - 1; k++){
			strcat(pyramid, S_ASTERIST);
		}
		
		strcat(pyramid, S_LINE_FEED);
	}
}

void make_pyramid_rev(char* pyramid, int height){
	int i, j, k;

	for(i = height; i >= 1; i--){
		for(j = 0; j < height - i; j++){
			strcat(pyramid, S_SPACE);
		}

		for(k = 0; k < i * 2 - 1; k++){
			strcat(pyramid, S_ASTERIST);
		}
		
		strcat(pyramid, S_LINE_FEED);
	}
}

