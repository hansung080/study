#include <string.h>
#include "ExpTokenizer.h"
#include "Token.h"

// 수식을 토큰으로 구분한 후 큐에 삽입
// ex) exp : -10 * ( -100 + 200 ) + ( 22345.678 / ( 20 - 10 ) )
void tokenizeExp(const char* exp, Queue* infixQ, Queue* destroyQ){
	int len = strlen(exp);
	int i;
	char ch;
	int sc = 0;
	double number = 0;
	double divisor = 1;
	Bool flagNumber = FALSE;
	Bool flagMinus = FALSE;
	Bool flagPoint = FALSE;
	Token* token;
	
	for(i = 0; i < len; i++){
		ch = exp[i];
		
		if(ch == ' '){
			sc++;
		
		}else if('0' <= ch && ch <= '9'){
			sc = 0;
			flagNumber = TRUE;
			if(!flagPoint){
				number *= 10;
				number += (ch - '0');
			}else{
				divisor *= 10;
				number += ((ch - '0') / divisor);
			}
			
		}else if((ch == '-' && (i-sc) == 0) || (ch == '-' && (i-sc-1) >= 0 && exp[i-sc-1] == '(')){
			sc = 0;
			flagMinus = TRUE;
			
		}else if(ch == '.' && flagNumber){
			sc = 0;
			flagPoint = TRUE;
			
		}else{
			sc = 0;
			if(flagNumber){
				flagNumber = FALSE;
				flagPoint = FALSE;
				
				if(flagMinus){
					flagMinus = FALSE;
					number = -number;
				}
				
				createToken(&token);
				enq(destroyQ, token);
				setToken(token, number, 0, TRUE);
				enq(infixQ, token);
				
				number = 0;
				divisor = 1;
			}
			
			createToken(&token);
			enq(destroyQ, token);
			setToken(token, 0, ch, FALSE);
			enq(infixQ, token);
		}
	}
	
	if(flagNumber){
		if(flagMinus){
			number = -number;
		}
		
		createToken(&token);
		enq(destroyQ, token);
		setToken(token, number, 0, TRUE);
		enq(infixQ, token);
	}
}

