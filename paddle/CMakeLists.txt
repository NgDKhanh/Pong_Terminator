project(paddle)

add_library(paddle paddle.cpp)

target_link_directories(paddle PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(lib::paddle ALIAS paddle)