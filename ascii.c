#include <ncurses.h>
#include <time.h>

#include "ascii.h"
#include "photo.h"
#include "colors.h"

#define FPS 60

Letter letters[] = {
    {'a', 38}, {'b', 38}, {'c', 19}, {'d', 27}, {'e', 40},
    {'f', 11}, {'g', 37}, {'i', 23}, {'j', 20}, {'k', 38},
    {'l', 26}, {'m', 38}, {'n', 28}, {'o', 30}, {'p', 38},
    {'q', 41}, {'r', 16}, {'s', 20}, {'t', 20}, {'u', 35},
    {'v', 21}, {'w', 27}, {'x', 22}, {'y', 28}, {'z', 19},
    {'A', 35}, {'B', 50}, {'C', 27}, {'D', 40}, {'E', 37},
    {'F', 27}, {'G', 38}, {'H', 45}, {'I', 27}, {'J', 27},
    {'K', 43}, {'L', 26}, {'M', 58}, {'N', 60}, {'O', 43},
    {'P', 34}, {'Q', 48}, {'R', 45}, {'S', 34}, {'T', 20},
    {'U', 39}, {'V', 34}, {'W', 53}, {'X', 37}, {'Y', 25},
    {'Z', 29}, {'+', 23}, {'!', 13}, {'$', 34}, {'%', 27},
    {' ', 0},  {'.', 8},  {',', 12}, {'=', 24}, {'?', 17},
    {'*', 17}, {'"', 20}, {'-', 11}, {'@', 46}, {'#', 43}
};

void init() {
    initscr();
    noecho();
    curs_set(0);
    cbreak();
    keypad(stdscr, TRUE);
    start_color();
    srand(time(NULL));
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    timeout(1000 / FPS);
    init_colors();
}

char get_fitting_letter(U8 value) {
    Letter results[16];
    U8 result_count = 0;
    U8 best = 0;
    for (U8 i = 0; i < sizeof(letters) / sizeof(Letter); i++) {
        int current = best - value;
        int bias = (rand() % 3 - 1) * 10;
        int this_one = letters[i].value - value + bias;
        if (abs(current) > abs(this_one)) {
            best = letters[i].value;
            result_count = 0;
        }
        if (best == letters[i].value) {
            results[result_count] = letters[i];
            result_count++;
        }
    }
    return results[rand() % result_count].ch;
}

void draw(const Photo *photo) {
    clear();
    for (U8 y = 0; y < photo->h; y++) {
        for (U8 x = 0; x < photo->w; x++) {
            U8 value = 255 - photo->pic[y][x].value;
            U8 color = photo->pic[y][x].color;
            attron(COLOR_PAIR(color));
            mvaddch(y, x, get_fitting_letter(value));
            attroff(COLOR_PAIR(color));
        }
    }
    refresh();
}

void close() {
    endwin();
}

U32 get_term_w() {return getmaxx(stdscr);}
U32 get_term_h() {return getmaxy(stdscr);}
