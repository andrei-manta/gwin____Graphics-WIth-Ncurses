#include <locale.h>
#include <stdio.h>
#include <string.h>
#include "gwin_constants.h"
#include "gwin_terminal_capabilities.h"
#include "gwin_colors.h"
#include "gwin_logging.h"
#include "gwin_error_handling.h"
#define _XOPEN_SOURCE_EXTENDED
#include <ncursesw/ncurses.h>

gwin_terminal_capabilities _gwin_terminal_capabilities;

signed char gwin_init_terminal_graphics()
{
  setlocale(LC_ALL, "");
  initscr();
  cbreak();
  noecho();
  curs_set(0);
  signed char gwin_init_color_ret = gwin_init_color();
  gwin_init_logging();
  gwin_init_error_logging();

  if(gwin_init_color_ret != (signed char)0)
  {
    char what_function_failed[(size_t)SIZE_OF_CHAR_BUFFER_FOR_ERROR_MESSAGES];
    memset(what_function_failed, (char)0, (size_t)SIZE_OF_CHAR_BUFFER_FOR_ERROR_MESSAGES);
    snprintf(what_function_failed, (size_t)SIZE_OF_CHAR_BUFFER_FOR_ERROR_MESSAGES, "gwin_init_color()");
    what_function_failed[(size_t)SIZE_OF_CHAR_BUFFER_FOR_ERROR_MESSAGES - (size_t)1] = (char)'\0';
    char failure_reason[(size_t)SIZE_OF_CHAR_BUFFER_FOR_ERROR_MESSAGES];
    memset(failure_reason, (char)0, (size_t)SIZE_OF_CHAR_BUFFER_FOR_ERROR_MESSAGES);
    snprintf(failure_reason, (size_t)SIZE_OF_CHAR_BUFFER_FOR_ERROR_MESSAGES, "returned code:%d", gwin_init_color_ret);
    failure_reason[(size_t)SIZE_OF_CHAR_BUFFER_FOR_ERROR_MESSAGES - (size_t)1] = (char)'\0';
    gwin_log_function_error(what_function_failed, failure_reason);
  }

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

