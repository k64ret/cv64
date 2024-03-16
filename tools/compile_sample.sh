#!/usr/bin/env bash
../tools/ido/linux/7.1/cc       \
  -c                            \
  -Wab,-r4300_mul               \
  -non_shared                   \
  -G0                           \
  -Xcpluscomm                   \
  -mips2                        \
  -O2                           \
  -fullwarn                     \
  -woff 513,594,596,649,712,838 \
  -D_LANGUAGE_C -DF3DEX_GBI_2   \
  "$@"
