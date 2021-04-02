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
