#include <math.h>
#include <locale.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "gwin_constants.h"
#include "gwin_colors.h"
#include "gwin_pixels.h"
#include "gwin_logging.h"
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

  unsigned char rgb_buffer[3];
  int pixels_read = 0;

  while(pixels_read < width * height)
  {
    fread(rgb_buffer, 3, 1, f);
    set_logical_pixel_yx_to_rgb_and_set_physical_pixel_and_refresh(pixels_read / width, pixels_read % width, 
        rgb_buffer[0], rgb_buffer[1], rgb_buffer[2]);
    pixels_read++;
  }

  fclose(f);
}






