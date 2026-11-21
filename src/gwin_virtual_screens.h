#ifndef GWIN_VIRTUAL_SCREENS_H
#define GWIN_VIRTUAL_SCREENS_H

typedef struct{
  signed short x;
  signed short y;
  unsigned char R;
  unsigned char G;
  unsigned char B;
}gwin_virtual_pixel;

typedef struct{
   gwin_virtual_pixel *pixels;
}gwin_virtual_screen;

typedef struct{
  gwin_virtual_screen *first;
  gwin_virtual_screen *last;
}gwin_virtual_screens_table;

extern gwin_virtual_screens_table _gwin_virtual_screens_table;

signed char gwin_init_virtual_screens();

#endif
