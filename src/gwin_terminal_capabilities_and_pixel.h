#include <ncurses.h>
#include <locale.h>
#include "gwin_colors.h"
#include "gwin_constants.h"
#include "gwin_logging.h"
#include <stdio.h>


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
    }
  }

  return (signed char)0;
}

signed char set_logical_pixel_yx_to_rgb_and_refresh(signed short y, signed short x, unsigned char R, unsigned char G, unsigned char B)
{
  if(y < (signed short)0) return (signed char)-1;
  if(y > (signed short)_gwin_terminal_capabilities.logical_rows) return (signed char)-2;
  if(x < (signed short)0) return (signed char)-3;
  if(x > (signed short)_gwin_terminal_capabilities.logical_columns) return (signed char)-4;

  unsigned char color_number = gwin_RGB_to_ncurses_solid_color_with_alpha(R, G, B);

  y % 2 == 0 ? 
    (_gwin_terminal_capabilities.physical_pixel_grid[y / (signed short)2][x].upper_pixel.rgb_color = color_number) : 
    (_gwin_terminal_capabilities.physical_pixel_grid[y / (signed short)2][x].lower_pixel.rgb_color = color_number);

  mvaddch(y / 2, x, 'A' | COLOR_PAIR(color_number));

  char buf[32];
  snprintf(buf, 32, "color_number is:%d", color_number);
  gwin_log(buf);

  refresh();
}







