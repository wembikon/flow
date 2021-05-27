cmake_minimum_required(VERSION 3.16)

set(PROJECT_VERSION 1.0.0)
project(flow VERSION ${PROJECT_VERSION} LANGUAGES CXX)
message(STATUS "Build flow: ${PROJECT_VERSION}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# dependencies (declarations only, population is done on specific needs later)
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG master
)

# main source
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)

# unit tests
get_directory_property(IS_SUBPROJECT PARENT_DIRECTORY)
if(NOT IS_SUBPROJECT)
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)
endif()