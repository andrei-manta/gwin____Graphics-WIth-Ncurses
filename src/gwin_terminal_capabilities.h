#include <ncurses.h>
#include <locale.h>
#include "gwin_colors.h"

typedef struct
{
  int rows;
  int columns;
}gwin_terminal_capabilities;

signed char gwin_init_terminal_graphics(gwin_terminal_capabilities * tc)
{
  setlocale(LC_ALL, "");
  initscr();
  cbreak();
  noecho();
  gwin_init_color();

  tc->rows = LINES;
  tc->columns = COLS;

  return (signed char)0;
}
