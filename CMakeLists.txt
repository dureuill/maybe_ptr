cmake_minimum_required(VERSION 3.7.9)

project(maybe_ptr CXX)

include(ExternalProject)

add_library(maybe_ptr INTERFACE)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)

target_include_directories(maybe_ptr INTERFACE
  $<BUILD_INTERFACE:
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  >
)

install(
  DIRECTORY include/
  DESTINATION include
)

# No tests at the moment
#option(maybe_ptr_TEST "Generate tests." OFF)
#if (maybe_ptr_TEST)
#  enable_testing()
#  add_subdirectory(tests)
#endif()

option(maybe_ptr_EXAMPLES "Generate examples." OFF)
if (maybe_ptr_EXAMPLES)
  add_subdirectory(examples)
endif()
