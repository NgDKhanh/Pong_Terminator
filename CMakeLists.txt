cmake_minimum_required(VERSION 3.6)
project(pong_terminator)

add_subdirectory(paddle)
add_subdirectory(game_window)
add_subdirectory(ball)

add_executable(${PROJECT_NAME} main.cpp app.cpp)

target_link_libraries( ${PROJECT_NAME}
 PRIVATE
 ncurses
 lib::paddle
 lib::game_window
 lib::ball
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR})