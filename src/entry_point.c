#include <ncurses.h>
#include <math.h>
#include "line_drawing.h"

int main()
{


  initscr();
  cbreak();
  noecho();

  while(1)
  {


    for(int i = 0;;i++)
    {
      erase();

      draw_line_made_of_formatted_ascii_char(i / 2 % 20, 2, (i / 3 + 10) % 20, 80, 'O' | A_DIM);
    
      refresh();
    
      napms(16);
    }


  }

  endwin();

  return 0;
}
