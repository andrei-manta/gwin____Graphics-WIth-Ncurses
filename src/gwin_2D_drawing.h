#define _XOPEN_SOURCE_EXTENDED
#include <ncursesw/ncurses.h>

signed char gwin_draw_line_made_of_one_color(signed short start_y, signed short start_x,
    signed char end_y, signed char end_x, unsigned char R, unsigned char G, unsigned char B);

signed char gwin_draw_point(signed short y, signed short x, unsigned char R, unsigned char G, unsigned char B);

signed char gwin_draw_circle_made_of_one_color(signed short center_y, signed short center_x, 
    signed short pixel_radius, unsigned char R, unsigned char G, unsigned char B);
