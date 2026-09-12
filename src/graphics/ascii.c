#include <ncurses.h>
#include <time.h>
#include <stdio.h>

#include "graphics/ascii.h"
#include "graphics/texture.h"
#include "graphics/color.h"
#include "graphics/photo.h"

void init_ascii() {
    initscr();
    noecho();
    curs_set(0);
    cbreak();
    keypad(stdscr, TRUE);
    start_color();
    srand(time(NULL));
    nodelay(stdscr, TRUE);
    timeout(1000 / FPS);
    init_colors();
}

static char get_fitting_letter(U8 value, U8 texture) {
    Texture t = textures[texture];
    Letter results[16] = {0};
    U8 result_count = 0;
    U8 best = 0;
    for (U8 i = 0; i < t.count; i++) {
        int current = best - value;
        int bias = (rand() % 3 - 1) * t.jitter;
        Letter letter = t.letters[i];
        int this_one = letter.value - value + bias;
        if (abs(current) > abs(this_one)) {
            best = letter.value;
            result_count = 0;
        }
        if (best == letter.value && letter.value > 0) {
            results[result_count] = letter;
            result_count++;
        }
    }
    if (result_count == 0) return t.letters[0].ch;
    return results[rand() % result_count].ch;
}

void draw_ascii(const Photo *photo, Camera *cam) {
    clear();
    for (U32 y = 0; y < photo->h; y++) {
        for (U32 x = 0; x < photo->w; x++) {
            U8 value = 255 - photo->pic[y][x].value;
            U8 color = photo->pic[y][x].color;
            U8 texture = photo->pic[y][x].texture;
            attron(COLOR_PAIR(color));
            mvaddch(y, x, get_fitting_letter(value, texture));
            attroff(COLOR_PAIR(color));
        }
    }
    mvprintw(0, 0, "x: %f", cam->pos.pos.x);
    mvprintw(1, 0, "y: %f", cam->pos.pos.y);
    mvprintw(2, 0, "z: %f", cam->pos.pos.z);
    mvprintw(3, 0, "dx: %f", cam->pos.dir.x);
    mvprintw(4, 0, "dy: %f", cam->pos.dir.y);
    mvprintw(5, 0, "dz: %f", cam->pos.dir.z);
    refresh();
}

void close_ascii() {
    endwin();
}

U32 ascii_w() {return getmaxx(stdscr);}
U32 ascii_h() {return getmaxy(stdscr);}
