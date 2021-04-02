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
set(DART_VERSION "8.0.0")
project(dart8 VERSION ${DART_VERSION} LANGUAGES CXX)

# Add <project>/cmake to CMAKE_MODULE_PATH
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

# ==============================================================================
# Build Options
# ==============================================================================

option(DART_VERBOSE "Print detailed build settings" OFF)

# ==============================================================================
# Find Dependencies
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
# C++ Project
# ==============================================================================

add_subdirectory(cpp)
