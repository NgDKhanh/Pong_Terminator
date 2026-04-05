#include <iostream>
#include <ncurses.h>
#include <thread>
#include <chrono>
#include <stdint.h>

#include "app.h"
#include "paddle/paddle.h"
#include "game_window/game_window.h"
#include "ball/ball.h"

#define PADDLE_HEIGHT 5

void app() {
    GameWindow gameWin(30, 80);

    int ch;
    int max_x, max_y;

    gameWin.getBoundary(max_x, max_y);

    gameWin.printWelcome();
    gameWin.setTimeout(0);

    bool gameContinue = true;
    bool newGame = false;

    int gamePoint = 0;

    int x, y;
    y = max_y * 0.5;
    x = 2;
    Paddle paddle(gameWin.getGameWin(), y, x, max_y - 1, 1, std::string("[]"), PADDLE_HEIGHT);
    paddle.render(y, x);

    Ball ball(gameWin.getGameWin(), max_y * 0.5, max_x * 0.5, max_y - 1, 1, max_x - 1, 1, std::string("o"));
    ball.render();

    gameWin.printGamePoint(gamePoint);

    while (gameContinue || newGame) {
        if (newGame) {
            ball.moveTo(max_x * 0.5, max_y * 0.5);
            ball.resetDirection();
            paddle.moveTo(y);
            gamePoint = 0;
            gameWin.printGamePoint(gamePoint);
            newGame = false;
            gameWin.refreshWindow();
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        gameWin.refreshWindow();
        gameWin.getchWindow(ch);
        gameContinue = paddle.handleMoving(ch);

        if (paddle.collisionWithBall(ball.getBallX(), ball.getBallY())) {
            ball.collideWithPaddle();
            gamePoint++;
            gameWin.printGamePoint(gamePoint);
        }

        ball.move();

        if (ball.collideWithLeftBorder()) {
            gameWin.printGameOver();
            gameContinue = newGame = gameWin.printContinuePlaying();
        }
    }

}