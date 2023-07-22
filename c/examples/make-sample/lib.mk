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
ST_OBJ_ROOT := $(BUILD_DIR)/sobj
DY_OBJ_ROOT := $(BUILD_DIR)/dobj
LIB_DIR := $(BUILD_DIR)/lib
DEP_DIR := $(BUILD_DIR)/dep
SRC_DIRS := $(shell find $(SRC_ROOT) -type d)
ST_OBJ_DIRS := $(patsubst $(SRC_ROOT)%,$(ST_OBJ_ROOT)%,$(SRC_DIRS))
DY_OBJ_DIRS := $(patsubst $(SRC_ROOT)%,$(DY_OBJ_ROOT)%,$(SRC_DIRS))

SRCS := $(subst $(SRC_ROOT)/main.c,,$(wildcard $(patsubst %,%/*.c,$(SRC_DIRS))))
ST_OBJS := $(patsubst $(SRC_ROOT)/%.c,$(ST_OBJ_ROOT)/%.o,$(SRCS))
DY_OBJS := $(patsubst $(SRC_ROOT)/%.c,$(DY_OBJ_ROOT)/%.o,$(SRCS))
TARGET_NAME := make-sample
ST_TARGET := $(LIB_DIR)/lib$(TARGET_NAME).a
DY_LIB_NAME := lib$(TARGET_NAME)
DY_LIB := $(LIB_DIR)/$(DY_LIB_NAME)
DY_EXT := $(if $(IS_MAC),dylib,so)
DY_MAJOR := 0
DY_VERSION := $(DY_MAJOR).1.0
DY_TARGET := $(if $(IS_MAC),$(DY_LIB).$(DY_VERSION).$(DY_EXT),$(DY_LIB).$(DY_EXT).$(DY_VERSION))
TARGET := $(if $(__static),$(ST_TARGET),$(DY_TARGET))
DEP := $(DEP_DIR)/dependencies.mk
CC := gcc
CFLAGS :=
DY_FLAGS :=
AR := ar
MAKE_REC := make -f $(SELF)

.PHONY: build
build:
ifeq ($(__verbose),)
	@$(MAKE_REC) src-build > /dev/null
	@echo $(call blue,BUILD COMPLETE): $(TARGET)
else
	$(MAKE_REC) src-build
endif

.PHONY: src-build
src-build: src-prepare src-dep $(TARGET)

.PHONY: src-prepare
src-prepare:
	mkdir -p $(if $(__static),$(ST_OBJ_DIRS),$(DY_OBJ_DIRS)) $(LIB_DIR) $(DEP_DIR)

.PHONY: src-dep
src-dep:
	$(CC) -MM $(CFLAGS) $(SRCS) | sed "s,\(^.*\.o: $(patsubst ./%,%,$(SRC_ROOT))\)\(.*\)\(/.*\.c\),$(if $(__static),$(ST_OBJ_ROOT),$(DY_OBJ_ROOT))\2/\1\2\3," > $(DEP)

$(ST_OBJ_ROOT)/%.o: $(SRC_ROOT)/%.c
	$(CC) -c -o $@ $(CFLAGS) $<

$(ST_TARGET): $(ST_OBJS)
	$(AR) crs $@ $^
	@echo $(call blue,BUILD COMPLETE): $@

$(DY_OBJ_ROOT)/%.o: $(SRC_ROOT)/%.c
	$(CC) -c -fPIC -o $@ $(CFLAGS) $<

$(DY_TARGET): $(DY_OBJS)
ifeq ($(IS_MAC),true)
	$(CC) -dynamiclib -Wl,-install_name,$(DY_LIB_NAME).$(DY_MAJOR).$(DY_EXT) -o $@ $(DY_FLAGS) $^
	ln -sf $(DY_LIB_NAME).$(DY_VERSION).$(DY_EXT) $(DY_LIB).$(DY_MAJOR).$(DY_EXT)
	ln -sf $(DY_LIB_NAME).$(DY_MAJOR).$(DY_EXT) $(DY_LIB).$(DY_EXT)
	@echo $(call blue,BUILD COMPLETE): $@
else
	$(CC) -shared -Wl,-soname,$(DY_LIB_NAME).$(DY_EXT).$(DY_MAJOR) -o $@ $(DY_FLAGS) $^
	ln -sf $(DY_LIB_NAME).$(DY_EXT).$(DY_VERSION) $(DY_LIB).$(DY_EXT).$(DY_MAJOR)
	ln -sf $(DY_LIB_NAME).$(DY_EXT).$(DY_MAJOR) $(DY_LIB).$(DY_EXT)
	@echo $(call blue,BUILD COMPLETE): $@
endif

.PHONY: run
run:
	@echo cannot run a library project

# Variables & Rules for test
TEST_SRC_ROOT := $(PROJECT_ROOT)/test
TEST_OBJ_ROOT := $(BUILD_DIR)/tobj
BIN_DIR := $(BUILD_DIR)/bin
TEST_SRC_DIRS := $(shell find $(TEST_SRC_ROOT) -type d)
TEST_OBJ_DIRS := $(patsubst $(TEST_SRC_ROOT)%,$(TEST_OBJ_ROOT)%,$(TEST_SRC_DIRS))

TEST_SRCS := $(wildcard $(patsubst %,%/*.c,$(TEST_SRC_DIRS)))
TEST_OBJS := $(patsubst $(TEST_SRC_ROOT)/%.c,$(TEST_OBJ_ROOT)/%.o,$(TEST_SRCS))
ST_TEST_TARGET := $(BIN_DIR)/stest-$(TARGET_NAME)
DY_TEST_TARGET := $(BIN_DIR)/dtest-$(TARGET_NAME)
TEST_TARGET := $(if $(__static),$(ST_TEST_TARGET),$(DY_TEST_TARGET))
TEST_DEP := $(DEP_DIR)/test_dependencies.mk
TEST_CFLAGS :=
TEST_LDFLAGS := -L$(LIB_DIR) -l$(patsubst lib%,%,$(DY_LIB_NAME))
ifeq ($(IS_MAC),true)
DYLD_LIBRARY_PATH := $(LIB_DIR)
else
LD_LIBRARY_PATH := $(LIB_DIR)
endif

.PHONY: test-build
test-build: src-build test-prepare test-dep $(TEST_TARGET)

.PHONY: test-prepare
test-prepare:
	mkdir -p $(TEST_OBJ_DIRS) $(BIN_DIR)

.PHONY: test-dep
test-dep:
	$(CC) -MM $(TEST_CFLAGS) $(TEST_SRCS) | sed "s,\(^.*\.o: $(patsubst ./%,%,$(TEST_SRC_ROOT))\)\(.*\)\(/.*\.c\),$(TEST_OBJ_ROOT)\2/\1\2\3," > $(TEST_DEP)

$(TEST_OBJ_ROOT)/%.o: $(TEST_SRC_ROOT)/%.c
	$(CC) -c -o $@ $(TEST_CFLAGS) $<

$(ST_TEST_TARGET): $(TEST_OBJS)
	$(CC) $(if $(IS_MAC),,-static) -o $@ $(TEST_LDFLAGS) $^
	@echo $(call blue,TEST BUILD COMPLETE): $@

$(DY_TEST_TARGET): $(TEST_OBJS)
	$(CC) -o $@ $(TEST_LDFLAGS) $^
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
	find $(TEST_SRC_ROOT) -name "*.pch" -o -name "*.gch" -o -name "*.stackdump" | xargs rm -f

.PHONY: version
version:
	@echo Makefile v$(VERSION) for a library project

.PHONY: var
var:
	@echo $(call blue,# User-defined Variables)
	@echo IS_MAC=$(IS_MAC)';'
	@echo VERSION=$(VERSION)';'
	@echo SELF=$(SELF)';'
	@echo PROJECT_ROOT=$(PROJECT_ROOT)';'
	@echo SRC_ROOT=$(SRC_ROOT)';'
	@echo BUILD_DIR=$(BUILD_DIR)';'
	@echo ST_OBJ_ROOT=$(ST_OBJ_ROOT)';'
	@echo DY_OBJ_ROOT=$(DY_OBJ_ROOT)';'
	@echo LIB_DIR=$(LIB_DIR)';'
	@echo DEP_DIR=$(DEP_DIR)';'
	@echo SRC_DIRS=$(SRC_DIRS)';'
	@echo ST_OBJ_DIRS=$(ST_OBJ_DIRS)';'
	@echo DY_OBJ_DIRS=$(DY_OBJ_DIRS)';'
	@echo SRCS=$(SRCS)';'
	@echo ST_OBJS=$(ST_OBJS)';'
	@echo DY_OBJS=$(DY_OBJS)';'
	@echo TARGET_NAME=$(TARGET_NAME)';'
	@echo ST_TARGET=$(ST_TARGET)';'
	@echo DY_LIB_NAME=$(DY_LIB_NAME)';'
	@echo DY_LIB=$(DY_LIB)';'
	@echo DY_EXT=$(DY_EXT)';'
	@echo DY_MAJOR=$(DY_MAJOR)';'
	@echo DY_VERSION=$(DY_VERSION)';'
	@echo DY_TARGET=$(DY_TARGET)';'
	@echo TARGET=$(TARGET)';'
	@echo DEP=$(DEP)';'
	@echo CC=$(CC)';'
	@echo CFLAGS=$(CFLAGS)';'
	@echo DY_FLAGS=$(DY_FLAGS)';'
	@echo AR=$(AR)';'
	@echo MAKE_REC=$(MAKE_REC)';'
	@echo TEST_SRC_ROOT=$(TEST_SRC_ROOT)';'
	@echo TEST_OBJ_ROOT=$(TEST_OBJ_ROOT)';'
	@echo BIN_DIR=$(BIN_DIR)';'
	@echo TEST_SRC_DIRS=$(TEST_SRC_DIRS)';'
	@echo TEST_OBJ_DIRS=$(TEST_OBJ_DIRS)';'
	@echo TEST_SRCS=$(TEST_SRCS)';'
	@echo TEST_OBJS=$(TEST_OBJS)';'
	@echo ST_TEST_TARGET=$(ST_TEST_TARGET)';'
	@echo DY_TEST_TARGET=$(DY_TEST_TARGET)';'
	@echo TEST_TARGET=$(TEST_TARGET)';'
	@echo TEST_DEP=$(TEST_DEP)';'
	@echo TEST_CFLAGS=$(TEST_CFLAGS)';'
	@echo TEST_LDFLAGS=$(TEST_LDFLAGS)';'
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
	@echo __static=$(__static)';'
	@echo __verbose=$(__verbose)';'
	@echo LD_LIBRARY_PATH=$(LD_LIBRARY_PATH)';'
	@echo DYLD_LIBRARY_PATH=$(DYLD_LIBRARY_PATH)';'

ifeq ($(DEP),$(wildcard $(DEP)))
include $(DEP)
endif
