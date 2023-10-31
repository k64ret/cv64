# vim:ft=make

include scripts/platform.make

IDO_URL_PREFIX    = https://github.com/decompals/ido-static-recomp/releases/latest/download
IDO_DIR           = tools/ido
IDO_5_3_ARTIFACT := ido-5.3-recomp-$(DETECTED_OS).tar.gz
IDO_7_1_ARTIFACT := ido-7.1-recomp-$(DETECTED_OS).tar.gz
IDO_5_3_URL      := $(IDO_URL_PREFIX)/$(IDO_5_3_ARTIFACT)
IDO_7_1_URL      := $(IDO_URL_PREFIX)/$(IDO_7_1_ARTIFACT)
IDO_5_3_DIR      := $(IDO_DIR)/$(DETECTED_OS)/5.3
IDO_7_1_DIR      := $(IDO_DIR)/$(DETECTED_OS)/7.1
IDO_5_3_CC       := $(IDO_5_3_DIR)/cc
IDO_7_1_CC       := $(IDO_7_1_DIR)/cc

all: $(IDO_5_3_CC) $(IDO_7_1_CC)
.PHONY: all

clean:
	$(RM) -r $(IDO_DIR)
.PHONY: clean

$(IDO_5_3_DIR):
	@mkdir -p $@

$(IDO_7_1_DIR):
	@mkdir -p $@

$(IDO_5_3_CC): | $(IDO_5_3_DIR)
	wget $(IDO_5_3_URL)
	tar xf $(IDO_5_3_ARTIFACT) -C $(IDO_5_3_DIR)
	$(RM) $(IDO_5_3_ARTIFACT)

$(IDO_7_1_CC): | $(IDO_7_1_DIR)
	wget $(IDO_7_1_URL)
	tar xf $(IDO_7_1_ARTIFACT) -C $(IDO_7_1_DIR)
	$(RM) $(IDO_7_1_ARTIFACT)
