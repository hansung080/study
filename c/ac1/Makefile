# Edit this makefile for your project.

SELF := $(firstword $(MAKEFILE_LIST))
PROJECT_ROOT := $(patsubst %/,%,$(dir $(SELF)))
include $(PROJECT_ROOT)/lib.mk

CFLAGS +=
LDFLAGS +=
TEST_CFLAGS +=
TEST_LDFLAGS +=
LD_LIBRARY_PATH := $(LD_LIBRARY_PATH)
DYLD_LIBRARY_PATH := $(DYLD_LIBRARY_PATH)

.PHONY: all
all:
	$(MAKE_REC) build
	make -C $(PROJECT_ROOT)/apps/micromouse build
	make -C $(PROJECT_ROOT)/../ypds build

.PHONY: clean-all
clean-all:
	$(MAKE_REC) clean
	make -C $(PROJECT_ROOT)/apps/micromouse clean
	make -C $(PROJECT_ROOT)/../ypds clean

.PHONY: ext
ext:
	@echo "$(call blue,# Extended Variables)"
	@echo "CFLAGS=$(CFLAGS);"
	@echo "LDFLAGS=$(LDFLAGS);"
	@echo "TEST_CFLAGS=$(TEST_CFLAGS);"
	@echo "TEST_LDFLAGS=$(TEST_LDFLAGS);"
	@echo "LD_LIBRARY_PATH=$(LD_LIBRARY_PATH);"
	@echo "DYLD_LIBRARY_PATH=$(DYLD_LIBRARY_PATH);"
