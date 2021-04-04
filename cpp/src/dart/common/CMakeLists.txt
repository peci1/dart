# Copyright (c) 2011-2021, The DART development contributors

# Set module name
set(module_name common)
set(target_name dart-${module_name})

# Link libraries
set(public_link_libraries ${CMAKE_DL_LIBS} coverage_config)
if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 8.0)
  list(APPEND public_link_libraries stdc++fs)
endif()

# Get header and source files
file(GLOB_RECURSE headers "*.hpp")
file(GLOB_RECURSE sources "*.cpp")

# Add module
dart_add_module(
  MODULE_NAME ${module_name}
  TARGET_NAME ${target_name}
  PROJECT_SOURCE_DIR ${DART_CPP_PROJECT_SOURCE_DIR}
  PROJECT_BINARY_DIR ${DART_CPP_PROJECT_BINARY_DIR}
  HEADERS ${headers}
  SOURCES ${sources}
  PUBLIC_LINK_LIBRARIES ${public_link_libraries}
  PUBLIC_COMPILE_FEATURES cxx_std_17
  GENERATE_META_HEADER
)
