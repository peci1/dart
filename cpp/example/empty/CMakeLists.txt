# Copyright (c) 2011-2021, The DART development contributors

cmake_minimum_required(VERSION 3.10.2 FATAL_ERROR)

get_filename_component(example_name ${CMAKE_CURRENT_LIST_DIR} NAME)

project(${example_name})

set(required_libraries dart8-common)

if(DART_BUILD_EXAMPLES)
  dart_build_example_in_source(
    ${DART_EXAMPLE_PREFIX}${example_name} LINK_LIBRARIES ${required_libraries}
  )
  return()
endif()

find_package(dart8 8 REQUIRED CONFIG)

file(GLOB headers "*.cpp" "*.hpp")
file(GLOB sources "*.cpp" "*.hpp")
add_executable(${example_name} ${headers} ${sources})
target_link_libraries(${example_name} PUBLIC ${required_libraries})
