#ifndef GWIN_COLORS_H
#define GWIN_COLORS_H

#define _XOPEN_SOURCE_EXTENDED
#include <ncursesw/ncurses.h>

signed char gwin_init_color();
signed char gwin_RGB_to_ncurses_solid_color_with_alpha(unsigned char *where_to_store_the_result,
    unsigned char R, unsigned char G, unsigned char B);

#endif
