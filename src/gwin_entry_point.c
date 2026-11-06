#include "gwin_library.h"
#define _XOPEN_SOURCE_EXTENDED
#include <ncursesw/ncurses.h>

extern gwin_terminal_capabilities _gwin_terminal_capabilities;

int main()
{


  gwin_init_terminal_graphics();

  char debug_buf[64];
  snprintf(debug_buf, 64, "Starting gwin entry point");
  gwin_log(debug_buf);

  int counter = 0;

  while(1)
  {
    gwin_draw_line_made_of_one_color((counter) % _gwin_terminal_capabilities.logical_rows, 
                                     (counter) % _gwin_terminal_capabilities.logical_columns, 
                                     10, 10,
                                     (counter) % 255, 0, (counter) % 255);
    counter += 4;
    napms(16);
  }

  getch();

  endwin();

  return 0;


}
