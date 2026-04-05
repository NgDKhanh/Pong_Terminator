#include <iostream>
#include <ncurses.h>
#include <stdint.h>
#include <memory>
#include <string>

class Ball {

public:
    Ball(WINDOW *win, int init_y, int init_x, int max_y, int min_y, int max_x, int min_x, std::string ball_shape);

    void render();

    void clear();

    void move();
    void moveTo(int des_x, int des_y);

    void collideWithPaddle();
    bool collideWithLeftBorder() { return x == lower_bound_x; }

    int getBallX() const { return x; }
    int getBallY() const { return y; }

    void setPosition(int x, int y) {
        this->x = x;
        this->y = y;
    }

    private:
    int x, y;
    int delta_x, delta_y;
    int upper_bound_y;
    int upper_bound_x;
    int lower_bound_y;
    int lower_bound_x;
    std::string shape;
    std::string clear_shape;
    WINDOW* game_win;

    void print_shape(int y, int x, const char *s) {
        mvwprintw(game_win, y, x, s);
    }

};