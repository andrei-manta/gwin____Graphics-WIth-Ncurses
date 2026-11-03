#include <ncurses.h>
#include <math.h>
#include "line_drawing.h"

int main()
{


  initscr();
  cbreak();
  noecho();

  unsigned char c = 'O';

  int center_x, center_y;
  center_x = 40;
  center_y = 20;
  float radius = 10.0;
  float screen_x_by_screen_y = 1.5;

  int desired_pos_x;
  int desired_pos_y;

  float timer = 0;
  float timer_increment = 0.1;

  int last_pos_x, last_pos_y;
  last_pos_x = 0;
  last_pos_y = 0;

  while(1)
  {


    draw_line_made_of_unformatted_ascii_char(1, 10, 20, 50, (unsigned char)'O');

    refresh();

    napms(16);


  }

  endwin();

  return 0;
}
