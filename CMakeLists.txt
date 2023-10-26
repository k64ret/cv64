cmake_minimum_required(VERSION 3.22)

set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

project(
  Castlevania
  VERSION 0.0.1
  LANGUAGES C ASM
  DESCRIPTION "Decompilation of Castlevania for the Nintendo 64"
  HOMEPAGE_URL "https://github.com/blazkowolf/c64")

include(cmake/PreventInSourceBuilds.cmake)

add_custom_command(
  OUTPUT ${CMAKE_SOURCE_DIR}/asm/header.s
         ${CMAKE_SOURCE_DIR}/asm/1000.s
         ${CMAKE_SOURCE_DIR}/asm/1060.s
         ${CMAKE_SOURCE_DIR}/asm/data/90CA0.data.s
         ${CMAKE_SOURCE_DIR}/asm/data/A87C0.bss.s
         ${CMAKE_SOURCE_DIR}/assets/A87C0.bin
         ${CMAKE_SOURCE_DIR}/assets/boot.bin
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/castlevania.yaml
  COMMAND python3 ARGS ${CMAKE_CURRENT_SOURCE_DIR}/tools/splat/split.py ${CMAKE_CURRENT_SOURCE_DIR}/castlevania.yaml
          --stdout-only --disassemble-all > ${CMAKE_BINARY_DIR}/splat.log
  COMMENT "Generate assembly"
  VERBATIM)

add_executable(
  castlevania
  asm/header.s
  asm/1000.s
  asm/1060.s
  asm/data/90CA0.data.s
  asm/data/A87C0.bss.s)
target_compile_options(castlevania PRIVATE -Wa,-march=vr4300,-G0,-EB,-mips2,-32)
target_include_directories(castlevania PRIVATE include)
target_link_options(
  castlevania
  PRIVATE
  -T
  linker_scripts/castlevania.ld
  -T
  linker_scripts/auto/undefined_funcs_auto.txt
  -T
  linker_scripts/auto/undefined_syms_auto.txt)

# add_subdirectory(tools)
