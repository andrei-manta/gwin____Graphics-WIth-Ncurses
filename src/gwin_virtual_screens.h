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
   gwin_virtual_pixel pixels[(signed short)MAXIMUM_SUPPORTED_VIRTUAL_SCREEN_ROWS][(signed short)MAXIMUM_SUPPORTED_VIRTUAL_SCREEN_COLUMNS];
}gwin_virtual_screen;

#endif
