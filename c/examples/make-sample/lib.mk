# Makefile for a library project

# Common Variables
C_RED := \033[0;31m
C_GREEN := \033[0;32m
C_BLUE := \033[0;34m
C_YELLOW := \033[1;33m
C_RESET := \033[0m

red = "$(C_RED)$(1)$(C_RESET)"
green = "$(C_GREEN)$(1)$(C_RESET)"
blue = "$(C_BLUE)$(1)$(C_RESET)"
yellow = "$(C_YELLOW)$(1)$(C_RESET)"

SELF := $(firstword $(MAKEFILE_LIST))
PROJECT_ROOT := $(patsubst %/,%,$(dir $(SELF)))

# Variables & Rules for src
SRC_ROOT := $(PROJECT_ROOT)/src
BUILD_DIR := $(PROJECT_ROOT)/build
AOBJ_ROOT := $(BUILD_DIR)/aobj
SOBJ_ROOT := $(BUILD_DIR)/sobj
LIB_DIR := $(BUILD_DIR)/lib
DEP_DIR := $(BUILD_DIR)/dep

SRC_DIRS := $(shell find $(SRC_ROOT) -type d)
AOBJ_DIRS := $(patsubst $(SRC_ROOT)%,$(AOBJ_ROOT)%,$(SRC_DIRS))
SOBJ_DIRS := $(patsubst $(SRC_ROOT)%,$(SOBJ_ROOT)%,$(SRC_DIRS))

SRCS := $(subst $(SRC_ROOT)/main.c,,$(wildcard $(patsubst %,%/*.c,$(SRC_DIRS))))
AOBJS := $(patsubst $(SRC_ROOT)/%.c,$(AOBJ_ROOT)/%.o,$(SRCS))
SOBJS := $(patsubst $(SRC_ROOT)/%.c,$(SOBJ_ROOT)/%.o,$(SRCS))
TARGET_NAME := make-sample
A_TARGET := $(LIB_DIR)/lib$(TARGET_NAME).a
SO_NAME := lib$(TARGET_NAME).so
SO_FILE := $(LIB_DIR)/$(SO_NAME)
SO_MAJOR := 0
SO_VERSION := $(SO_MAJOR).1.0
SO_TARGET := $(SO_FILE).$(SO_VERSION)
ifeq ($(shell uname -s),Darwin)
SO_FLAGS := -install_name
else
SO_FLAGS := -soname
endif
DEP := $(DEP_DIR)/dependencies.mk
CC := gcc
AR := ar
MAKE_REC := make -f $(SELF) $(MFLAGS) $(MAKEOVERRIDES)

.PHONY: build
build:
ifeq ($(__verbose),)
	@$(MAKE_REC) src-build > /dev/null
	@echo $(call blue,BUILD COMPLETE): $(A_TARGET) $(SO_TARGET)
else
	$(MAKE_REC) src-build
endif

.PHONY: src-build
src-build: src-prepare src-dep $(A_TARGET) $(SO_TARGET)

.PHONY: src-prepare
src-prepare:
	mkdir -p $(AOBJ_DIRS) $(SOBJ_DIRS) $(LIB_DIR) $(DEP_DIR)

.PHONY: src-dep
src-dep:
	$(CC) -MM $(SRCS) | sed "s,\(^.*\.o: $(patsubst ./%,%,$(SRC_ROOT))\)\(.*\)\(/.*\.c\),$(AOBJ_ROOT)\2/\1\2\3," > $(DEP)

$(AOBJ_ROOT)/%.o: $(SRC_ROOT)/%.c
	$(CC) -c -o $@ $<

$(A_TARGET): $(AOBJS)
	$(AR) cr $@ $^
	@echo $(call blue,A BUILD COMPLETE): $@

$(SOBJ_ROOT)/%.o: $(SRC_ROOT)/%.c
	$(CC) -c -fPIC -o $@ $<

$(SO_TARGET): $(SOBJS)
	$(CC) -shared -Wl,$(SO_FLAGS),$(SO_NAME).$(SO_MAJOR) -o $@ $^
	ln -sf $@ $(SO_FILE).$(SO_MAJOR)
	ln -sf $(SO_FILE).$(SO_MAJOR) $(SO_FILE)
	@echo $(call blue,SO BUILD COMPLETE): $@

.PHONY: run
run:
	@echo cannot run a library project

# Variables & Rules for test
TEST_ROOT := $(PROJECT_ROOT)/test
TOBJ_ROOT := $(BUILD_DIR)/tobj
BIN_DIR := $(BUILD_DIR)/bin

TEST_DIRS := $(shell find $(TEST_ROOT) -type d)
TOBJ_DIRS := $(patsubst $(TEST_ROOT)%,$(TOBJ_ROOT)%,$(TEST_DIRS))

TESTS := $(wildcard $(patsubst %,%/*.c,$(TEST_DIRS)))
TOBJS := $(patsubst $(TEST_ROOT)/%.c,$(TOBJ_ROOT)/%.o,$(TESTS))
TEST_TARGET := $(BIN_DIR)/test-$(TARGET_NAME)
TEST_DEP := $(DEP_DIR)/test_dependencies.mk

.PHONY: test-build
test-build: src-build test-prepare test-dep $(TEST_TARGET)

.PHONY: test-prepare
test-prepare:
	mkdir -p $(TOBJ_DIRS) $(BIN_DIR)

.PHONY: test-dep
test-dep:
	$(CC) -MM $(TESTS) | sed "s,\(^.*\.o: $(patsubst ./%,%,$(TEST_ROOT))\)\(.*\)\(/.*\.c\),$(TOBJ_ROOT)\2/\1\2\3," > $(TEST_DEP)

$(TOBJ_ROOT)/%.o: $(TEST_ROOT)/%.c
	$(CC) -c -o $@ $<

$(TEST_TARGET): $(AOBJS) $(TOBJS)
	$(CC) -o $@ $^
	@echo $(call blue,TEST BUILD COMPLETE): $@

.PHONY: test
test:
ifeq ($(__verbose),)
	@$(MAKE_REC) test-build > /dev/null
	@$(TEST_TARGET) $(__args)
else
	$(MAKE_REC) test-build
	@echo
	@printf '> '$(call blue,TEST START)': '
	$(TEST_TARGET) $(__args)
endif

# Rules for src & test
.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
	find $(SRC_ROOT) -name "*.pch" -o -name "*.gch" -o -name "*.stackdump" | xargs rm -f
	find $(TEST_ROOT) -name "*.pch" -o -name "*.gch" -o -name "*.stackdump" | xargs rm -f

.PHONY: var
var:
	@echo $(call blue,# User-defined Variables)
	@echo SELF=$(SELF)';'
	@echo PROJECT_ROOT=$(PROJECT_ROOT)';'
	@echo SRC_ROOT=$(SRC_ROOT)';'
	@echo BUILD_DIR=$(BUILD_DIR)';'
	@echo AOBJ_ROOT=$(AOBJ_ROOT)';'
	@echo SOBJ_ROOT=$(SOBJ_ROOT)';'
	@echo LIB_DIR=$(LIB_DIR)';'
	@echo DEP_DIR=$(DEP_DIR)';'
	@echo SRC_DIRS=$(SRC_DIRS)';'
	@echo AOBJ_DIRS=$(AOBJ_DIRS)';'
	@echo SOBJ_DIRS=$(SOBJ_DIRS)';'
	@echo SRCS=$(SRCS)';'
	@echo AOBJS=$(AOBJS)';'
	@echo SOBJS=$(SOBJS)';'
	@echo TARGET_NAME=$(TARGET_NAME)';'
	@echo A_TARGET=$(A_TARGET)';'
	@echo SO_NAME=$(SO_NAME)';'
	@echo SO_FILE=$(SO_FILE)';'
	@echo SO_MAJOR=$(SO_MAJOR)';'
	@echo SO_VERSION=$(SO_VERSION)';'
	@echo SO_TARGET=$(SO_TARGET)';'
	@echo SO_FLAGS=$(SO_FLAGS)';'
	@echo DEP=$(DEP)';'
	@echo CC=$(CC)';'
	@echo AR=$(AR)';'
	@echo MAKE_REC=$(MAKE_REC)';'
	@echo TEST_ROOT=$(TEST_ROOT)';'
	@echo TOBJ_ROOT=$(TOBJ_ROOT)';'
	@echo BIN_DIR=$(BIN_DIR)';'
	@echo TEST_DIRS=$(TEST_DIRS)';'
	@echo TOBJ_DIRS=$(TOBJ_DIRS)';'
	@echo TESTS=$(TESTS)';'
	@echo TOBJS=$(TOBJS)';'
	@echo TEST_TARGET=$(TEST_TARGET)';'
	@echo TEST_DEP=$(TEST_DEP)';'
	@echo $(call blue,# Built-in Variables)
	@echo MAKE=$(MAKE)';'
	@echo MAKEFLAGS=$(MAKEFLAGS)';'
	@echo MFLAGS=$(MFLAGS)';'
	@echo MAKEOVERRIDES=$(MAKEOVERRIDES)';'
	@echo MAKEFILE_LIST=$(MAKEFILE_LIST)';'

.PHONY: env
env:
	@echo $(call blue,# Environment Variables)
	@echo __args=$(__args)';'
	@echo __verbose=$(__verbose)';'

ifeq ($(DEP),$(wildcard $(DEP)))
include $(DEP)
endif
