# Copyright (c) 2011-2021, The DART development contributors

set(DART_CPP_PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(DART_CPP_PROJECT_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})

# ==============================================================================
# CodeCov settings
# ==============================================================================
# Code Coverage Configuration
add_library(coverage_config INTERFACE)

if(DART_ENABLE_CODECOV)
  # Add required flags (GCC & LLVM/Clang)
  target_compile_options(
    coverage_config
    INTERFACE -O0 # no optimization
              -g # generate debug info
              --coverage # sets all required flags
  )
  if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.13)
    target_link_options(coverage_config INTERFACE --coverage)
  else()
    target_link_libraries(coverage_config INTERFACE --coverage)
  endif()
endif()

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
