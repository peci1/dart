# Copyright (c) 2011-2021, The DART development contributors

set(DART_CPP_PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(DART_CPP_PROJECT_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})

# ==============================================================================
# Add Source Directories
# ==============================================================================
add_subdirectory(external)
add_subdirectory(src)

# ==============================================================================
# Test
# ==============================================================================
if(DART_BUILD_TESTS)
  # valgrind settings
  #
  # NOTE: These settings must be placed before including CTest
  set(MEMORYCHECK_SUPPRESSIONS_FILE ${CMAKE_SOURCE_DIR}/.valgrind.supp
      CACHE FILEPATH "Valgrind suppressions file" FORCE
  )
  # --show-reachable is intentionally disabled to avoid false alarm for valgrind
  # + OpenMP/TBB
  #
  # See:
  # https://medium.com/@auraham/pseudo-memory-leaks-when-using-openmp-11a383cc4cf9
  set(MEMORYCHECK_COMMAND_OPTIONS
      "--verbose --leak-check=full --show-leak-kinds=definite --errors-for-leak-kinds=definite --error-exitcode=1 --track-origins=yes --trace-children=yes"
      CACHE STRING "Valgrind command options" FORCE
  )
  add_subdirectory(test)
endif()

# ==============================================================================
# Benchmark
# ==============================================================================
if(DART_BUILD_BENCHMARKS)
  add_subdirectory(benchmark)
endif()

# ==============================================================================
# Test
# ==============================================================================
if(DART_BUILD_EXAMPLES)
  set(DART_EXAMPLE_PREFIX EXAMPLE_)
  add_subdirectory(example)
endif()

# ==============================================================================
# Install Config and Version Files
# ==============================================================================
get_property(DART_BUILT_MODULES GLOBAL PROPERTY DART_CPP_BUILDING_MODULES)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  ${PROJECT_NAME}${DART_VERSION_MAJOR}-config-version.cmake
  VERSION ${DART_VERSION} COMPATIBILITY SameMajorVersion
)
configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/${PROJECT_NAME}-config.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}${DART_VERSION_MAJOR}-config.cmake"
  INSTALL_DESTINATION
    ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}${DART_VERSION_MAJOR}
)
install(
  FILES
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}${DART_VERSION_MAJOR}-config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}${DART_VERSION_MAJOR}-config-version.cmake"
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}${DART_VERSION_MAJOR}
)
