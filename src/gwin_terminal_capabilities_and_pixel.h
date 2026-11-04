#include <ncurses.h>
#include <locale.h>
#include "gwin_colors.h"
#include "gwin_constants.h"


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
}gwin_2pixel_cell;


typedef struct
{
  int rows;
  int columns;
  gwin_2pixel_cell physical_pixel_grid[MAXIMUM_SUPPORTED_TERMINAL_CELL_ROWS][MAXIMUM_SUPPORTED_TERMINAL_CELL_COLUMNS];
}gwin_terminal_capabilities;

gwin_terminal_capabilities _gwin_terminal_capabilities;



signed char gwin_init_terminal_graphics()
{
  setlocale(LC_ALL, "");
  initscr();
  cbreak();
  noecho();
  gwin_init_color();

  _gwin_terminal_capabilities.rows = LINES;
  _gwin_terminal_capabilities.columns = COLS;

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
    }
  }

  return (signed char)0;
}

