# Makefile

SRC_ROOT=src
BUILD_DIR=build
OBJ_ROOT=$(BUILD_DIR)/obj
BIN_DIR=$(BUILD_DIR)/bin
DEP_DIR=$(BUILD_DIR)/dep

SRC_DIRS=$(shell find $(SRC_ROOT) -type d)
src2obj=$(patsubst $(SRC_ROOT)%,$(OBJ_ROOT)%,$(1))
OBJ_DIRS=$(call src2obj,$(SRC_DIRS))

SRCS=$(wildcard $(patsubst %,%/*.c,$(SRC_DIRS)))
OBJS=$(patsubst $(SRC_ROOT)/%.c,$(OBJ_ROOT)/%.o,$(SRCS))
TARGET=$(BIN_DIR)/hello-make
DEP=$(DEP_DIR)/dependencies.dep
CC=gcc

all: prepare dep $(TARGET)

prepare:
	mkdir -p $(OBJ_DIRS) $(BIN_DIR) $(DEP_DIR)

dep:
	rm -f $(DEP)
	$(foreach dir,$(SRC_DIRS),$(CC) -MM $(wildcard $(dir)/*.c) | sed "s,^\(.*\)\.o:,$(call src2obj,$(dir))/\1.o:,g" >> $(DEP);)

$(OBJ_ROOT)/%.o: $(SRC_ROOT)/%.c
	$(CC) -c -o $@ $<

$(TARGET): $(OBJS)
	$(CC) -o $@ $^
	@echo BUILD COMPLETE: $@

run: all
	@echo
	@echo -n '=====>>>>> RUN: '
	./$(TARGET)

clean:
	rm -rf $(BUILD_DIR)
	find $(SRC_ROOT) -name "*.pch" -o -name "*.gch" -o -name "*.stackdump" | xargs rm -f

var:
	@echo SRC_ROOT=$(SRC_ROOT)
	@echo BUILD_DIR=$(BUILD_DIR)
	@echo OBJ_ROOT=$(OBJ_ROOT)
	@echo BIN_DIR=$(BIN_DIR)
	@echo DEP_DIR=$(DEP_DIR)
	@echo SRC_DIRS=$(SRC_DIRS)
	@echo OBJ_DIRS=$(OBJ_DIRS)
	@echo SRCS=$(SRCS)
	@echo OBJS=$(OBJS)
	@echo TARGET=$(TARGET)
	@echo DEP=$(DEP)
	@echo CC=$(CC)

ifeq ($(DEP),$(wildcard $(DEP)))
include $(DEP)
endif
