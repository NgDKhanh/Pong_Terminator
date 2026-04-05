#include "game_window.h"

GameWindow::GameWindow(int height, int width) {
    initscr(); // Start ncurses mode
    noecho();
    cbreak();
    curs_set(0);

    game_height = height;
    game_width = width;

    game_win = std::shared_ptr<WINDOW>(newwin(game_height, game_width, 5, 10), [](WINDOW* w){ delwin(w); });
    keypad(game_win.get(), TRUE);
    box(game_win.get(), 0, 0); 
    wrefresh(game_win.get());

    windowsHasColors();
    initColor();
}

GameWindow::~GameWindow() {
    endwin(); // End ncurses mode
}

void GameWindow::getBoundary(int &max_x, int &max_y) {
    getmaxyx(game_win.get(), max_y, max_x);
}

void GameWindow::refreshWindow() {
    wrefresh(game_win.get());
}

void GameWindow::getchWindow(int &ch) {
    ch = wgetch(game_win.get());
}

void GameWindow::printGameOver() {
    printNormalText(game_width * 0.5 - 6, game_height * 0.5, "Game Over :)");
    // mvwprintw(game_win.get(), game_height * 0.5, game_width * 0.5 - 6, "Game Over :)");
    wrefresh(game_win.get());
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    clearText(game_width * 0.5 - 6, game_height * 0.5, "Game Over :)");
}

void GameWindow::printGamePoint(int points) {
    // printNormalText(0, 0, "Pong terminator: %d", points);
    mvwprintw(game_win.get(), 0, 0, "Pong terminator: %d", points);
}

void GameWindow::printWelcome() {
    std::string welcome = "Welcome to Pong Terminator";
    std::string enter = "Enter to continue";
    printNormalText(game_width * 0.5 - welcome.length(), game_height * 0.5, welcome.c_str());
    // mvwprintw(game_win.get(), game_height * 0.5, game_width * 0.5 - welcome.length(), welcome.c_str());
    printColorText(game_width * 0.5 - enter.length(), game_height * 0.5 + 2, enter.c_str());
    // mvwprintw(game_win.get(), game_height * 0.5 + 2, game_width * 0.5 - enter.length(), enter.c_str());

    int ch;
    bool stayHere = true;

    while (stayHere) {
    getchWindow(ch);

        switch (ch)
        {
            case KEY_ENTER:
            case '\n':
            // Exit welcome screen
            stayHere = false;
            break;

            default:
            continue;
            break;
        }
    }

    // mvwprintw(game_win.get(), game_height * 0.5, game_width * 0.5 - clear_welcome.length(), clear_welcome.c_str());
    clearText(game_width * 0.5 - welcome.length(), game_height * 0.5, welcome.c_str());
    // mvwprintw(game_win.get(), game_height * 0.5 + 2, game_width * 0.5 - clear_enter.length(), clear_enter.c_str());
    clearText(game_width * 0.5 - enter.length(), game_height * 0.5 + 2, enter.c_str());
}

bool GameWindow::printContinuePlaying() {
    std::string ask = "Continue playing ?";
    std::string option[2] = {"YES", "NO"};

    uint8_t chosen = 0;
    printNormalText(game_width * 0.5 - ask.length(), game_height * 0.5, ask.c_str());
    printColorText(game_width * 0.5 - option[0].length(), game_height * 0.5 + 1 , option[0].c_str());
    printNormalText(game_width * 0.5 - option[1].length(), game_height * 0.5 + 2 , option[1].c_str());

    int ch;
    bool continuePlaying = true;
    bool stayHere = true;

    setTimeout(-1);

    while (stayHere) {
        getchWindow(ch);

        switch (ch)
        {
            case KEY_DOWN:
                chosen = (chosen + 1) % 2;
                break;
            case KEY_UP:
                chosen = (chosen - 1) % 2;
                break;
            case KEY_ENTER:
            case '\n':
                stayHere = false;
            default:
                break;
        }

        clearText(game_width * 0.5 - option[0].length(), game_height * 0.5 + 1, option[0].c_str());
        clearText(game_width * 0.5 - option[1].length(), game_height * 0.5 + 2, option[1].c_str());
        if (chosen == 0) {
            printColorText(game_width * 0.5 - option[0].length(), game_height * 0.5 + 1 , option[0].c_str());
            printNormalText(game_width * 0.5 - option[1].length(), game_height * 0.5 + 2 , option[1].c_str());
        }
        if (chosen == 1) {
            printNormalText(game_width * 0.5 - option[0].length(), game_height * 0.5 + 1 , option[0].c_str());
            printColorText(game_width * 0.5 - option[1].length(), game_height * 0.5 + 2 , option[1].c_str());
        }
    }

    clearText(game_width * 0.5 - ask.length(), game_height * 0.5, ask.c_str());
    clearText(game_width * 0.5 - option[0].length(), game_height * 0.5 + 1, option[0].c_str());
    clearText(game_width * 0.5 - option[1].length(), game_height * 0.5 + 2, option[1].c_str());

    setTimeout(0);

    return (bool)(1 - chosen);
}