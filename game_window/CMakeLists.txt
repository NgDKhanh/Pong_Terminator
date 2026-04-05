project(game_window)

add_library(game_window game_window.cpp)

target_link_directories(game_window PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(game_window
 PRIVATE
 ncurses 
)

add_library(lib::game_window ALIAS game_window)