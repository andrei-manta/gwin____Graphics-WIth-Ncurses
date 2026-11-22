#include <math.h>
#include "gwin_colors.h"
#include "gwin_pixels.h"
#include "gwin_terminal_capabilities.h"
#define _XOPEN_SOURCE_EXTENDED
#include <ncursesw/ncurses.h>

signed char gwin_write_virtual_screen_to_physical_screen(gwin_virtual_screen *which_virtual_screen)
{
  if(which_virtual_screen == (gwin_virtual_screen *)NULL)
  {
    gwin_log_function_error("this function itself", "received NULL pointer as parameter", -1,
                            "gwin_write_virtual_screen_to_physical_screen()");
    return (signed char)-1;
  }

  signed short virtual_rows = _gwin_virtual_screens_table.virtual_screen_rows;
  signed short virtual_columns = _gwin_virtual_screens_table.virtual_screen_columns;

  for(signed short cell_y = (signed short)0; (int)cell_y * (int)2 < (int)virtual_rows; cell_y++)
  {
    signed short upper_y = (signed short)((int)cell_y * (int)2);
    signed short lower_y = (signed short)((int)upper_y + (int)1);

    for(signed short x = (signed short)0; x < virtual_columns; x++)
    {
      gwin_virtual_pixel *upper_pixel = &which_virtual_screen->pixels[(size_t)upper_y * (size_t)virtual_columns + (size_t)x];

      unsigned char upper_color_number;
      unsigned char lower_color_number;

      signed char upper_conversion_return = gwin_RGB_to_ncurses_solid_color_with_alpha(&upper_color_number,
                                                                                       upper_pixel->R, upper_pixel->G,
                                                                                       upper_pixel->B);

      if(upper_conversion_return != (signed char)0)
      {
        gwin_log_function_error("gwin_RGB_to_ncurses_solid_color_with_alpha()", "returned with error",
                                upper_conversion_return, "gwin_write_virtual_screen_to_physical_screen()");
        return (signed char)-2;
      }

      signed char lower_conversion_return;

      if(lower_y < virtual_rows)
      {
        gwin_virtual_pixel *lower_pixel = &which_virtual_screen->pixels[(size_t)lower_y * (size_t)virtual_columns + (size_t)x];

        lower_conversion_return = gwin_RGB_to_ncurses_solid_color_with_alpha(&lower_color_number,
                                                                             lower_pixel->R, lower_pixel->G,
                                                                             lower_pixel->B);
      }
      else
      {
        // odd number of pixel rows: the missing lower pixel is black
        lower_conversion_return = gwin_RGB_to_ncurses_solid_color_with_alpha(&lower_color_number,
                                                                             (unsigned char)0, (unsigned char)0,
                                                                             (unsigned char)0);
      }

      if(lower_conversion_return != (signed char)0)
      {
        gwin_log_function_error("gwin_RGB_to_ncurses_solid_color_with_alpha()", "returned with error",
                                lower_conversion_return, "gwin_write_virtual_screen_to_physical_screen()");
        return (signed char)-3;
      }

      int cell_color_pair = (int)upper_color_number * (int)256 + (int)lower_color_number;

      cchar_t physical_cell_contents;

      if(setcchar(&physical_cell_contents, L"\u2580", A_NORMAL, 0, &cell_color_pair) == ERR)
      {
        gwin_log_function_error("setcchar()", "returned ERR", -1, "gwin_write_virtual_screen_to_physical_screen()");
        return (signed char)-4;
      }

      if(mvadd_wch((int)cell_y, (int)x, &physical_cell_contents) == ERR)
      {
        gwin_log_function_error("mvadd_wch()", "returned ERR", -1, "gwin_write_virtual_screen_to_physical_screen()");
        return (signed char)-5;
      }
    }
  }

  if(refresh() == ERR)
  {
    gwin_log_function_error("refresh()", "returned ERR", -1, "gwin_write_virtual_screen_to_physical_screen()");
    return (signed char)-6;
  }

  return (signed char)0;
}

signed char gwin_compute_as_float_distance_between_two_logical_pixels(signed short first_pixel_y, signed short first_pixel_x,
    signed short second_pixel_y, signed short second_pixel_x, float *where_to_store_the_result)
{
  if(first_pixel_y < (signed short)0)
  {
    return (signed char)-1;
  }
  if(first_pixel_x < (signed short)0)
  {
    return (signed char)-1;
  }
  if(second_pixel_y < (signed short)0)
  {
    return (signed char)-1;
  }
  if(second_pixel_x < (signed short)0)
  {
    return (signed char)-1;
  }

  *where_to_store_the_result = sqrtf(powf(((float)first_pixel_y) - ((float)second_pixel_y), (float)2.0)
                                     + powf(((float)first_pixel_x) - ((float)second_pixel_x), (float)2.0));

  return (signed char)0;
}

