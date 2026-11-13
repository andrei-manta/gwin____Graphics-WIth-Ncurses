// remember to add each .c file in the kwargs of the compiler

#include <stdio.h>
#include "gwin_terminal_capabilities.h"
#include "gwin_logging.h"
#include "gwin_error_handling.h"
#include "gwin_2D_drawing.h"
#define _XOPEN_SOURCE_EXTENDED
#include <ncursesw/ncurses.h>

signed int main()
{

  signed char gwin_init_terminal_graphics_return = gwin_init_terminal_graphics();

  if(gwin_init_terminal_graphics_return != (signed char)0)
  {
    printf("Error number:%d in gwin initialisation. Aborting.\n", (signed int)gwin_init_terminal_graphics_return);

    return (signed int)-1;
  }

  char debug_buf[64];
  snprintf(debug_buf, 64, "Starting gwin entry point");
  gwin_log(debug_buf);

  getch();

  endwin();

  gwin_print_error_log();

  return (signed int)0;
}
