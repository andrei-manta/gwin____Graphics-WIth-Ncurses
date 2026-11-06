
#include <math.h>
#include <locale.h>
#include <stdio.h>
#include "gwin_logging.h"
#include "gwin_constants.h"
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


typedef struct
{
  signed short rows;
  signed short columns;
  gwin_2pixel_cell physical_pixel_grid[MAXIMUM_SUPPORTED_TERMINAL_CELL_ROWS][MAXIMUM_SUPPORTED_TERMINAL_CELL_COLUMNS];
  signed short logical_rows;
  signed short logical_columns;
}gwin_terminal_capabilities;

gwin_terminal_capabilities _gwin_terminal_capabilities;

signed char gwin_init_color()
{
  start_color();

  for(int fg = 1; fg < 256; fg++)
  {
    for(int bg = 1; bg < 256; bg++)
    {
      init_extended_pair(fg * 256 + bg, fg, bg);
    }
  }

  return (signed char)0;
}

unsigned char gwin_RGB_to_ncurses_solid_color_with_alpha(unsigned char R, unsigned char G, unsigned char B)
{
  unsigned char R_to_color_cube_r = (unsigned char)(roundf((float)R / (float)255.0 * 5.0));
  unsigned char G_to_color_cube_g = (unsigned char)(roundf((float)G / (float)255.0 * 5.0));
  unsigned char B_to_color_cube_b = (unsigned char)(roundf((float)B / (float)255.0 * 5.0));

  unsigned char resulting_color = R_to_color_cube_r * 6 * 6 + G_to_color_cube_g * 6 + B_to_color_cube_b + 16;

  return resulting_color;
}


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

signed char set_logical_pixel_yx_to_rgb_and_set_physical_pixel_and_refresh(
    signed short y, signed short x, unsigned char R, unsigned char G, unsigned char B)
{
  if(y < (signed short)0) return (signed char)-1;
  if(y > (signed short)_gwin_terminal_capabilities.logical_rows) return (signed char)-2;
  if(x < (signed short)0) return (signed char)-3;
  if(x > (signed short)_gwin_terminal_capabilities.logical_columns) return (signed char)-4;

  unsigned char color_number = gwin_RGB_to_ncurses_solid_color_with_alpha(R, G, B);

  if(y % 2 == 0)
  {
    _gwin_terminal_capabilities.physical_pixel_grid[y / (signed short)2][x].upper_pixel.rgb_color = color_number;
    int cell_color_pair = (int)color_number * (int)256 + 
      (int)(_gwin_terminal_capabilities.physical_pixel_grid[y / (signed short)2][x].lower_pixel.rgb_color);
    setcchar(&(_gwin_terminal_capabilities.physical_pixel_grid[y / (signed short)2][x].physical_cell_contents), L"\u2580", A_NORMAL, 
      0, &cell_color_pair);
    mvadd_wch((int)(y / (signed short)2), (int)x, 
        &(_gwin_terminal_capabilities.physical_pixel_grid[y / (signed short)2][x].physical_cell_contents));
  }
  if(y % 2 == 1)
  {
    _gwin_terminal_capabilities.physical_pixel_grid[y / (signed short)2][x].lower_pixel.rgb_color = color_number;
    int cell_color_pair = (int)(_gwin_terminal_capabilities.physical_pixel_grid[y / (signed short)2][x].upper_pixel.rgb_color) * 
      (int)256 + (int)color_number;
    setcchar(&(_gwin_terminal_capabilities.physical_pixel_grid[y / (signed short)2][x].physical_cell_contents), L"\u2580", A_NORMAL,
        0, &cell_color_pair);
    mvadd_wch((int)(y / (signed short)2), (int)x,
        &(_gwin_terminal_capabilities.physical_pixel_grid[y / (signed short)2][x].physical_cell_contents));
  }

  refresh();
}

signed char gwin_draw_line_made_of_one_color(signed short start_y, signed short start_x,
    signed char end_y, signed char end_x, unsigned char R, unsigned char G, unsigned char B)
{

  if (start_y < 0)
  {
    return (signed char)-1;
  }

  if (start_x < 0)
  {
    return (signed char)-2;
  }

  if (end_y < 0)
  {
    return (signed char)-3;
  }

  if (end_x < 0)
  {
    return (signed char)-4;
  }


  if (start_y == end_y)
  {
    
    if (start_x == end_x)
    {
      set_logical_pixel_yx_to_rgb_and_set_physical_pixel_and_refresh(start_y, start_x, R, G, B);
      return (signed char)0;
    }

    for(int i = 0; i <= (end_x > start_x ? end_x - start_x : start_x - end_x); i++)
    {
      set_logical_pixel_yx_to_rgb_and_set_physical_pixel_and_refresh(start_y, start_x + i * (end_x > start_x ? (int)1 : (int)-1), R, G, B);
    }

    return (signed char)0;
  
  }


  if (start_x == end_x)
  {

    for(int i = 0; i <= (end_y > start_y ? end_y - start_y : start_y - end_y); i++)
    {
      set_logical_pixel_yx_to_rgb_and_set_physical_pixel_and_refresh(start_y + i * (end_y > start_y ? (int)1 : (int)-1), start_x, R, G, B);
    }

    return (signed char)0;

  }

  float length_of_the_requested_line = sqrtf(powf((float)(end_y - start_y), 2.0) + powf((float)(end_x - start_x), 2.0));
  float x_slope_component = (float)(end_x - start_x) / length_of_the_requested_line;
  float y_slope_component = (float)(end_y - start_y) / length_of_the_requested_line;

  for(float i = 0.0; i < length_of_the_requested_line; i += 1.0)
  {
    set_logical_pixel_yx_to_rgb_and_set_physical_pixel_and_refresh(start_y + (int)roundf(y_slope_component * i), 
        start_x + (int)roundf(x_slope_component * i), R, G, B);
  }

  return (signed char)0;

}


