message(STATUS "Building flow UNIT TESTS")
enable_testing()

FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
  FetchContent_MakeAvailable(googletest)
endif()

add_executable(flow_test
  ${CMAKE_CURRENT_SOURCE_DIR}/flow_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)
target_link_libraries(flow_test
  PRIVATE
  flow gtest gtest_main
)

add_test(NAME flow_test COMMAND flow_test)