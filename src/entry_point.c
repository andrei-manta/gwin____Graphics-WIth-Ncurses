#include <ncurses.h>
#include <math.h>
#include "line_drawing.h"
#include "colors.h"

int main()
{


  initscr();
  cbreak();
  noecho();
  initcolor();

  refresh();

  getch();

  endwin();

  return 0;
}
