#ifndef GWIN_PIXELS_H
#define GWIN_PIXELS_H

#include "gwin_virtual_screens.h"
#define _XOPEN_SOURCE_EXTENDED
#include <ncursesw/ncurses.h>

signed char gwin_write_virtual_screen_to_physical_screen(gwin_virtual_screen *which_virtual_screen);

signed char gwin_compute_as_float_distance_between_two_logical_pixels(signed short first_pixel_y, signed short first_pixel_x,
    signed short second_pixel_y, signed short second_pixel_x, float *where_to_store_the_result);

#endif
