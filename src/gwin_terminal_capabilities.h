#ifndef GWIN_TERMINAL_CAPABILITIES_H
#define GWIN_TERMINAL_CAPABILITIES_H

#include "gwin_constants.h"
#include "gwin_pixels.h"
#define _XOPEN_SOURCE_EXTENDED
#include <ncursesw/ncurses.h>

typedef struct
{
  signed short rows;
  signed short columns;
  gwin_2pixel_cell physical_pixel_grid[(signed short)MAXIMUM_SUPPORTED_TERMINAL_CELL_ROWS]
  [(signed short)MAXIMUM_SUPPORTED_TERMINAL_CELL_COLUMNS];
  signed short logical_rows;
  signed short logical_columns;
}gwin_terminal_capabilities;

extern gwin_terminal_capabilities _gwin_terminal_capabilities;

signed char gwin_init_terminal_graphics();

signed char gwin_get_terminal_size(signed short *where_to_store_lines,
    signed short *where_to_store_columns);

#endif
