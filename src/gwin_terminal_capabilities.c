#include <locale.h>
#include "gwin_constants.h"
#include "gwin_terminal_capabilities.h"
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

signed char gwin_init_terminal_graphics()
{
  setlocale(LC_ALL, "");
  initscr();
  cbreak();
  noecho();
  curs_set(0);
  gwin_init_color();
  gwin_init_logging();

  _gwin_terminal_capabilities.rows = (signed short)LINES;
  _gwin_terminal_capabilities.columns = (signed short)COLS;
  _gwin_terminal_capabilities.logical_rows = _gwin_terminal_capabilities.rows * (signed short)2;
  _gwin_terminal_capabilities.logical_columns = _gwin_terminal_capabilities.columns;

  for(int rows = 0; rows < _gwin_terminal_capabilities.rows; rows++)
  {
    for(int columns = 0; columns < _gwin_terminal_capabilities.columns; columns++)
    {
      _gwin_terminal_capabilities.physical_pixel_grid[rows][columns].upper_pixel.y = rows * 2;
      _gwin_terminal_capabilities.physical_pixel_grid[rows][columns].upper_pixel.x = columns;
      _gwin_terminal_capabilities.physical_pixel_grid[rows][columns].upper_pixel.rgb_color = START_OF_XTERM256_COLOR_CUBE_INCLUSIVE;

      _gwin_terminal_capabilities.physical_pixel_grid[rows][columns].lower_pixel.y = rows * 2 + 1;
      _gwin_terminal_capabilities.physical_pixel_grid[rows][columns].lower_pixel.x = columns;
      _gwin_terminal_capabilities.physical_pixel_grid[rows][columns].lower_pixel.rgb_color = START_OF_XTERM256_COLOR_CUBE_INCLUSIVE;
    
      setcchar(&_gwin_terminal_capabilities.physical_pixel_grid[rows][columns].physical_cell_contents, L"", A_NORMAL, 0, NULL);
    }
  }

  return (signed char)0;
}

