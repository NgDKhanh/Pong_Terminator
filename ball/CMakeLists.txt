project(ball)

add_library(ball ball.cpp)

target_link_directories(ball PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(lib::ball ALIAS ball)