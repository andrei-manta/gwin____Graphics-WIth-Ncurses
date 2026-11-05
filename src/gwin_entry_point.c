#include "gwin_line_drawing.h"
#include "gwin_terminal_capabilities_and_pixel.h"
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
    for(int x = 0; x < _gwin_terminal_capabilities.logical_columns; x++)
      for(int y = 0; y < _gwin_terminal_capabilities.logical_rows; y++)
        set_logical_pixel_yx_to_rgb_and_set_physical_pixel_and_refresh(y, x, (x + counter) % 255, 0, (y + counter) % 255);
    counter += 20;
    napms(16);
  }

  getch();

  endwin();

  return 0;


}
