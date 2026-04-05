#include "paddle.h"

Paddle::Paddle(WINDOW *win, int init_y, int init_x, int max_y, int min_y, std::string paddle_shape, int height) {
    x = init_x;
    y = init_y;
    game_win = win;
    shape = paddle_shape;
    paddle_width = shape.length();
    clear_shape = "";
    for (uint8_t i = 0; i < shape.length(); i++) {
        clear_shape.append(" ");
    }
    paddle_height = height;
    upper_bound_y = max_y;
    lower_bound_y = min_y;
}

void Paddle::render(int y, int x) {
    print_vertical(y, x, shape.c_str());
}

void Paddle::clear(int y, int x) {
    print_vertical(y, x, clear_shape.c_str());
}

void Paddle::moveUp(int delta_y) {
    if (y == lower_bound_y) {
        // Do nothing
    }
    else if (y - delta_y <= lower_bound_y) {
        clear(y, x);
        y = lower_bound_y;
        render(y, x);
    }
    else {
        clear(y, x);
        y -= delta_y;
        render(y, x);
    }
}

void Paddle::moveDown(int delta_y) {
    if (y == upper_bound_y) {
        // Do nothing
    }
    if (y + delta_y >= upper_bound_y - paddle_height) {
        clear(y, x);
        y = upper_bound_y - paddle_height;
        render(y, x);
    }
    else {
        clear(y, x);
        y += delta_y;
        render(y, x);
    }
}

void Paddle::moveTo(int des_y) {
    if (des_y <= upper_bound_y - paddle_height && des_y >= lower_bound_y) {
        clear(y, x);
        setPosition(x, des_y);
        render(des_y, x);
    }
    else {
        // Do nothing
    }
}