cmake_minimum_required(VERSION 3.16)

set(PROJECT_VERSION 1.0.0)
project(flow VERSION ${PROJECT_VERSION} LANGUAGES CXX)
message(STATUS "Build flow: ${PROJECT_VERSION}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# the source code
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)

# tests
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)