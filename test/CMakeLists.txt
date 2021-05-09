enable_testing()

# specifying an out-of-tree source a binary directory must be explicitly specified
add_subdirectory(
  ${CMAKE_CURRENT_SOURCE_DIR}/../thirdparty/googletest
  googletest
  EXCLUDE_FROM_ALL
)

add_executable(flow_test
  ${CMAKE_CURRENT_SOURCE_DIR}/flow_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)
target_link_libraries(flow_test
  PRIVATE
  flow gtest gtest_main
)

add_test(NAME flow_test COMMAND flow_test)