default_target: all
.PHONY: default_target

# Delete rule output on recipe error
.DELETE_ON_ERROR:

# Silence nested `$(MAKE)`
$(VERBOSE)MAKESILENT = -s

# Suppress display of executed commands
$(VERBOSE).SILENT:

UNAME_S := $(shell uname -s)
ifeq ($(OS),Windows_NT)
	$(error Native Windows is currently unsupported - please use Windows Subsystem for Linux instead...)
else ifeq ($(UNAME_S),Linux)
	DETECTED_OS = linux
else ifeq ($(UNAME_S),Darwin)
	DETECTED_OS = macos
	MAKE = gmake
	CPPFLAGS += -xc++
endif

include make/flags.make

include make/tools.make

all:
	$(info OS is $(OS))
.PHONY: all

clean:
	@rm -rf build asm assets
.PHONY: clean

# Print target for debugging
print-% : ; $(info $* is a $(flavor $*) variable set to [$($*)]) @true
