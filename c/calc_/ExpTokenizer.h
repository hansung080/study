#ifndef __EXP_TOKENIZER_H__
#define __EXP_TOKENIZER_H__

#include "Types.h"
#include "Queue.h"

void tokenizeExp(const char* exp, Queue* infixQ, Queue* destroyQ);

#endif // __EXP_TOKENIZER_H__
