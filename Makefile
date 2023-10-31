default_target: all
.PHONY: default_target

# Allow only one "make -f SomeOtherMakefile" at a time
.NOTPARALLEL:

SHELL = /bin/sh -e

# Silence nested `$(MAKE)`
# $(VERBOSE)MAKESILENT = -s

# Suppress display of executed commands
$(VERBOSE).SILENT:

all:
	$(MAKE) $(MAKESILENT) -f scripts/ido.make all
	$(MAKE) $(MAKESILENT) -f scripts/build.make all
.PHONY: all

split:
	$(MAKE) $(MAKESILENT) -f scripts/build.make split
.PHONY: split

clean:
	$(MAKE) $(MAKESILENT) -f scripts/ido.make clean
	$(MAKE) $(MAKESILENT) -f scripts/build.make clean
.PHONY: clean

help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... split (run splat tool)"
	@echo "... clean"
	@echo "... help"
.PHONY: help

print-%:
	$(MAKE) $(MAKESILENT) -f scripts/build.make print-$*
.PHONY: print-%
