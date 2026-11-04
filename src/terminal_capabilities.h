#include <ncurses.h>
#include <locale.h>
#include "colors.h"

typedef struct
{
  int rows;
  int columns;
}terminal_capabilities;

signed char init_terminal_graphics(terminal_capabilities * tc)
{
  setlocale(LC_ALL, "");
  initscr();
  cbreak();
  noecho();
  initcolor();

  tc->rows = LINES;
  tc->columns = COLS;

  return (signed char)0;
}
