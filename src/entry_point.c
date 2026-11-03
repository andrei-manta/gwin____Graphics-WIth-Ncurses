#include <ncurses.h>
#include <math.h>
#include "line_drawing.h"

int main()
{


  initscr();
  cbreak();
  noecho();

  for(int i = 1; i < 256; i++) init_pair(i, i, i);

  int counter = 0;
  for(int r = 0; r < 6; r++)
    for(int g = 0; g < 6; g++)
      for(int b = 0; b < 6; b++)
      {
        move(r, 6 * g + b);
        addch(' ' | COLOR_PAIR(16 + 6 * 6 * r + 6 * g + b));
      }

  refresh();

  getch();

  endwin();

  return 0;
}
