cmake_minimum_required(VERSION 3.22)

set(ELF ${CMAKE_BINARY_DIR}/castlevania.elf)
set(ROM ${CMAKE_BINARY_DIR}/castlevania.z64)
set(BASEROM ${CMAKE_SOURCE_DIR}/baserom.z64)
set(SPLAT ${CMAKE_SOURCE_DIR}/tools/splat/split.py)
set(SPLAT_CONFIG ${CMAKE_SOURCE_DIR}/castlevania.yaml)
set(DECOMPRESS ${CMAKE_SOURCE_DIR}/tools/decompress.py)

# Ensure Python is installed and install required development packages
find_package(Python REQUIRED COMPONENTS Interpreter)
if(Python_FOUND)
  execute_process(
    COMMAND ${Python_EXECUTABLE} -m pip install -r ${CMAKE_SOURCE_DIR}/requirements.txt
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_FILE ${CMAKE_BINARY_DIR}/pip.log)
  execute_process(COMMAND pre-commit install WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
  execute_process(
    COMMAND ${Python_EXECUTABLE} ${DECOMPRESS} ${BASEROM} ${CMAKE_SOURCE_DIR}/baserom_uncompressed.z64
    OUTPUT_FILE ${CMAKE_BINARY_DIR}/decompress.log
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
  execute_process(
    COMMAND ${Python_EXECUTABLE} ${SPLAT} ${SPLAT_CONFIG} --disassemble-all
    OUTPUT_FILE ${CMAKE_BINARY_DIR}/splat.log
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
else()
  message(FATAL_ERROR "Python is required!")
endif()

# Ensure Git is installed and update all submodules
find_package(Git REQUIRED)
if(Git_FOUND)
  execute_process(COMMAND ${Git_EXECUTABLE} submodule update --init --recursive WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
else()
  message(FATAL_ERROR "Git is required!")
endif()

# Install IDO compilers
execute_process(COMMAND ${CMAKE_COMMAND} -P ${CMAKE_SOURCE_DIR}/cmake/IDO.cmake WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

set(CROSS mips-linux-gnu-)

find_program(
  OBJCOPY_EXECUTABLE
  NAMES ${CROSS}objcopy
  DOC "objcopy executable location")

set(CMAKE_ASM_COMPILER ${CROSS}as)
set(CMAKE_ASM_COMPILE_OBJECT "<CMAKE_ASM_COMPILER> <DEFINES> <INCLUDES> <FLAGS> -o <OBJECT> <SOURCE>")
set(CMAKE_C_COMPILER_LAUNCHER ${Python_EXECUTABLE} ${CMAKE_SOURCE_DIR}/tools/asm-processor/build.py)
set(CMAKE_C_COMPILER
    ${CMAKE_SOURCE_DIR}/tools/ido/linux/7.1/cc
    --
    ${CMAKE_ASM_COMPILER}
    -I${CMAKE_SOURCE_DIR}/include
    -march=vr4300
    -EB
    --)
set(CMAKE_C_COMPILER_WORKS TRUE)
set(CMAKE_C_LINK_EXECUTABLE "${CROSS}ld <LINK_FLAGS> <OBJECTS> -o <TARGET>.elf")

# set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

project(
  Castlevania
  VERSION 0.0.1
  LANGUAGES C ASM
  DESCRIPTION "Decompilation of Castlevania for the Nintendo 64"
  HOMEPAGE_URL "https://github.com/blazkowolf/c64")

include(cmake/PreventInSourceBuilds.cmake)

# set(GENERATED_ASM_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/asm/header.s ${CMAKE_CURRENT_SOURCE_DIR}/asm/1000.s
# ${CMAKE_CURRENT_SOURCE_DIR}/asm/1370.s ${CMAKE_CURRENT_SOURCE_DIR}/asm/data/90920.data.s
# ${CMAKE_CURRENT_SOURCE_DIR}/asm/data/A8420.bss.s) set(C_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/gamestate.c)
# set(GENERATED_BINS ${CMAKE_CURRENT_SOURCE_DIR}/assets/A8420.bin ${CMAKE_CURRENT_SOURCE_DIR}/assets/boot.bin)

file(
  GLOB_RECURSE
  GENERATED_ASM_SOURCES
  CONFIGURE_DEPENDS
  ${CMAKE_CURRENT_SOURCE_DIR}/asm/*.s)
file(
  GLOB_RECURSE
  C_SOURCES
  CONFIGURE_DEPENDS
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)
file(
  GLOB_RECURSE
  GENERATED_BINS
  CONFIGURE_DEPENDS
  ${CMAKE_CURRENT_SOURCE_DIR}/assets/*.bin
  ${CMAKE_CURRENT_SOURCE_DIR}/assets/*.png)

list(
  FILTER
  GENERATED_ASM_SOURCES
  EXCLUDE
  REGEX
  "^${CMAKE_CURRENT_SOURCE_DIR}/asm/nonmatchings/.*\\.s$")
list(
  FILTER
  C_SOURCES
  EXCLUDE
  REGEX
  "^${CMAKE_CURRENT_SOURCE_DIR}/src/data/.*\\.c$")

# add_custom_command( OUTPUT ${GENERATED_ASM_SOURCES} ${C_SOURCES} ${GENERATED_BINS} DEPENDS ${SPLAT_CONFIG}
# WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} COMMAND ${Python_EXECUTABLE} ARGS ${SPLAT} ${SPLAT_CONFIG} --disassemble-all >
# ${CMAKE_BINARY_DIR}/splat.log COMMENT "Split ${BASEROM}" VERBATIM)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/castlevania.dir/assets)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/castlevania.dir/assets/nisitenma_ichigo)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/castlevania.dir/assets/nisitenma_ichigo/code)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/castlevania.dir/assets/nisitenma_ichigo/map)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/castlevania.dir/assets/nisitenma_ichigo/map/castle_center)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/castlevania.dir/assets/nisitenma_ichigo/map/castle_keep)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/castlevania.dir/assets/nisitenma_ichigo/map/castle_wall)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/castlevania.dir/assets/nisitenma_ichigo/map/clock_tower)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/castlevania.dir/assets/nisitenma_ichigo/map/dracula_desert)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/castlevania.dir/assets/nisitenma_ichigo/map/duel_tower)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/castlevania.dir/assets/nisitenma_ichigo/map/ending)
file(MAKE_DIRECTORY
     ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/castlevania.dir/assets/nisitenma_ichigo/map/forest_of_silence)
file(MAKE_DIRECTORY
     ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/castlevania.dir/assets/nisitenma_ichigo/map/intro_narration_cutscene)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/castlevania.dir/assets/nisitenma_ichigo/map/room_of_clocks)
file(MAKE_DIRECTORY
     ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/castlevania.dir/assets/nisitenma_ichigo/map/rose_actrise_meet_room)
file(MAKE_DIRECTORY
     ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/castlevania.dir/assets/nisitenma_ichigo/map/tower_of_execution)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/castlevania.dir/assets/nisitenma_ichigo/map/tower_of_science)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/castlevania.dir/assets/nisitenma_ichigo/map/tower_of_sorcery)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/castlevania.dir/assets/nisitenma_ichigo/map/tunnel)
file(MAKE_DIRECTORY
     ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/castlevania.dir/assets/nisitenma_ichigo/map/underground_waterway)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/castlevania.dir/assets/nisitenma_ichigo/map/villa)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/castlevania.dir/assets/nisitenma_ichigo/overlay)
set(BIN_OBJECTS)
foreach(bin IN LISTS GENERATED_BINS)
  file(
    RELATIVE_PATH
    RELATIVE_BIN_FILE
    ${CMAKE_SOURCE_DIR}
    ${bin})
  set(BIN_OBJECT ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/castlevania.dir/${RELATIVE_BIN_FILE}.o)
  add_custom_command(
    OUTPUT ${BIN_OBJECT}
    DEPENDS ${bin}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMAND ${CROSS}ld ARGS -r -b binary -o ${BIN_OBJECT} ${bin}
    COMMENT "Building binary object ${BIN_OBJECT}"
    VERBATIM)
  list(APPEND BIN_OBJECTS ${BIN_OBJECT})
endforeach()

set_source_files_properties(${BIN_OBJECTS} PROPERTIES EXTERNAL_OBJECT TRUE GENERATED TRUE)

add_executable(castlevania ${GENERATED_ASM_SOURCES} ${C_SOURCES} ${BIN_OBJECTS})

add_custom_command(
  TARGET castlevania
  POST_BUILD
  COMMAND ${OBJCOPY_EXECUTABLE} ARGS ${ELF} ${ROM} -O binary
  COMMAND ${OBJCOPY_EXECUTABLE} ARGS -O binary --gap-fill 0x00 --pad-to 0xC00000 ${ELF} ${ROM}
  COMMENT "Converting ${ELF} executable into final ${ROM} ROM"
  VERBATIM)

# add_custom_command( TARGET castlevania POST_BUILD COMMAND ${CMAKE_COMMAND} -E compare_files ${BASEROM} ${ROM} COMMENT
# "Compare final ${ROM} ROM file to ${BASEROM}" VERBATIM)

target_compile_definitions(castlevania PRIVATE $<$<COMPILE_LANGUAGE:C>:_LANGUAGE_C>)

target_compile_options(
  castlevania
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
  castlevania
  PRIVATE $<$<COMPILE_LANGUAGE:ASM>:${CMAKE_SOURCE_DIR}/include>
          $<$<COMPILE_LANGUAGE:C>:${CMAKE_SOURCE_DIR}/include
          ${CMAKE_SOURCE_DIR}/include/ultra64
          ${CMAKE_SOURCE_DIR}/include/game
          ${CMAKE_SOURCE_DIR}/assets>)

target_link_options(
  castlevania
  PRIVATE
  -T${CMAKE_SOURCE_DIR}/linker/castlevania.ld
  -T${CMAKE_SOURCE_DIR}/linker/undefined_funcs.ld
  -T${CMAKE_SOURCE_DIR}/linker/auto/undefined_funcs_auto.ld
  -T${CMAKE_SOURCE_DIR}/linker/auto/undefined_syms_auto.ld)
