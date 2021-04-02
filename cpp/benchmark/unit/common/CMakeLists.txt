# Copyright (c) 2011-2021, The DART development contributors

# Glob all the test files
file(GLOB_RECURSE test_files RELATIVE "${CMAKE_CURRENT_LIST_DIR}"
     "benchmark_*.cpp"
)
if(test_files)
  list(SORT test_files)
endif()

set(link_libraries)
set(link_dart_libraries ${PROJECT_NAME}-common)

# Build the uint tests
dart_build_benchmarks(
  TYPE ${test_type}
  TEST_LIST test_targets
  SOURCES ${test_files}
  LINK_LIBRARIES ${link_libraries}
  LINK_DART_LIBRARIES ${link_dart_libraries}
  TARGET_PREFIX common
)
