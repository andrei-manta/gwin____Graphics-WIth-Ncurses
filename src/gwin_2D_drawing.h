#define _XOPEN_SOURCE_EXTENDED
#include <ncursesw/ncurses.h>

signed char gwin_draw_line_made_of_one_color(signed short start_y, signed short start_x,
    signed char end_y, signed char end_x, unsigned char R, unsigned char G, unsigned char B);
