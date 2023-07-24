# Makefile for a binary project

# Common Variables
S_RESET := \033[0m
S_RED := \033[0;31m
S_RED_BOLD := \033[1;31m
S_GREEN := \033[0;32m
S_YELLOW := \033[0;33m
S_BLUE := \033[0;34m
red = $(S_RED)$(1)$(S_RESET)
red_bold = $(S_RED_BOLD)$(1)$(S_RESET)
green = $(S_GREEN)$(1)$(S_RESET)
yellow = $(S_YELLOW)$(1)$(S_RESET)
blue = $(S_BLUE)$(1)$(S_RESET)
ERROR := $(call red_bold,error)

ifeq ($(shell uname -s),Darwin)
IS_MAC := true
else
IS_MAC :=
endif
VERSION := 1.0
SELF := $(firstword $(MAKEFILE_LIST))
PROJECT_ROOT := $(patsubst %/,%,$(dir $(SELF)))

# Variables & Rules for src
SRC_ROOT := $(PROJECT_ROOT)/src
BUILD_DIR := $(PROJECT_ROOT)/build
OBJ_ROOT := $(BUILD_DIR)/obj
BIN_DIR := $(BUILD_DIR)/bin
DEP_DIR := $(BUILD_DIR)/dep
SRC_DIRS := $(shell find $(SRC_ROOT) -type d)
OBJ_DIRS := $(patsubst $(SRC_ROOT)%,$(OBJ_ROOT)%,$(SRC_DIRS))

SRCS := $(wildcard $(patsubst %,%/*.c,$(SRC_DIRS)))
OBJS := $(patsubst $(SRC_ROOT)/%.c,$(OBJ_ROOT)/%.o,$(SRCS))
TARGET_NAME := make-sample
TARGET := $(BIN_DIR)/$(TARGET_NAME)
DEP := $(DEP_DIR)/dependencies.mk
CC := gcc
CFLAGS := -std=c11
LDFLAGS :=
ifeq ($(IS_MAC),true)
DYLD_LIBRARY_PATH :=
else
LD_LIBRARY_PATH :=
endif
MAKE_REC := make -f $(SELF)

.PHONY: build
build:
ifeq ($(__verbose),)
	@$(MAKE_REC) src-build > /dev/null
	@echo "$(call blue,build complete): $(TARGET)"
else
	$(MAKE_REC) src-build
endif

.PHONY: src-build
src-build: src-prepare src-dep $(TARGET)

.PHONY: src-prepare
src-prepare:
	mkdir -p $(OBJ_DIRS) $(BIN_DIR) $(DEP_DIR)

.PHONY: src-dep
src-dep:
	$(CC) -MM $(CFLAGS) $(SRCS) | sed "s,\(^.*\.o: $(patsubst ./%,%,$(SRC_ROOT))\)\(.*\)\(/.*\.c\),$(OBJ_ROOT)\2/\1\2\3," > $(DEP)

$(OBJ_ROOT)/%.o: $(SRC_ROOT)/%.c
	$(CC) -c -o $@ $(CFLAGS) $<

$(TARGET): $(OBJS)
	$(CC) -o $@ $(LDFLAGS) $^
	@echo "> $(call blue,build complete): $@"

.PHONY: run
run:
ifeq ($(__verbose),)
	@$(MAKE_REC) src-build > /dev/null
	@$(TARGET) $(__args)
else
	$(MAKE_REC) src-build
	@echo
	@printf "> $(call blue,run): "
	$(TARGET) $(__args)
endif

# Variables & Rules for test
TEST_SRC_ROOT := $(PROJECT_ROOT)/test
TEST_OBJ_ROOT := $(BUILD_DIR)/tobj
TEST_SRC_DIRS := $(shell find $(TEST_SRC_ROOT) -type d)
TEST_OBJ_DIRS := $(patsubst $(TEST_SRC_ROOT)%,$(TEST_OBJ_ROOT)%,$(TEST_SRC_DIRS))

TEST_SRCS := $(wildcard $(patsubst %,%/*.c,$(TEST_SRC_DIRS)))
TEST_OBJS := $(patsubst $(TEST_SRC_ROOT)/%.c,$(TEST_OBJ_ROOT)/%.o,$(TEST_SRCS))
TEST_TARGET := $(BIN_DIR)/test-$(TARGET_NAME)
TEST_DEP := $(DEP_DIR)/test_dependencies.mk
TEST_CFLAGS := -std=c11 -I$(PROJECT_ROOT)/..
TEST_LDFLAGS :=

.PHONY: test-build
test-build: src-build test-prepare test-dep $(TEST_TARGET)

.PHONY: test-prepare
test-prepare:
	mkdir -p $(TEST_OBJ_DIRS)

.PHONY: test-dep
test-dep:
	$(CC) -MM $(TEST_CFLAGS) $(TEST_SRCS) | sed "s,\(^.*\.o: $(patsubst ./%,%,$(TEST_SRC_ROOT))\)\(.*\)\(/.*\.c\),$(TEST_OBJ_ROOT)\2/\1\2\3," > $(TEST_DEP)

$(TEST_OBJ_ROOT)/%.o: $(TEST_SRC_ROOT)/%.c
	$(CC) -c -o $@ $(TEST_CFLAGS) $<

$(TEST_TARGET): $(TEST_OBJS) $(subst $(OBJ_ROOT)/main.o,,$(OBJS))
	$(CC) -o $@ $(TEST_LDFLAGS) $^
	@echo "> $(call blue,test build complete): $@"

.PHONY: test
test:
ifeq ($(__verbose),)
	@$(MAKE_REC) test-build > /dev/null
	@$(TEST_TARGET) $(__args)
else
	$(MAKE_REC) test-build
	@echo
	@printf "> $(call blue,test start): "
	$(TEST_TARGET) $(__args)
endif

# Rules for src & test
.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
	find $(SRC_ROOT) -name '*.pch' -o -name '*.gch' -o -name '*.stackdump' | xargs rm -f
	find $(TEST_SRC_ROOT) -name '*.pch' -o -name '*.gch' -o -name '*.stackdump' | xargs rm -f

.PHONY: rename-project
rename-project:
ifneq ($(__old_pname),)
ifneq ($(__new_pname),)
	find test -name '*.c' -o -name '*.h' | xargs sed -i $(if $(IS_MAC),'',) "s:\(^ *# *include *<\)$(__old_pname)/:\1$(__new_pname)/:"
else
	@echo "$(ERROR): __new_pname not provided"
	@echo "usage: make rename-project __old_pname=? __new_pname=?"
endif
else
	@echo "$(ERROR): __old_pname not provided"
	@echo "usage: make rename-project __old_pname=? __new_pname=?"
endif

.PHONY: version
version:
	@echo "Makefile v$(VERSION) for a binary project"

.PHONY: var
var:
	@echo "$(call blue,# User-defined Variables)"
	@echo "VERSION=$(VERSION);"
	@echo "SELF=$(SELF);"
	@echo "PROJECT_ROOT=$(PROJECT_ROOT);"
	@echo "SRC_ROOT=$(SRC_ROOT);"
	@echo "BUILD_DIR=$(BUILD_DIR);"
	@echo "OBJ_ROOT=$(OBJ_ROOT);"
	@echo "BIN_DIR=$(BIN_DIR);"
	@echo "DEP_DIR=$(DEP_DIR);"
	@echo "SRC_DIRS=$(SRC_DIRS);"
	@echo "OBJ_DIRS=$(OBJ_DIRS);"
	@echo "SRCS=$(SRCS);"
	@echo "OBJS=$(OBJS);"
	@echo "TARGET_NAME=$(TARGET_NAME);"
	@echo "TARGET=$(TARGET);"
	@echo "DEP=$(DEP);"
	@echo "CC=$(CC);"
	@echo "CFLAGS=$(CFLAGS);"
	@echo "LDFLAGS=$(LDFLAGS);"
	@echo "MAKE_REC=$(MAKE_REC);"
	@echo "TEST_SRC_ROOT=$(TEST_SRC_ROOT);"
	@echo "TEST_OBJ_ROOT=$(TEST_OBJ_ROOT);"
	@echo "TEST_SRC_DIRS=$(TEST_SRC_DIRS);"
	@echo "TEST_OBJ_DIRS=$(TEST_OBJ_DIRS);"
	@echo "TEST_SRCS=$(TEST_SRCS);"
	@echo "TEST_OBJS=$(TEST_OBJS);"
	@echo "TEST_TARGET=$(TEST_TARGET);"
	@echo "TEST_DEP=$(TEST_DEP);"
	@echo "TEST_CFLAGS=$(TEST_CFLAGS);"
	@echo "TEST_LDFLAGS=$(TEST_LDFLAGS);"
	@echo "$(call blue,# Built-in Variables)"
	@echo "MAKE=$(MAKE);"
	@echo "MAKEFLAGS=$(MAKEFLAGS);"
	@echo "MFLAGS=$(MFLAGS);"
	@echo "MAKEOVERRIDES=$(MAKEOVERRIDES);"
	@echo "MAKEFILE_LIST=$(MAKEFILE_LIST);"

.PHONY: env
env:
	@echo "$(call blue,# Environment Variables)"
	@echo "__args=$(__args);"
	@echo "__new_pname=$(__new_pname);"
	@echo "__old_pname=$(__old_pname);"
	@echo "__verbose=$(__verbose);"
	@echo "DYLD_LIBRARY_PATH=$(DYLD_LIBRARY_PATH);"
	@echo "LD_LIBRARY_PATH=$(LD_LIBRARY_PATH);"

ifeq ($(DEP),$(wildcard $(DEP)))
include $(DEP)
endif

ifeq ($(TEST_DEP),$(wildcard $(TEST_DEP)))
include $(TEST_DEP)
endif
