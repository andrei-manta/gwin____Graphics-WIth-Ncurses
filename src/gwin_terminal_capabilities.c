#include <locale.h>
#include <stdio.h>
#include <string.h>
#include "gwin_constants.h"
#include "gwin_terminal_capabilities.h"
#include "gwin_colors.h"
#include "gwin_logging.h"
#include "gwin_error_handling.h"
#include "gwin_virtual_screens.h"
#define _XOPEN_SOURCE_EXTENDED
#include <ncursesw/ncurses.h>

gwin_terminal_capabilities _gwin_terminal_capabilities;

signed char gwin_init_terminal_graphics()
{
  char *setlocale_return = setlocale(LC_ALL, "");
  initscr();
  int cbreak_return = cbreak();
  int noecho_return = noecho();
  int curs_set_return = curs_set(0);
  signed char gwin_init_color_return = gwin_init_color();
  signed char gwin_init_logging_return = gwin_init_logging();
  signed char gwin_init_error_logging_return = gwin_init_error_logging();
  signed char gwin_init_virtual_screens_return = gwin_init_virtual_screens();
  signed char gwin_get_terminal_size_return = gwin_get_terminal_size(&(_gwin_terminal_capabilities.rows), 
                                                                     &(_gwin_terminal_capabilities.columns));

  if(gwin_init_logging_return != (signed char)0)
  {
    //can't log an error in the logging systems
    return (signed char)-2;
  }

  if(gwin_init_error_logging_return != (signed char)0)
  {
    //can't log an error in the logging systems
    return (signed char)-3;
  }

  if(setlocale_return == (char *)NULL)
  {
    gwin_log_function_error("setlocale()", "returned error", (signed int)NULL, "gwin_init_terminal_graphics()");
    
    return (signed char)-1;
  }

  //upon error in initscr(), ncurses prints to stderr and exits by itself

  if(cbreak_return != (int)OK)
  {
    gwin_log_function_error("cbreak()", "returned not OK", ERR, "gwin_init_terminal_graphics()");
  
    return (signed char)-1;
  }

  if(noecho_return != (int)OK)
  {
    gwin_log_function_error("noecho()", "returned not OK", ERR, "gwin_init_terminal_graphics()");
  
    return (signed char)-1;
  }

  if(curs_set_return == (int)ERR)
  {
    gwin_log_function_error("curs_set()", "returned ERR", ERR, "gwin_init_terminal_graphics()");
  
    return (signed char)-1;
  }

  if(gwin_init_color_return != (signed char)0)
  {
    gwin_log_function_error("gwin_init_color()", "returned with error", (signed char)gwin_init_color_return, "gwin_init_terminal_graphics()");

    return (signed char)-1;
  }

  if(gwin_get_terminal_size_return != (signed char)0)
  {
    gwin_log_function_error("gwin_get_terminal_size()", "returned with error", (signed char)gwin_get_terminal_size_return,
                            "gwin_init_terminal_graphics()");

    return (signed char)-1;
  }

  if(gwin_init_virtual_screens_return != (signed char)0)
  {
    gwin_log_function_error("gwin_init_virtual_screens()", "returned with error", 
                            gwin_init_virtual_screens_return, "gwin_init_terminal_graphics()");
  }

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
    
      signed int setcchar_return;
      if((setcchar_return = 
        (signed int)setcchar(&_gwin_terminal_capabilities.physical_pixel_grid[rows][columns].physical_cell_contents, 
                             L"", A_NORMAL, 0, NULL)) != OK)
      {
        gwin_log_function_error("setcchar()", "returned with error", setcchar_return, "gwin_init_terminal_graphics()");
      }
    }
  }

  return (signed char)0;
}

signed char gwin_get_terminal_size(signed short *where_to_store_lines,
    signed short *where_to_store_columns)
{
  if(where_to_store_lines == (signed short*)NULL)
  {
    return (signed char)-1;
  }
  if(where_to_store_columns == (signed short*)NULL)
  {
    return (signed char)-1;
  }

  *where_to_store_lines = (signed short)LINES;
  *where_to_store_columns = (signed short)COLS;

  return (signed char)0;
}
