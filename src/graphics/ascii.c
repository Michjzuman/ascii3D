#include <ncurses.h>
#include <time.h>

#include "graphics/ascii.h"
#include "graphics/colors.h"
#include "graphics/photo.h"

Palette palettes[] = {
    (Palette){.count = 90, .letters = (Letter[90]){
        {' ', 0},   {'\'', 37}, {'.', 39},  {',', 56},  {'-', 59},  {':', 69},  {'!', 74},  {'"', 75},
        {';', 88},  {'/', 92},  {'r', 96},  {'(', 98},  {')', 98},  {'+', 99},  {'l', 103}, {'>', 103},
        {'<', 103}, {'?', 108}, {'i', 109}, {'[', 117}, {']', 117}, {'=', 117}, {'c', 119}, {'v', 121},
        {'}', 124}, {'{', 124}, {'7', 125}, {'*', 125}, {'L', 127}, {'x', 128}, {'z', 130}, {'Y', 130},
        {'s', 134}, {'j', 134}, {'f', 137}, {'t', 137}, {'J', 138}, {'T', 139}, {'1', 140}, {'n', 144},
        {'u', 144}, {'C', 144}, {'e', 144}, {'y', 152}, {'I', 156}, {'2', 158}, {'V', 158}, {'o', 158},
        {'F', 162}, {'k', 164}, {'h', 164}, {'%', 165}, {'w', 165}, {'X', 168}, {'3', 168}, {'Z', 170},
        {'4', 172}, {'S', 173}, {'a', 177}, {'5', 177}, {'A', 184}, {'P', 185}, {'U', 185}, {'m', 190},
        {'b', 190}, {'d', 190}, {'G', 190}, {'p', 194}, {'K', 194}, {'q', 194}, {'#', 194}, {'$', 195},
        {'&', 197}, {'6', 198}, {'9', 198}, {'O', 200}, {'E', 203}, {'H', 204}, {'D', 212}, {'Q', 215},
        {'R', 218}, {'g', 218}, {'8', 219}, {'W', 227}, {'@', 232}, {'M', 232}, {'0', 241}, {'B', 249},
        {'N', 253}
    }},
    (Palette){.count = 2, .letters = (Letter[2]){{'6', 67}, {'7', 67}}},
    (Palette){.count = 5, .letters = (Letter[5]){{'|', 90}, {'/', 130}, {'\\', 170}, {'(', 210}, {')', 250}}}
};

void init_ascii() {
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

static char get_fitting_letter(U8 v, U8 palette) {
    Letter results[16] = {0};
    U8 result_count = 0;
    U8 best = 0;
    for (U8 i = 0; i < palettes[palette].count; i++) {
        int current = best - v;
        int bias = (rand() % 3 - 1) * 0;
        Letter letter = palettes[palette].letters[i];
        int this_one = letter.value - v + bias;
        if (abs(current) > abs(this_one)) {
            best = letter.value;
            result_count = 0;
        }
        if (best == letter.value && letter.value > 0) {
            results[result_count] = letter;
            result_count++;
        }
    }
    if (result_count == 0) return ' ';
    return results[rand() % result_count].ch;
}

#include <stdio.h>

void draw_ascii(const Photo *photo, Camera *cam) {
    clear();
    for (U32 y = 0; y < photo->h; y++) {
        for (U32 x = 0; x < photo->w; x++) {
            U8 value = 255 - photo->pic[y][x].value;
            U8 color = photo->pic[y][x].color;
            U8 palette = photo->pic[y][x].palette;
            attron(COLOR_PAIR(color));
            mvaddch(y, x, get_fitting_letter(value, 0));
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

void close_ascii() {
    endwin();
}

U32 ascii_w() {return getmaxx(stdscr);}
U32 ascii_h() {return getmaxy(stdscr);}
