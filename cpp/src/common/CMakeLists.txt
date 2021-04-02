# Copyright (c) 2011-2021, The DART development contributors

# Set target name
set(module_name common)
set(target_name ${PROJECT_NAME}-${module_name})
set(dependency_modules)

# Get header and source files
file(
  GLOB_RECURSE headers
  "${DART_CPP_PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/${module_name}/*.hpp"
)
file(GLOB_RECURSE sources "*.cpp")

# Add library
add_library(${target_name} ${headers} ${sources})

# Set include directory
target_include_directories(
  ${target_name}
  PUBLIC $<BUILD_INTERFACE:${DART_CPP_PROJECT_SOURCE_DIR}/include>
         $<BUILD_INTERFACE:${DART_CPP_PROJECT_BINARY_DIR}/include>
         $<INSTALL_INTERFACE:include>
)

# Set link libraries
if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 8.0)
  target_link_libraries(${target_name} PUBLIC "stdc++fs")
endif()
target_link_libraries(
  ${target_name} PUBLIC ${dependency_modules} ${CMAKE_DL_LIBS}
)

# Set compile features
target_compile_features(${target_name} PUBLIC cxx_std_17)

# Set compile definitions
target_compile_definitions(${target_name} PUBLIC)
