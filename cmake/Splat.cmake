# Makes `target` depend on Splat
function(splat_add_target target)
  cmake_parse_arguments(
    ARG
    ""
    "CONFIG;ROM;EXECUTABLE"
    ""
    ${ARGN})

  if(NOT ARG_EXECUTABLE)
    find_program(ARG_EXECUTABLE splat REQUIRED)
  endif()

  set(stamp "${CMAKE_CURRENT_BINARY_DIR}/${target}.stamp")

  add_custom_command(
    OUTPUT "${stamp}"
    COMMAND "${ARG_EXECUTABLE}" split --verbose "${ARG_CONFIG}"
    COMMAND "${CMAKE_COMMAND}" -E touch "${stamp}"
    DEPENDS "${ARG_CONFIG}" "${ARG_ROM}"
    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
    COMMENT "Running Splat"
    VERBATIM)

  add_custom_target(
    "${target}"
    DEPENDS "${stamp}"
    COMMENT "${target} depends on Splat")
endfunction()
