#include <math.h>
#include "gwin_colors.h"
#include "gwin_pixels.h"
#include "gwin_terminal_capabilities.h"
#define _XOPEN_SOURCE_EXTENDED
#include <ncursesw/ncurses.h>

signed char set_logical_pixel_yx_to_rgb_and_set_physical_pixel_and_refresh(
    signed short y, signed short x, unsigned char R, unsigned char G, unsigned char B)
{
  if(y < (signed short)0) return (signed char)-1;
  if(y > (signed short)_gwin_terminal_capabilities.logical_rows) return (signed char)-2;
  if(x < (signed short)0) return (signed char)-3;
  if(x > (signed short)_gwin_terminal_capabilities.logical_columns) return (signed char)-4;

  unsigned char color_number;
  gwin_RGB_to_ncurses_solid_color_with_alpha(&color_number, R, G, B);

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

signed char compute_as_float_distance_between_two_logical_pixels(signed short first_pixel_y, signed short first_pixel_x,
    signed short second_pixel_y, signed short second_pixel_x, float *where_to_store_the_result)
{
  if(first_pixel_y < (signed short)0)
  {
    return (signed char)-1;
  }
  if(first_pixel_x < (signed short)0)
  {
    return (signed char)-2;
  }
  if(second_pixel_y < (signed short)0)
  {
    return (signed char)-3;
  }
  if(second_pixel_x < (signed short)0)
  {
    return (signed char)-4;
  }

  *where_to_store_the_result = sqrtf(powf(((float)first_pixel_y) - ((float)second_pixel_y), (float)2.0)
                                     + powf(((float)first_pixel_x) - ((float)second_pixel_x), (float)2.0));

  return (signed char)0;
}

