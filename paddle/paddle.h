#include <iostream>
#include <ncurses.h>
#include <stdint.h>
#include <memory>
#include <string>

class Paddle {

    public:
        Paddle(WINDOW *win, int init_y, int init_x, int max_y, int min_y, std::string paddle_shape, int height);

        void render(int y, int x);

        void clear(int y, int x);

        void moveUp(int delta_y);

        void moveDown(int delta_y);

        void moveTo(int des_y);

        bool handleMoving(int &ch) {
            switch (ch) {
                case KEY_UP:
                    moveUp(1);
                    return true;
                case KEY_DOWN:
                    moveDown(1);
                    return true;
                case 'q':
                    return false;
                break;
                    default:
                    break;
            }
            return true;
    }

    int getPaddleY() const { return y; }
    bool collisionWithBall(int ball_x, int ball_y) {
        return (ball_x == x + paddle_width && ball_y >= y && ball_y <= y + paddle_height);
    }

    void setPosition(int x, int y) {
        this->x = x;
        this->y = y;
    }

private:
    int x, y;
    int upper_bound_y;
    int lower_bound_y;
    std::string shape;
    std::string clear_shape;
    uint8_t paddle_height;
    uint8_t paddle_width;
    WINDOW* game_win;

    void print_vertical(int start_y, int x, const char *s) {
        for (uint8_t i = 0; i < paddle_height; i++) {
            mvwprintw(game_win, start_y, x, s);
            start_y++;
        }
    }

};