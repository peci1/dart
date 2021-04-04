# Copyright (c) 2011-2021, The DART development contributors

add_subdirectory(common)
add_subdirectory(math)

# Generate meta header for the project (i.e., dart/all.hpp)
get_property(modules GLOBAL PROPERTY DART_CPP_BUILDING_MODULES)
set(meta_headers )
foreach(module ${modules})
  list(APPEND meta_headers "dart/${module}/all.hpp")
endforeach()
dart_generate_meta_header(
  DESTINATION "all.hpp"
  HEADERS ${meta_headers}
  PREFIX_TO_REMOVE "${DART_CPP_PROJECT_SOURCE_DIR}/src/"
)
