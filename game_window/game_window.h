#include <iostream>
#include <ncurses.h>
#include <thread>
#include <chrono>
#include <stdint.h>
#include <memory>

class GameWindow {
public:
    GameWindow(int height, int width);

    ~GameWindow();

    void getBoundary(int &max_x, int &max_y);

    void refreshWindow();

    void getchWindow(int &ch);

    WINDOW* getGameWin() {
        return game_win.get();
    }

    void setTimeout(uint16_t miliseconds) {
        wtimeout(game_win.get(), miliseconds);
    }

    void printGameOver();
    void printGamePoint(int points);
    bool printContinuePlaying();

    void printWelcome();

    bool initColor() {
        if (hasColorsFlag) {
            start_color();
            init_pair(1, COLOR_BLACK, COLOR_WHITE);
            return true;
        }
        else {
            return false;
        }
    }

    private:

    void windowsHasColors()
    {
        if (has_colors() == FALSE) {
            hasColorsFlag = false;
        }
        else {
            hasColorsFlag = true;
        }
    }

    void printColorText(int x, int y, const std::string &s) {
        wattron(game_win.get(), COLOR_PAIR(1));
        mvwprintw(game_win.get(), y, x, s.c_str());
        wattroff(game_win.get(), COLOR_PAIR(1));
    }

    void printNormalText(int x, int y, const std::string &s) {
        mvwprintw(game_win.get(), y, x, s.c_str());
    }

    void clearText(int x, int y, std::string s) {
        std::string clearString = "";
        for (int i = 0; i < s.length(); i++)
        {
            clearString.append(" ");
        }
        mvwprintw(game_win.get(), y, x, clearString.c_str());
    }

    int game_height, game_width;
    std::shared_ptr<WINDOW> game_win;
    bool hasColorsFlag = false;
};