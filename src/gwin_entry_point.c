// remember to add each .c file in the kwargs of the compiler

#include "gwin_terminal_capabilities.h"
#include "gwin_logging.h"
#include "gwin_2D_drawing.h"
#define _XOPEN_SOURCE_EXTENDED
#include <ncursesw/ncurses.h>

int main()
{

  gwin_init_terminal_graphics();

  char debug_buf[64];
  snprintf(debug_buf, 64, "Starting gwin entry point");
  gwin_log(debug_buf);

  gwin_draw_point((signed short)10, (signed short)20, (unsigned char)200, (unsigned char)0, (unsigned char)50);

  getch();

  endwin();

  return 0;


}
