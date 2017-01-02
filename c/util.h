#ifndef __UTIL_H__
#define __UTIL_H__

#define SWAP(x, y, t) ((t)=(x)), ((x)=(y)), ((y)=(t))

int strlen_hs(const char* str);
int atoi_hs(const char* str);

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

    for(i = 0; str[i] != '\0'; i++){
        result *= 10; 
        result += (str[i] - '0');
    }   

    return result;
}

#endif // __UTIL_H__
