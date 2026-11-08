#ifndef GWIN_COLORS_H
#define GWIN_COLORS_H

#define _XOPEN_SOURCE_EXTENDED
#include <ncursesw/ncurses.h>

signed char gwin_init_color();
unsigned char gwin_RGB_to_ncurses_solid_color_with_alpha(unsigned char R, unsigned char G, unsigned char B);

#endif
