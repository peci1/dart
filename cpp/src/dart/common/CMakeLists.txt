# Copyright (c) 2011-2021, The DART development contributors

# Set module name
set(module_name common)
set(target_name ${PROJECT_NAME}${DART_VERSION_MAJOR}-${module_name})

# Link libraries
set(public_link_libraries ${CMAKE_DL_LIBS})
if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 8.0)
  list(APPEND public_link_libraries stdc++fs)
endif()

# Link options
set(public_link_options)

# Compile options
set(public_compile_options)

# CodeCov settings
if(DART_ENABLE_CODECOV)
  if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.13)
    list(APPEND public_link_options --coverage)
  else()
    list(APPEND public_link_libraries --coverage)
  endif()
  list(APPEND public_compile_options -O0 # no optimization
       -g # generate debug info
       --coverage # sets all required flags
  )
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
  PUBLIC_LINK_OPTIONS ${public_link_options}
  PUBLIC_COMPILE_FEATURES cxx_std_17
  PUBLIC_COMPILE_OPTIONS ${public_compile_options}
  GENERATE_META_HEADER
)
