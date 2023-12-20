cmake_minimum_required(VERSION 3.22)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

set(TARGET castlevania)
set(ELF ${CMAKE_BINARY_DIR}/${TARGET})
set(ROM ${CMAKE_BINARY_DIR}/${TARGET}.z64)
set(BASEROM ${CMAKE_SOURCE_DIR}/baserom.z64)
set(SPLAT ${CMAKE_SOURCE_DIR}/tools/splat/split.py)
set(SPLAT_CONFIG ${CMAKE_SOURCE_DIR}/${TARGET}.yaml)
set(DECOMPRESS ${CMAKE_SOURCE_DIR}/tools/decompress.py)

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
  COMMAND ${CMAKE_OBJCOPY} ARGS -O binary --gap-fill 0x00 --pad-to 0xC00000 ${ELF} ${ROM}
  COMMENT "Converting ${ELF} executable into final ${ROM} ROM"
  VERBATIM)

add_custom_command(
  TARGET ${TARGET}
  POST_BUILD
  COMMAND sha1sum ARGS ${ROM}
  COMMAND sha1sum ARGS -c ${CMAKE_SOURCE_DIR}/${TARGET}.sha1
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  COMMENT "Comparing ${ROM} ROM file to ${BASEROM}"
  VERBATIM)

target_compile_definitions(${TARGET} PRIVATE $<$<COMPILE_LANGUAGE:C>:_LANGUAGE_C>)

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
          513,649,838>)

target_include_directories(
  ${TARGET}
  PRIVATE $<$<COMPILE_LANGUAGE:ASM>:${CMAKE_SOURCE_DIR}/include>
          $<$<COMPILE_LANGUAGE:C>:${CMAKE_SOURCE_DIR}/include
          ${CMAKE_SOURCE_DIR}/include/ultra64
          ${CMAKE_SOURCE_DIR}/include/game
          ${CMAKE_SOURCE_DIR}/assets>)

target_link_options(
  ${TARGET}
  PRIVATE
  -T${CMAKE_SOURCE_DIR}/linker/${TARGET}.ld
  -T${CMAKE_SOURCE_DIR}/linker/auto/undefined_funcs_auto.ld
  -T${CMAKE_SOURCE_DIR}/linker/auto/undefined_syms_auto.ld)
