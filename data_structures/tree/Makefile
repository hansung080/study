# Makefile

ALL_SRCS=binary_tree.c \
         binary_tree_test.c \
		 binary_search_tree.c \
		 binary_search_tree_test.c \
		 avl_rebalance.c \
		 avl_tree_test.c

ALL_OBJS=binary_tree.o \
         binary_tree_test.o \
		 binary_search_tree.o \
		 binary_search_tree_test.o \
		 avl_rebalance.o \
		 avl_tree_test.o

BT_OBJS=binary_tree.o \
        binary_tree_test.o

BST_OBJS=binary_tree.o \
		 avl_rebalance.o \
         binary_search_tree.o \
		 binary_search_tree_test.o

AVL_OBJS=binary_tree.o \
		 avl_rebalance.o \
         binary_search_tree.o \
		 avl_tree_test.o

BT_TARGET=binary-tree-test
BST_TARGET=binary-search-tree-test
AVL_TARGET=avl-tree-test
CC=gcc

all: dep $(BT_TARGET) $(BST_TARGET) $(AVL_TARGET)

dep:
	$(CC) -MM $(ALL_SRCS) > dependencies.dep

$(ALL_OBJS): $(ALL_SRCS)
	$(CC) -c $^

$(BT_TARGET): $(BT_OBJS)
	$(CC) -o $@ $^

$(BST_TARGET): $(BST_OBJS)
	$(CC) -o $@ $^

$(AVL_TARGET): $(AVL_OBJS)
	$(CC) -o $@ $^

clean:
	rm -f dependencies.dep
	rm -f *.pch
	rm -f *.gch
	rm -f *.stackdump
	rm -f *.o
	rm -f $(BT_TARGET)
	rm -f $(BST_TARGET)
	rm -f $(AVL_TARGET)

ifeq (dependencies.dep, $(wildcard dependencies.dep))
include dependencies.dep
endif
