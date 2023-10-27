default_target: all
.PHONY: default_target

# Allow only one "make -f SomeOtherMakefile" at a time
.NOTPARALLEL:

# Silence nested `$(MAKE)`
$(VERBOSE)MAKESILENT = -s

# Suppress display of executed commands
$(VERBOSE).SILENT:

all:
	$(MAKE) $(MAKESILENT) -f make/Makefile all
.PHONY: all

clean:
	$(MAKE) $(MAKESILENT) -f make/Makefile clean
.PHONY: clean

help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... help"
.PHONY: help

print-%:
	$(MAKE) $(MAKESILENT) -f make/Makefile print-$*
.PHONY: print-%
