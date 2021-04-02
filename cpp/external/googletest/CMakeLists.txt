include(FetchContent)

# NOTE: Find PythonInterp for Python 3 before GoogleTest finds it for Python 2
find_package(PythonInterp 3)

# GoogleTest
fetchcontent_declare(
  googletest GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.10.0
)
fetchcontent_getproperties(googletest)
function(add_gtest_subdirectory)
  set(BUILD_SHARED_LIBS OFF)
  add_subdirectory(
    ${googletest_SOURCE_DIR} ${googletest_BINARY_DIR} EXCLUDE_FROM_ALL
  )
endfunction()
if(NOT googletest_POPULATED)
  fetchcontent_populate(googletest)

  # Prevent GoogleTest from overriding our compiler/linker options when building
  # with Visual Studio
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  # Prevent GoogleTest from using PThreads
  set(gtest_disabl_pthreads ON CACHE BOOL "" FORCE)

  # Adds the targets: gtest, gtest_main, gmock, gmock_main
  add_gtest_subdirectory()

  # Silence std::tr1 warning on MSVC
  if(MSVC)
    foreach(_tgt gtest gtest_main gmock gmock_main)
      target_compile_definitions(
        ${_tgt} PRIVATE "_SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING"
      )
    endforeach()
  endif()
endif()
