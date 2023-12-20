file(
  GLOB_RECURSE
  GENERATED_BINS
  CONFIGURE_DEPENDS
  ${CMAKE_CURRENT_SOURCE_DIR}/assets/*.bin
  ${CMAKE_CURRENT_SOURCE_DIR}/assets/*.png)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${TARGET}.dir/assets)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${TARGET}.dir/assets/nisitenma_ichigo)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${TARGET}.dir/assets/nisitenma_ichigo/code)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${TARGET}.dir/assets/nisitenma_ichigo/map)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${TARGET}.dir/assets/nisitenma_ichigo/map/castle_center)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${TARGET}.dir/assets/nisitenma_ichigo/map/castle_keep)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${TARGET}.dir/assets/nisitenma_ichigo/map/castle_wall)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${TARGET}.dir/assets/nisitenma_ichigo/map/clock_tower)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${TARGET}.dir/assets/nisitenma_ichigo/map/dracula_desert)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${TARGET}.dir/assets/nisitenma_ichigo/map/duel_tower)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${TARGET}.dir/assets/nisitenma_ichigo/map/ending)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${TARGET}.dir/assets/nisitenma_ichigo/map/forest_of_silence)
file(MAKE_DIRECTORY
     ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${TARGET}.dir/assets/nisitenma_ichigo/map/intro_narration_cutscene)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${TARGET}.dir/assets/nisitenma_ichigo/map/room_of_clocks)
file(MAKE_DIRECTORY
     ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${TARGET}.dir/assets/nisitenma_ichigo/map/rose_actrise_meet_room)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${TARGET}.dir/assets/nisitenma_ichigo/map/tower_of_execution)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${TARGET}.dir/assets/nisitenma_ichigo/map/tower_of_science)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${TARGET}.dir/assets/nisitenma_ichigo/map/tower_of_sorcery)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${TARGET}.dir/assets/nisitenma_ichigo/map/tunnel)
file(MAKE_DIRECTORY
     ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${TARGET}.dir/assets/nisitenma_ichigo/map/underground_waterway)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${TARGET}.dir/assets/nisitenma_ichigo/map/villa)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${TARGET}.dir/assets/nisitenma_ichigo/overlay)
set(BIN_OBJECTS)
foreach(bin IN LISTS GENERATED_BINS)
  file(
    RELATIVE_PATH
    RELATIVE_BIN_FILE
    ${CMAKE_SOURCE_DIR}
    ${bin})
  set(BIN_OBJECT ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${TARGET}.dir/${RELATIVE_BIN_FILE}.o)
  add_custom_command(
    OUTPUT ${BIN_OBJECT}
    DEPENDS ${bin}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMAND ${CMAKE_LINKER} ARGS -r -b binary -o ${BIN_OBJECT} ${bin}
    COMMENT "Building binary object ${BIN_OBJECT}"
    VERBATIM)
  list(APPEND BIN_OBJECTS ${BIN_OBJECT})
endforeach()

set_source_files_properties(${BIN_OBJECTS} PROPERTIES EXTERNAL_OBJECT TRUE GENERATED TRUE)
