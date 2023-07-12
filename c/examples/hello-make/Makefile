# Makefile

# Variables for Color
C_RED=\033[0;31m
C_GREEN=\033[0;32m
C_BLUE=\033[0;34m
C_YELLOW=\033[1;33m
C_RESET=\033[0m

red="$(C_RED)$(1)$(C_RESET)"
green="$(C_GREEN)$(1)$(C_RESET)"
blue="$(C_BLUE)$(1)$(C_RESET)"
yellow="$(C_YELLOW)$(1)$(C_RESET)"

# Variables & Rules for src
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

build: prepare dep $(TARGET)

prepare:
	mkdir -p $(OBJ_DIRS) $(BIN_DIR) $(DEP_DIR)

dep:
	rm -f $(DEP)
	$(foreach dir,$(SRC_DIRS),$(CC) -MM $(wildcard $(dir)/*.c) | sed "s,^\(.*\)\.o:,$(call src2obj,$(dir))/\1.o:,g" >> $(DEP);)

$(OBJ_ROOT)/%.o: $(SRC_ROOT)/%.c
	$(CC) -c -o $@ $<

$(TARGET): $(OBJS)
	$(CC) -o $@ $^
	@echo $(call blue,BUILD COMPLETE): $@

run: build
	@echo
	@printf '> '$(call blue,RUN)': '
	./$(TARGET) $(args)

# Variables & Rules for test
TEST_ROOT=test
TOBJ_ROOT=$(BUILD_DIR)/tobj

TEST_DIRS=$(shell find $(TEST_ROOT) -type d)
test2obj=$(patsubst $(TEST_ROOT)%,$(TOBJ_ROOT)%,$(1))
TOBJ_DIRS=$(call test2obj,$(TEST_DIRS))

TESTS=$(wildcard $(patsubst %,%/*.c,$(TEST_DIRS)))
TOBJS=$(patsubst $(TEST_ROOT)/%.c,$(TOBJ_ROOT)/%.o,$(TESTS))
TEST_TARGET=$(TARGET)-test

test-build: build test-prepare test-dep $(TEST_TARGET)

test-prepare:
	mkdir -p $(TOBJ_DIRS)

test-dep:
	$(foreach dir,$(TEST_DIRS),$(CC) -MM $(wildcard $(dir)/*.c) | sed "s,^\(.*\)\.o:,$(call test2obj,$(dir))/\1.o:,g" >> $(DEP);)

$(TOBJ_ROOT)/%.o: $(TEST_ROOT)/%.c
	$(CC) -c -o $@ $<

$(TEST_TARGET): $(subst $(OBJ_ROOT)/main.o,,$(OBJS)) $(TOBJS)
	$(CC) -o $@ $^
	@echo $(call blue,TEST BUILD COMPLETE): $@

test: test-build
	@echo
	@printf '> '$(call blue,TEST START)': '
	./$(TEST_TARGET) $(args)

# Rules for src & test
clean:
	rm -rf $(BUILD_DIR)
	find $(SRC_ROOT) -name "*.pch" -o -name "*.gch" -o -name "*.stackdump" | xargs rm -f
	find $(TEST_ROOT) -name "*.pch" -o -name "*.gch" -o -name "*.stackdump" | xargs rm -f

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
	@echo TEST_ROOT=$(TEST_ROOT)
	@echo TOBJ_ROOT=$(TOBJ_ROOT)
	@echo TEST_DIRS=$(TEST_DIRS)
	@echo TOBJ_DIRS=$(TOBJ_DIRS)
	@echo TESTS=$(TESTS)
	@echo TOBJS=$(TOBJS)
	@echo TEST_TARGET=$(TEST_TARGET)

ifeq ($(DEP),$(wildcard $(DEP)))
include $(DEP)
endif
