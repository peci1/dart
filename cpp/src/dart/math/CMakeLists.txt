# Copyright (c) 2011-2021, The DART development contributors

# Set module name
set(module_name math)
set(target_name dart-${module_name})

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
  PUBLIC_LINK_LIBRARIES dart-common
  GENERATE_META_HEADER
)
