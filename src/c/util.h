#ifndef __UTIL_H__
#define __UTIL_H__

#include "type.h"

#define SWAP(x, y, t) ((t)=(x)), ((x)=(y)), ((y)=(t))

int strlen_hs(const char* str);
int atoi_hs(const char* str);
double atof_hs(const char* str);

int strlen_hs(const char* str){
    int i;
    
    for(i = 0; str[i] != '\0'; i++){
        ;   
    }   
    
    return i;
}

int atoi_hs(const char* str){
    int i;
    int result = 0;

	if(str[0] == '-'){
		i = 1;

	}else{
		i = 0;
	}

    for(; str[i] != '\0'; i++){
        result *= 10; 
        result += (str[i] - '0');
    }   

	if(str[0] == '-'){
		result *= -1;
	}

    return result;
}

double atof_hs(const char* str){
    int i;
    double result = 0.0;
	BOOL point = FALSE;	
	double divisor = 1.0;

	if(str[0] == '-'){
		i = 1;

	}else{
		i = 0;
	}

    for(; str[i] != '\0'; i++){
		if(str[i] == '.'){
			point = TRUE;
			continue;
		}
		
		if(point){
			divisor *= 10;
			result += ((str[i] - '0') / divisor); 			
	
		}else{
        	result *= 10; 
        	result += (str[i] - '0');
		}
	
    }   

	if(str[0] == '-'){
		result *= -1;
	}

    return result;
}

#endif // __UTIL_H__

