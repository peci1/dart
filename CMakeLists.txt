# Copyright (c) 2011-2021, The DART development contributors

# ==============================================================================
# Basic Project Setup
# ==============================================================================

# CMake 3.10.2, the default version of Ubuntu 18.04 LTS
cmake_minimum_required(VERSION 3.10.2 FATAL_ERROR)

# Policy settings
if(POLICY CMP0074)
  cmake_policy(SET CMP0074 NEW)
endif()
if(POLICY CMP0072)
  cmake_policy(SET CMP0072 NEW)
endif()

# Keep the version v0.0.Z until the first release to the public
set(DART_VERSION_MAJOR 8)
set(DART_VERSION_MINOR 0)
set(DART_VERSION_PATCH 0)
set(DART_VERSION
    "${DART_VERSION_MAJOR}.${DART_VERSION_MINOR}.${DART_VERSION_PATCH}"
)
project(dart VERSION ${DART_VERSION} LANGUAGES CXX)

# Add <project>/cmake to CMAKE_MODULE_PATH
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

# Include utility modules
include(GNUInstallDirs)
include(dart_functions)

# ==============================================================================
# Build Options
# ==============================================================================

# Binary options
dart_option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
dart_option(DART_VERBOSE "Print detailed build settings" OFF)
dart_option(DART_BUILD_TESTS "Build tests" ON)
dart_option(DART_BUILD_BENCHMARKS "Build benchmarks" ON)
dart_option(DART_BUILD_EXAMPLES "Build Examples" ON)
dart_option(DART_BUILD_PYTHON_BINDING "Build Python bindings" ON)
dart_option(
  DART_ENABLE_CODECOV "Enable code coverage reporting using Codecov" OFF
)

dart_print_options()

# Build type
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE
      RelWithDebInfo
      CACHE
        STRING
        "Choose the type of build, options are: Debug | Release | RelWithDebInfo | MinSizeRel"
        FORCE
  )
endif()
if(NOT CMAKE_BUILD_TYPE STREQUAL Debug AND DART_ENABLE_CODECOV)
  message(
    FATAL_ERROR
      "DART_ENABLE_CODECOV=${DART_ENABLE_CODECOV} and CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} are in conflict. Change one of the option."
  )
endif()

# ==============================================================================
# Find Dependencies
#
# Note: If you add new dependencies here, then please make sure to update
# cmake/dart-config.cmake.in as well.
# ==============================================================================

# Eigen3
find_package(Eigen3 3.3.4 REQUIRED CONFIG)
if(Eigen3_FOUND AND NOT TARGET Eigen3::Eigen)
  add_library(Eigen3::Eigen INTERFACE IMPORTED)
  set_target_properties(
    Eigen3::Eigen PROPERTIES INTERFACE_INCLUDE_DIRECTORIES
                             "${EIGEN3_INCLUDE_DIRS}"
  )
endif()

# ==============================================================================
# C++ Project Build
# ==============================================================================

# Enable 'test' target
if(DART_BUILD_TESTS)
  include(CTest)
  enable_testing()
endif()

# Include the C++ project directory
add_subdirectory(cpp)

# ==============================================================================
# Python Binding
# ==============================================================================
if(DART_BUILD_PYTHON_BINDING)
  add_subdirectory(python)
endif()

# ==============================================================================
# Code Formatting
# ==============================================================================
dart_clang_format_setup(VERSION 10)
dart_clang_format_add_targets()
