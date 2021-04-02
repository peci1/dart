# Copyright (c) 2011-2021, The DART development contributors

if(DART_BUILD_TESTS)
  add_subdirectory(googletest)
endif()

if(DART_BUILD_BENCHMARKS)
  add_subdirectory(benchmark)
endif()
