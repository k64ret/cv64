# vim:ft=make

MAKEFLAGS += --no-builtin-rules

.SECONDARY:

COMPARE ?= 1

BASEROM = baserom.z64
TARGET  = castlevania

# Fail early
ifeq ($(wildcard $(BASEROM)),)
	$(error $(BASEROM) not found.)
endif

BUILD_DIR  = build
ROM       := $(BUILD_DIR)/$(TARGET).z64
ELF       := $(BUILD_DIR)/$(TARGET).elf
LD_SCRIPT := linker_scripts/$(TARGET).ld

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

PYTHON      = python3
SPLAT_YAML := $(TARGET).yaml
SPLAT      := $(PYTHON) tools/splat/split.py $(SPLAT_YAML)
DIFF        = diff

CROSS    = mips-linux-gnu
AS      := $(CROSS)-as
LD      := $(CROSS)-ld
OBJDUMP := $(CROSS)-objdump
OBJCOPY := $(CROSS)-objcopy
STRIP   := $(CROSS)-strip

SPLAT_FLAGS      = --stdout-only --disassemble-all
SPLAT_TIMESTAMP := $(BUILD_DIR)/.splat_timestamp

ASM_DEFINES  =
ASM_INCLUDES = -I./include
ASM_FLAGS    = -march=vr4300 -EB

LD_FLAGS    := -T linker_scripts/auto/undefined_syms_auto.ld \
               -T linker_scripts/auto/undefined_funcs_auto.ld \
               -T linker_scripts/undefined_funcs.ld \
               -T $(LD_SCRIPT) \
               --no-check-sections

# SRC_DIRS  := $(shell find src -type d)
# ASM_DIRS  := $(shell find asm -type d -not -path "asm/nonmatchings/*" -not -path "asm/lib/*")
# BIN_DIRS  := $(shell find assets -type d)
#
# C_FILES   := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
# ASM_FILES := $(foreach dir,$(ASM_DIRS),$(wildcard $(dir)/*.s))
# BIN_FILES := $(foreach dir,$(BIN_DIRS),$(wildcard $(dir)/*.bin))
#
# O_FILES   := $(foreach file,$(C_FILES:.c=.o),$(BUILD_DIR)/$(file)) \
#              $(foreach file,$(ASM_FILES:.s=.o),$(BUILD_DIR)/$(file)) \
#              $(foreach file,$(BIN_FILES:.bin=.o),$(BUILD_DIR)/$(file))

O_FILES := $(shell $(PYTHON) tools/splat_objects.py $(SPLAT_YAML))
DEP_FILES := $(O_FILES:.o=.d)

-include $(DEP_FILES)

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

# Link the .o object files into an .elf file
$(ELF): $(O_FILES)
	$(LD) $(LD_FLAGS) -o $@

# Convert the .elf file into the final .z64 ROM file
$(ROM): $(ELF)
	$(OBJCOPY) $< $@ -O binary
	$(OBJCOPY) -O binary --gap-fill 0xFF --pad-to 0x1000000 $< $@
ifeq ($(COMPARE),1)
	diff $(BASEROM) $(ROM) \
		&& echo OK \
		|| (echo FAILED\ \($(ROM)\ built,\ but\ differs\ from\ $(BASEROM)\) && false)
endif

# Print target for debugging
print-%: ; $(info $* is a $(flavor $*) variable set to [$($*)]) @true
