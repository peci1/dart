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
  add_subdirectory(test)
endif()

# ==============================================================================
# Benchmark
# ==============================================================================
if(DART_BUILD_BENCHMARKS)
  add_subdirectory(benchmark)
endif()
