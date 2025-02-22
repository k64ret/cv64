find_package(Python REQUIRED COMPONENTS Interpreter)

if(Python_FOUND)
  # Install Python dependencies
  execute_process(
    COMMAND ${Python_EXECUTABLE} -m pip install -U -r ${CMAKE_SOURCE_DIR}/requirements.txt
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_FILE ${CMAKE_BINARY_DIR}/pip.log)

  # Install pre-commit hooks
  execute_process(COMMAND pre-commit install WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

  # Decompress baserom
  execute_process(
    COMMAND ${Python_EXECUTABLE} ${DECOMPRESS} ${BASEROM} ${BASEROM_UNCOMPRESSED}
    OUTPUT_FILE ${CMAKE_BINARY_DIR}/decompress.log
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

  # Build Torch
  execute_process(COMMAND make -C ${TOOLS_DIR}/Torch type=release WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

  # Run Splat
  execute_process(
    COMMAND ${Python_EXECUTABLE} -m splat split --verbose ${SPLAT_CONFIG}
    OUTPUT_FILE ${CMAKE_BINARY_DIR}/splat.log
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

  # Run Torch Extract assets as source code files
  execute_process(
    COMMAND ${TORCH} code ${BASEROM_UNCOMPRESSED} -v
    OUTPUT_FILE ${CMAKE_BINARY_DIR}/torch.log
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

  # Extract header files
  execute_process(COMMAND ${TORCH} header ${BASEROM_UNCOMPRESSED} WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

  # Extract some data into humanly-readable formats (such as image data to .png)
  execute_process(COMMAND ${TORCH} modding export ${BASEROM_UNCOMPRESSED} WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
endif()

set(MIPS_BINUTILS_PREFIX mips-linux-gnu-)

# Install IDO compilers
execute_process(COMMAND ${CMAKE_COMMAND} -P ${CMAKE_SOURCE_DIR}/cmake/IDO.cmake WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

set(TOOLCHAIN_ASM_COMPILER_EXE ${MIPS_BINUTILS_PREFIX}as)
find_program(CMAKE_ASM_COMPILER ${TOOLCHAIN_ASM_COMPILER_EXE} HINTS "/usr/bin" REQUIRED)
set(CMAKE_ASM_COMPILE_OBJECT "<CMAKE_ASM_COMPILER> <DEFINES> <INCLUDES> <FLAGS> -o <OBJECT> <SOURCE>")

set(CMAKE_C_COMPILER_LAUNCHER ${Python_EXECUTABLE} ${TOOLS_DIR}/asm-processor/build.py)
find_program(TOOLCHAIN_C_COMPILER_EXE cc HINTS "${TOOLS_DIR}/ido/linux/7.1/" REQUIRED)
set(CMAKE_C_COMPILER
    ${TOOLCHAIN_C_COMPILER_EXE}
    --
    ${CMAKE_ASM_COMPILER}
    -I${CMAKE_SOURCE_DIR}/include
    -march=vr4300
    -EB
    --)
set(CMAKE_C_COMPILER_WORKS TRUE)

set(TOOLCHAIN_LINKER_EXE ${MIPS_BINUTILS_PREFIX}ld)
find_program(CMAKE_LINKER ${TOOLCHAIN_LINKER_EXE} HINTS "/usr/bin" REQUIRED)
set(CMAKE_C_LINK_EXECUTABLE "<CMAKE_LINKER> <LINK_FLAGS> <OBJECTS> -o <TARGET>")

set(TOOLCHAIN_OBJCOPY_EXE ${MIPS_BINUTILS_PREFIX}objcopy)
find_program(CMAKE_OBJCOPY ${TOOLCHAIN_OBJCOPY_EXE} HINTS "/usr/bin" REQUIRED)
