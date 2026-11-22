#include <math.h>
#include "gwin_pixels.h"
#include "gwin_PPM_file_handling.h"
#include "gwin_virtual_screens.h"
#include "gwin_logging.h"
#include <string.h>
#include <stdlib.h>
#define _XOPEN_SOURCE_EXTENDED
#include <ncursesw/ncurses.h>


signed char gwin_display_P6_PPM_file_in_terminal(char *file_name_from_current_folder)
{

  FILE *f = fopen(file_name_from_current_folder, "r");

  // skip P6 magic number
  while(1)
  {
    unsigned char c = (unsigned char)fgetc(f);
    if(c == (unsigned char)'\n')
    {
      break;
    }
  }

  // read width space height
  unsigned char buf[64];
  memset(buf, 0, 64);
  int buf_pointer = 0;
  while(1)
  {
    unsigned char c = (unsigned char)fgetc(f);
    if(c == (unsigned char)'\n')
    {
      break;
    }
    buf[buf_pointer++] = c;
  }

  unsigned char first_number_buffer[64];
  memset(first_number_buffer, 0, 64);
  int number_buffer_pointer = 0;
  while(1)
  {
    if(buf[number_buffer_pointer] == (unsigned char)' ')
    {
      break;
    }
    first_number_buffer[number_buffer_pointer] = buf[number_buffer_pointer];
    number_buffer_pointer++;
  }
  number_buffer_pointer++;

  unsigned char second_number_buffer[64];
  memset(second_number_buffer, 0, 64);
  int second_buffer_pointer = 0;
  while(1)
  {
    if(buf[number_buffer_pointer] == (unsigned char)'\0')
    {
      break;
    }
    second_number_buffer[second_buffer_pointer++] = buf[number_buffer_pointer];
    number_buffer_pointer++;
  }

  int width = (int)strtol(first_number_buffer, NULL, 10);
  int height = (int)strtol(second_number_buffer, NULL, 10);

  while(1)
  {
    unsigned char c = (unsigned char)fgetc(f);
    if(c == (unsigned char)'\n')
    {
      break;
    }
  }

  gwin_virtual_screen *virtual_screen;
  signed char gwin_request_virtual_screen_return = gwin_request_virtual_screen(&virtual_screen);

  if(gwin_request_virtual_screen_return != (signed char)0)
  {
    gwin_log_function_error("gwin_request_virtual_screen()", "returned with error", gwin_request_virtual_screen_return,
                            "gwin_display_P6_PPM_file_in_terminal()");
    fclose(f);
    return (signed char)-1;
  }

  unsigned char rgb_buffer[3];
  int pixels_read = 0;

  while(pixels_read < width * height)
  {
    fread(rgb_buffer, 3, 1, f);
    signed char gwin_write_pixel_to_virtual_screen_return = gwin_write_pixel_to_virtual_screen(virtual_screen,
        (signed short)(pixels_read / width), (signed short)(pixels_read % width),
        rgb_buffer[0], rgb_buffer[1], rgb_buffer[2]);

    if(gwin_write_pixel_to_virtual_screen_return != (signed char)0)
    {
      gwin_log_function_error("gwin_write_pixel_to_virtual_screen()", "returned with error",
                              gwin_write_pixel_to_virtual_screen_return, "gwin_display_P6_PPM_file_in_terminal()");
      gwin_delete_virtual_screen(virtual_screen);
      fclose(f);
      return (signed char)-2;
    }

    pixels_read++;
  }

  signed char gwin_write_virtual_screen_to_physical_screen_return = gwin_write_virtual_screen_to_physical_screen(virtual_screen);

  if(gwin_write_virtual_screen_to_physical_screen_return != (signed char)0)
  {
    gwin_log_function_error("gwin_write_virtual_screen_to_physical_screen()", "returned with error",
                            gwin_write_virtual_screen_to_physical_screen_return, "gwin_display_P6_PPM_file_in_terminal()");
    gwin_delete_virtual_screen(virtual_screen);
    fclose(f);
    return (signed char)-3;
  }

  signed char gwin_delete_virtual_screen_return = gwin_delete_virtual_screen(virtual_screen);

  if(gwin_delete_virtual_screen_return != (signed char)0)
  {
    gwin_log_function_error("gwin_delete_virtual_screen()", "returned with error", gwin_delete_virtual_screen_return,
                            "gwin_display_P6_PPM_file_in_terminal()");
    fclose(f);
    return (signed char)-4;
  }

  fclose(f);

  return (signed char)0;
}
