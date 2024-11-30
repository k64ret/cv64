cmake_minimum_required(VERSION 3.22)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

set(TOOLS_DIR ${CMAKE_SOURCE_DIR}/tools)

set(TARGET castlevania)
set(ELF ${CMAKE_BINARY_DIR}/${TARGET})
set(ROM ${CMAKE_BINARY_DIR}/${TARGET}.z64)
set(BASEROM ${CMAKE_SOURCE_DIR}/baserom.z64)
set(BASEROM_UNCOMPRESSED ${CMAKE_SOURCE_DIR}/baserom_uncompressed.z64)
set(SPLAT_CONFIG ${CMAKE_SOURCE_DIR}/${TARGET}.yaml)
set(TORCH ${TOOLS_DIR}/Torch/cmake-build-release/torch)
set(DECOMPRESS ${CMAKE_SOURCE_DIR}/tools/decompress.py)
set(COMPRESS ${CMAKE_SOURCE_DIR}/tools/compress.py)

# Enable compression and check the ROM's sha1sum. At the moment this is only useful for debugging non-matching issues
# regarding compressed files. Enabled by default to build a matching ROM.
option(compress "Compress the ROM and check sha1sum" TRUE)

include(cmake/Prerequisites.cmake)

project(
  ${TARGET}
  VERSION 0.0.1
  LANGUAGES C ASM
  DESCRIPTION "Decompilation of Castlevania for the Nintendo 64"
  HOMEPAGE_URL "https://github.com/blazkowolf/cv64")

include(cmake/PreventInSourceBuilds.cmake)
include(cmake/CreateBinaryObjects.cmake)

# set(GENERATED_ASM_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/asm/header.s ${CMAKE_CURRENT_SOURCE_DIR}/asm/1000.s
# ${CMAKE_CURRENT_SOURCE_DIR}/asm/1370.s ${CMAKE_CURRENT_SOURCE_DIR}/asm/data/90920.data.s
# ${CMAKE_CURRENT_SOURCE_DIR}/asm/data/A8420.bss.s) set(C_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/gamestate.c)
# set(GENERATED_BINS ${CMAKE_CURRENT_SOURCE_DIR}/assets/A8420.bin ${CMAKE_CURRENT_SOURCE_DIR}/assets/boot.bin)

# add_custom_command( OUTPUT ${GENERATED_ASM_SOURCES} ${C_SOURCES} ${GENERATED_BINS} DEPENDS ${SPLAT_CONFIG}
# WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} COMMAND ${PYTHON_EXECUTABLE} ARGS ${SPLAT} ${SPLAT_CONFIG} --disassemble-all >
# ${CMAKE_BINARY_DIR}/splat.log COMMENT "Split ${BASEROM}" VERBATIM)

add_executable(${TARGET} ${BIN_OBJECTS})

add_subdirectory(asm)
add_subdirectory(src)

add_custom_command(
  TARGET ${TARGET}
  POST_BUILD
  COMMAND ${CMAKE_OBJCOPY} ARGS ${ELF} ${ROM} -O binary
  COMMAND ${CMAKE_OBJCOPY} ARGS -O binary --gap-fill 0x00 --pad-to 0x01000000 ${ELF} ${ROM}
  COMMENT "Converting ${ELF} executable into final ${ROM} ROM"
  VERBATIM)

# Compress build/castlevania.z64
if(compress)
  add_custom_command(
    TARGET ${TARGET}
    POST_BUILD
    COMMAND ${Python_EXECUTABLE} ARGS ${COMPRESS} ${ROM} ${ROM}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Compressing Nisitema-Ichigo assets in ${ROM} ROM file"
    VERBATIM)

  add_custom_command(
    TARGET ${TARGET}
    POST_BUILD
    COMMAND sha1sum ARGS ${ROM}
    COMMAND sha1sum ARGS -c ${CMAKE_SOURCE_DIR}/${TARGET}.sha1
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Comparing ${ROM} ROM file to ${BASEROM}"
    VERBATIM)
endif()

target_compile_definitions(${TARGET} PRIVATE $<$<COMPILE_LANGUAGE:C>:_LANGUAGE_C F3DEX_GBI_2>)

target_compile_options(
  ${TARGET}
  PRIVATE $<$<COMPILE_LANGUAGE:ASM>:-march=vr4300
          -EB>
          $<$<COMPILE_LANGUAGE:C>:-Wab,-r4300_mul
          -non_shared
          -G0
          -Xcpluscomm
          -mips2
          -O2
          -verbose
          -fullwarn
          -woff
          513,594,596,649,712,838>)

target_include_directories(
  ${TARGET}
  PRIVATE $<$<COMPILE_LANGUAGE:ASM>:${CMAKE_SOURCE_DIR}/include>
          $<$<COMPILE_LANGUAGE:C>:${CMAKE_SOURCE_DIR}/include
          ${CMAKE_SOURCE_DIR}/include/ultra64
          ${CMAKE_SOURCE_DIR}/include/game
          ${CMAKE_SOURCE_DIR}/assets
          ${CMAKE_SOURCE_DIR}/include/assets>)

target_link_options(
  ${TARGET}
  PRIVATE
  -T${CMAKE_SOURCE_DIR}/linker/${TARGET}.ld
  -T${CMAKE_SOURCE_DIR}/linker/auto/undefined_funcs_auto.ld
  -T${CMAKE_SOURCE_DIR}/linker/auto/undefined_syms_auto.ld
  -Map
  ${ELF}.map)
