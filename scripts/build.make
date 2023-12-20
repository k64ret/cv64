# vim:ft=make

# $(VERBOSE)MAKESILENT = -s
# $(VERBOSE).SILENT:

-include .make_options

MAKEFLAGS += --no-builtin-rules

# Don't delete intermediate files
.SECONDARY:

### Defaults ###

COMPARE              ?= 1
MIPS_BINUTILS_PREFIX ?= mips-linux-gnu-
PYTHON               ?= python3

################

TOOLS_DIR      = tools
LD_SCRIPTS_DIR = linker_scripts

# A real "chicken before the egg" scenario here with the yaml
BUILD_HELPER := $(PYTHON) $(TOOLS_DIR)/splat_objects.py castlevania.yaml
BUILD_DIR    := $(shell $(BUILD_HELPER) build_dir)
BASEROM      := $(shell $(BUILD_HELPER) baserom)
TARGET       := $(shell $(BUILD_HELPER) target)

# Fail early
ifeq ($(wildcard $(BASEROM)),)
	$(error $(BASEROM) not found.)
endif

ROM       := $(BUILD_DIR)/$(TARGET).z64
ELF       := $(BUILD_DIR)/$(TARGET).elf
LD_SCRIPT := $(LD_SCRIPTS_DIR)/$(TARGET).ld

include scripts/platform.make

ifeq ($(DETECTED_OS),windows)
	$(error Native Windows is currently unsupported - please use Windows Subsystem for Linux instead...)
else ifeq ($(DETECTED_OS),macos)
	MAKE = gmake
	CPPFLAGS += -xc++
endif

SPLAT_YAML := $(TARGET).yaml
SPLAT      := $(PYTHON) $(TOOLS_DIR)/splat/split.py $(SPLAT_YAML)
ASM_PROC   := $(PYTHON) $(TOOLS_DIR)/asm-processor/build.py
DIFF        = diff

CC     := $(TOOLS_DIR)/ido/$(DETECTED_OS)/7.1/cc
# CC     := $(TOOLS_DIR)/ido/$(DETECTED_OS)/5.3/cc

# CC_DEFINES =
CC_INCLUDES = -I./include -I./include/ultra64 -I./include/game
# Original suggested flags from here: https://github.com/simonlindholm/asm-processor#usage
# CC_FLAGS = -Wab,-r4300_mul -non_shared -G 0 -Xcpluscomm -g
CC_FLAGS = -Wab,-r4300_mul -non_shared -G0 -Xcpluscomm -mips2 -O2 -verbose -fullwarn

AS      := $(MIPS_BINUTILS_PREFIX)as
LD      := $(MIPS_BINUTILS_PREFIX)ld
OBJDUMP := $(MIPS_BINUTILS_PREFIX)objdump
OBJCOPY := $(MIPS_BINUTILS_PREFIX)objcopy
STRIP   := $(MIPS_BINUTILS_PREFIX)strip

SPLAT_FLAGS      = --disassemble-all
SPLAT_TIMESTAMP := $(BUILD_DIR)/.splat_timestamp

ASM_DEFINES  =
ASM_INCLUDES = -I./include
ASM_FLAGS    = -march=vr4300 -EB

LD_FLAGS    := -T $(LD_SCRIPTS_DIR)/auto/undefined_syms_auto.ld \
               -T $(LD_SCRIPTS_DIR)/auto/undefined_funcs_auto.ld \
               -T $(LD_SCRIPT) \
               --no-check-sections

O_FILES   := $(shell $(BUILD_HELPER) objects)
DEP_FILES := $(O_FILES:.o=.d) \
             $(O_FILES:.o=.asmproc.d)

-include $(DEP_FILES)

$(BUILD_DIR)/src/%.o: \
	CC := $(ASM_PROC) $(ASM_PROC_FLAGS) $(CC) -- $(AS) $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) --

all: $(ROM)
.PHONY: all

clean:
	$(RM) -r $(BUILD_DIR) asm assets
.PHONY: clean

$(BUILD_DIR):
	@mkdir -p $@

split: $(BUILD_DIR)
	$(SPLAT) $(SPLAT_FLAGS) > $(BUILD_DIR)/splat.log
	@touch $(SPLAT_TIMESTAMP)

$(SPLAT_TIMESTAMP): $(SPLAT_YAML) | $(BUILD_DIR)
	$(SPLAT) $(SPLAT_FLAGS) > $(BUILD_DIR)/splat.log
	@touch $@

asm/%.s: $(SPLAT_TIMESTAMP)
	@touch $@

assets/%.bin: $(SPLAT_TIMESTAMP)
	@touch $@

$(BUILD_DIR)/asm/%.o: asm/%.s | $(BUILD_DIR)
	@mkdir -p $(shell dirname $@)
	$(AS) $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) -o $@ $<

$(BUILD_DIR)/assets/%.o: assets/%.bin | $(BUILD_DIR)
	@mkdir -p $(shell dirname $@)
	$(LD) -r -b binary -o $@ $<

$(BUILD_DIR)/src/%.o: src/%.c | $(BUILD_DIR)
	@mkdir -p $(shell dirname $@)
	$(CC) $(CC_FLAGS) $(CC_DEFINES) $(CC_INCLUDES) -c -o $@ $<

# Link the .o object files into an .elf file
$(ELF): $(O_FILES)
	$(LD) $(LD_FLAGS) -o $@

# Convert the .elf file into the final .z64 ROM file
$(ROM): $(ELF)
	$(OBJCOPY) $< $@ -O binary
	$(OBJCOPY) -O binary --gap-fill 0x00 --pad-to 0xC00000 $< $@
ifeq ($(COMPARE),1)
	@diff $(BASEROM) $(ROM) \
		&& echo OK \
		|| (echo FAILED\ \($(ROM)\ built,\ but\ differs\ from\ $(BASEROM)\) && false)
endif

# Print target for debugging
print-%: ; $(info $* is a $(flavor $*) variable set to [$($*)]) @true
