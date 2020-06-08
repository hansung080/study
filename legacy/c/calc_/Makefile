# Makefile

SRCS=Main.c Stack.c InfixCalculator.c InfixToPostfix.c PostfixCalculator.c Queue.c Token.c ExpTokenizer.c
OBJS=Main.o Stack.o InfixCalculator.o InfixToPostfix.o PostfixCalculator.o Queue.o Token.o ExpTokenizer.o 
TARGET=calc
CC=gcc

all: dep $(TARGET)

dep:
	$(CC) -MM $(SRCS) > Dependency.dep

$(OBJS): $(SRCS)
	$(CC) -c $^

$(TARGET): $(OBJS)
	$(CC) -o $@ $^

clean:
	rm -f Dependency.dep
	rm -f *.pch
	rm -f *.gch
	rm -f *.stackdump
	rm -f *.o
	rm -f $(TARGET)
	
	
ifeq (Dependency.dep, $(wildcard Dependency.dep))
include Dependency.dep
endif
