cmake_minimum_required(VERSION 3.22)

set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

project(
  Castlevania
  VERSION 0.0.1
  LANGUAGES C
  DESCRIPTION "Decompilation of Castlevania for the Nintendo 64"
  HOMEPAGE_URL "https://github.com/blazkowolf/c64")

include(cmake/PreventInSourceBuilds.cmake)

# add_subdirectory(tools)
