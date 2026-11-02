#include <ncurses.h>

int main()
{
  initscr();
  cbreak();


  printw("Hello, World!");
  refresh();

  getch();
  getch();

  endwin();

  return 0;
}
