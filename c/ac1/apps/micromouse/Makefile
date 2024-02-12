# Edit this makefile for your project.

SELF := $(firstword $(MAKEFILE_LIST))
PROJECT_ROOT := $(patsubst %/,%,$(dir $(SELF)))
include $(PROJECT_ROOT)/bin.mk

CFLAGS += -I$(PROJECT_ROOT)/../../..
LDFLAGS += -L$(PROJECT_ROOT)/../../build/lib -lac1
DY_FLAGS +=
TEST_CFLAGS +=
TEST_LDFLAGS += -L$(PROJECT_ROOT)/../../build/lib -lac1
LD_LIBRARY_PATH := $(LD_LIBRARY_PATH):$(PROJECT_ROOT)/../../build/lib
DYLD_LIBRARY_PATH := $(DYLD_LIBRARY_PATH):$(PROJECT_ROOT)/../../build/lib

.PHONY: all
all:
	make -C $(PROJECT_ROOT)/../.. build
	$(MAKE_REC) build

.PHONY: clean-all
clean-all:
	make -C $(PROJECT_ROOT)/../.. clean
	$(MAKE_REC) clean

.PHONY: ext
ext:
	@echo "$(call blue,# Extended Variables)"
	@echo "CFLAGS=$(CFLAGS);"
	@echo "LDFLAGS=$(LDFLAGS);"
	@echo "DY_FLAGS=$(DY_FLAGS);"
	@echo "TEST_CFLAGS=$(TEST_CFLAGS);"
	@echo "TEST_LDFLAGS=$(TEST_LDFLAGS);"
	@echo "LD_LIBRARY_PATH=$(LD_LIBRARY_PATH);"
	@echo "DYLD_LIBRARY_PATH=$(DYLD_LIBRARY_PATH);"
