#include "gwin_constants.h"
#include "gwin_pixels.h"
#define _XOPEN_SOURCE_EXTENDED
#include <ncursesw/ncurses.h>


typedef struct
{
  signed short rows;
  signed short columns;
  gwin_2pixel_cell physical_pixel_grid[MAXIMUM_SUPPORTED_TERMINAL_CELL_ROWS][MAXIMUM_SUPPORTED_TERMINAL_CELL_COLUMNS];
  signed short logical_rows;
  signed short logical_columns;
}gwin_terminal_capabilities;

gwin_terminal_capabilities _gwin_terminal_capabilities;

signed char gwin_init_terminal_graphics();
