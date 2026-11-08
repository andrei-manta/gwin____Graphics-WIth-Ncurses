#ifndef GWIN_PIXELS_H
#define GWIN_PIXELS_H

#define _XOPEN_SOURCE_EXTENDED
#include <ncursesw/ncurses.h>

typedef struct
{
  int x;
  int y;
  unsigned char rgb_color;
}gwin_pixel;

typedef struct
{
  gwin_pixel upper_pixel;
  gwin_pixel lower_pixel;
  cchar_t physical_cell_contents;
}gwin_2pixel_cell;

signed char set_logical_pixel_yx_to_rgb_and_set_physical_pixel_and_refresh(
    signed short y, signed short x, unsigned char R, unsigned char G, unsigned char B);

#endif
