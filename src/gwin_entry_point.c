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
  
  int counter = 0;
  while(1)
  {
    gwin_draw_circle_made_of_one_color((40 + counter) % 50, (40 + counter / 2) % 50, (10 + counter) % 15, (100 + counter) % 255, 0, 100);
    counter++;

    napms(16);
  }

  getch();

  endwin();

  return 0;


}
