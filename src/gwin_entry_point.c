#include <ncurses.h>
#include "gwin_line_drawing.h"
#include "gwin_terminal_capabilities.h"

int main()
{


  gwin_terminal_capabilities tc;

  gwin_init_terminal_graphics(&tc);

  mvaddstr(5, 5, "\u2580");
  mvaddstr(10, 10, "\u2584");
  mvaddstr(15, 15, "\u2588");
  mvaddstr(20, 20, "\u281B");
  mvaddstr(25, 25, "\u28E4");
  mvaddstr(30, 30, "\u28FF");

  refresh();

  getch();

  endwin();

  return 0;


}
