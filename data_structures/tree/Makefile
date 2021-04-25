# Makefile

ALL_SRCS=binary_tree.c binary_tree_test.c binary_search_tree.c binary_search_tree_test.c
ALL_OBJS=binary_tree.o binary_tree_test.o binary_search_tree.o binary_search_tree_test.o
BT_OBJS=binary_tree.o binary_tree_test.o
BST_OBJS=binary_tree.o binary_search_tree.o binary_search_tree_test.o
BT_TARGET=binary-tree-test
BST_TARGET=binary-search-tree-test
CC=gcc

all: dep $(BT_TARGET) $(BST_TARGET)

dep:
	$(CC) -MM $(ALL_SRCS) > dependencies.dep

$(ALL_OBJS): $(ALL_SRCS)
	$(CC) -c $^

$(BT_TARGET): $(BT_OBJS)
	$(CC) -o $@ $^

$(BST_TARGET): $(BST_OBJS)
	$(CC) -o $@ $^

clean:
	rm -f dependencies.dep
	rm -f *.pch
	rm -f *.gch
	rm -f *.stackdump
	rm -f *.o
	rm -f $(BT_TARGET)
	rm -f $(BST_TARGET)

ifeq (dependencies.dep, $(wildcard dependencies.dep))
include dependencies.dep
endif
