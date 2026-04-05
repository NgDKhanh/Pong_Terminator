#include "ball.h"

Ball::Ball(WINDOW *win, int init_y, int init_x, int max_y, int min_y, int max_x, int min_x, std::string ball_shape) {
    x = init_x;
    y = init_y;
    delta_x = 1;
    delta_y = 1;
    game_win = win;
    shape = ball_shape;
    clear_shape = " ";
    upper_bound_y = max_y;
    lower_bound_y = min_y;
    upper_bound_x = max_x;
    lower_bound_x = min_x;
}

void Ball::render() {
    print_shape(y, x, shape.c_str());
}

void Ball::clear() {
    print_shape(y, x, clear_shape.c_str());
}

void Ball::move() {
    clear();
    if (y == upper_bound_y - 1 || y == lower_bound_y) {
    delta_y = -delta_y;
    }
    if (x == upper_bound_x -1 || x == lower_bound_x) {
    delta_x = -delta_x;
    }
    y += delta_y;
    x += delta_x;
    render();
}

void Ball::moveTo(int des_x, int des_y) {
    clear();
    if ( (des_x <= upper_bound_x - 1 && des_x >= lower_bound_x) && (y <= upper_bound_y - 1 && y >= lower_bound_y) ) {
    setPosition(des_x, des_y);
    }
    render();
}

void Ball::collideWithPaddle() {
    delta_x = -delta_x;
}