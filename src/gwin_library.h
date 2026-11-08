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






