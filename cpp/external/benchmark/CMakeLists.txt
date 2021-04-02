# Copyright (c) 2011-2021, The DART development contributors

include(FetchContent)

# GoogleBenchmark
fetchcontent_declare(
  googlebenchmark GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG v1.5.2
)
fetchcontent_getproperties(googlebenchmark)
function(add_gbench_subdirectory)
  set(BUILD_SHARED_LIBS OFF)
  # Adds the targets: gtest, gtest_main, gmock, gmock_main
  add_subdirectory(
    ${googlebenchmark_SOURCE_DIR} ${googlebenchmark_BINARY_DIR}
    EXCLUDE_FROM_ALL
  )
endfunction()
if(NOT googlebenchmark_POPULATED)
  fetchcontent_populate(googlebenchmark)

  # Prevent GoogleBenchmark from building tests
  set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
  set(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE BOOL "" FORCE)

  # Prevent GoogleBenchmark from enabling install
  set(BENCHMARK_ENABLE_INSTALL OFF CACHE BOOL "" FORCE)

  # Adds the targets: gtest, gtest_main, gmock, gmock_main
  add_gbench_subdirectory()
endif()
