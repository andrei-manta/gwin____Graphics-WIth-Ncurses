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


    draw_line_made_of_unformatted_ascii_char(5, 10, 5, 30, (unsigned char)'I');

    draw_line_made_of_unformatted_ascii_char(8, 10, 20, 10, (unsigned char)'O');

    draw_line_made_of_unformatted_ascii_char(25, 55, 25, 15, (unsigned char)'A');

    draw_line_made_of_unformatted_ascii_char(23, 55, 10, 55, (unsigned char)'B');

    refresh();

    napms(16);


  }

  endwin();

  return 0;
}
