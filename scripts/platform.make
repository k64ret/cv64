# vim:ft=make

UNAME_S := $(shell uname -s)
ifeq ($(OS),Windows_NT)
	DETECTED_OS = windows
else ifeq ($(UNAME_S),Linux)
	DETECTED_OS = linux
else ifeq ($(UNAME_S),Darwin)
	DETECTED_OS = macos
endif
