add_library(flow
  INTERFACE
  ${CMAKE_CURRENT_SOURCE_DIR}/pub/yano/flow/flow.h
)
target_include_directories(flow
  INTERFACE
  ${CMAKE_CURRENT_SOURCE_DIR}/pub
)