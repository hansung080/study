# Edit this makefile for your project.

SELF := $(firstword $(MAKEFILE_LIST))
PROJECT_ROOT := $(patsubst %/,%,$(dir $(SELF)))
include $(PROJECT_ROOT)/lib.mk

CFLAGS += -I$(PROJECT_ROOT)/..
LDFLAGS += -L$(PROJECT_ROOT)/../ac1/build/lib -lac1
TEST_CFLAGS += -I$(PROJECT_ROOT)/..
TEST_LDFLAGS += -L$(PROJECT_ROOT)/../ac1/build/lib -lac1
LD_LIBRARY_PATH := $(LD_LIBRARY_PATH):$(PROJECT_ROOT)/../ac1/build/lib
DYLD_LIBRARY_PATH := $(DYLD_LIBRARY_PATH):$(PROJECT_ROOT)/../ac1/build/lib

.PHONY: all
all:
	make -C $(PROJECT_ROOT)/../ac1 build
	$(MAKE_REC) build

.PHONY: clean-all
clean-all:
	make -C $(PROJECT_ROOT)/../ac1 clean
	$(MAKE_REC) clean

.PHONY: ext
ext:
	@echo "$(call blue,# Extended Variables)"
	@echo "CFLAGS=$(CFLAGS);"
	@echo "LDFLAGS=$(LDFLAGS);"
	@echo "TEST_CFLAGS=$(TEST_CFLAGS);"
	@echo "TEST_LDFLAGS=$(TEST_LDFLAGS);"
	@echo "LD_LIBRARY_PATH=$(LD_LIBRARY_PATH);"
	@echo "DYLD_LIBRARY_PATH=$(DYLD_LIBRARY_PATH);"
