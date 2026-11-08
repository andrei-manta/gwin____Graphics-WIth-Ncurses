#include <math.h>
#include "gwin_constants.h"
#include "gwin_colors.h"
#include "gwin_pixels.h"
#include "gwin_2D_drawing.h"
#define _XOPEN_SOURCE_EXTENDED
#include <ncursesw/ncurses.h>

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

