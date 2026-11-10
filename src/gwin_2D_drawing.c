#include <math.h>
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

signed char gwin_draw_point(signed short y, signed short x, unsigned char R, unsigned char G, unsigned char B)
{
  if(y < (signed short)0)
  {
    return (signed char)-1;
  }
  if(x < (signed short)0)
  {
    return (signed short)-2;
  }

  set_logical_pixel_yx_to_rgb_and_set_physical_pixel_and_refresh(y, x, R, G, B);
}

signed char gwin_draw_circle_made_of_one_color(signed short center_y, signed short center_x, 
    signed short pixel_radius, unsigned char R, unsigned char G, unsigned char B)
{
  if(center_y < (signed short)0)
  {
    return (signed char)-1;
  }
  if(center_x < (signed short)0)
  {
    return (signed char)-2;
  }
  if(pixel_radius < (signed short)0)
  {
    return (signed char)-3;
  }

  // TODO what happens on overflow in these kinds of operations? Consider that throughout the drawing,
  // perhaps add a virtual drawing space that gets sync'd to the real one
  for(int rows = (int)(center_y - pixel_radius); rows <= (int)(center_y + pixel_radius); rows++)
  {
    for(int columns = (int)(center_x - pixel_radius); columns <= (int)(center_x + pixel_radius); columns++)
    {
      float distance_to_circle_center_for_this_pixel = 0.0;
      compute_as_float_distance_between_two_logical_pixels(center_y, center_x, rows, columns, &distance_to_circle_center_for_this_pixel);
      if(distance_to_circle_center_for_this_pixel <= (float)pixel_radius)
      {
        set_logical_pixel_yx_to_rgb_and_set_physical_pixel_and_refresh(rows, columns, R, G, B);
      }
    }
  }

  return (signed char)0;  
}
