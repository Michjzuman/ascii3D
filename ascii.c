#include <ncurses.h>
#include <time.h>

#include "ascii.h"
#include "photo.h"
#include "colors.h"
#include "3D.h"

#define FPS 60

Letter letters[] = {
    {'a', 162}, {'b', 162}, {'c', 81}, {'d', 115}, {'e', 170},
    {'f', 47}, {'g', 157}, {'i', 98}, {'j', 85}, {'k', 162},
    {'l', 111}, {'m', 162}, {'n', 119}, {'o', 128}, {'p', 162},
    {'q', 174}, {'r', 68}, {'s', 85}, {'t', 85}, {'u', 149},
    {'v', 89}, {'w', 115}, {'x', 94}, {'y', 119}, {'z', 81},
    {'A', 149}, {'B', 213}, {'C', 115}, {'D', 170}, {'E', 157},
    {'F', 115}, {'G', 162}, {'H', 191}, {'I', 115}, {'J', 115},
    {'K', 183}, {'L', 111}, {'M', 247}, {'N', 255}, {'O', 183},
    {'P', 145}, {'Q', 204}, {'R', 191}, {'S', 145}, {'T', 85},
    {'U', 166}, {'V', 145}, {'W', 225}, {'X', 157}, {'Y', 106},
    {'Z', 123}, {'+', 98}, {'!', 55}, {'$', 145}, {'%', 115},
    {' ', 0}, {'.', 34}, {',', 51}, {'=', 102}, {'?', 72},
    {'*', 72}, {'"', 85}, {'-', 47}, {'@', 196}, {'#', 183}
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

char get_fitting_letter(U8 v) {
    Letter results[16];
    U8 result_count = 0;
    U8 best = 0;
    for (U8 i = 0; i < sizeof(letters) / sizeof(Letter); i++) {
        int current = best - v;
        int bias = (rand() % 3 - 1) * 5;
        int this_one = letters[i].value - v + bias;
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

void draw(const Photo *photo, Camera *cam) {
    clear();
    for (U32 y = 0; y < photo->h; y++) {
        for (U32 x = 0; x < photo->w; x++) {
            U8 value = 255 - photo->pic[y][x].value;
            U8 color = photo->pic[y][x].color;
            attron(COLOR_PAIR(color));
            mvaddch(y, x, get_fitting_letter(value));
            attroff(COLOR_PAIR(color));
        }
    }
    mvprintw(0, 0, "x: %f", cam->pos.x);
    mvprintw(1, 0, "y: %f", cam->pos.y);
    mvprintw(2, 0, "z: %f", cam->pos.z);
    mvprintw(3, 0, "dx: %f", cam->pos.dx);
    mvprintw(4, 0, "dy: %f", cam->pos.dy);
    mvprintw(5, 0, "dz: %f", cam->pos.dz);
    refresh();
}

void close() {
    endwin();
}

U32 get_term_w() {return getmaxx(stdscr);}
U32 get_term_h() {return getmaxy(stdscr);}
