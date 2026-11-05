#include <ncurses.h>
#include "gwin_line_drawing.h"
#include "gwin_terminal_capabilities_and_pixel.h"

int main()
{


  gwin_init_terminal_graphics();

  char debug_buf[64];
  snprintf(debug_buf, 64, "Starting gwin entry point");
  gwin_log(debug_buf);

  mvaddstr(5, 5, "\u2580");
  mvaddstr(10, 10, "\u2584");
  mvaddstr(15, 15, "\u2588");
  mvaddstr(20, 20, "\u281B");
  mvaddstr(25, 25, "\u28E4");
  mvaddstr(30, 30, "\u28FF");

  refresh();

  for(int x = 0; x < 5; x++)
    for(int y = 0; y < 5; y++)
      set_logical_pixel_yx_to_rgb_and_refresh(y, x, 200, 0, 0);

  getch();

  endwin();

  return 0;


}
