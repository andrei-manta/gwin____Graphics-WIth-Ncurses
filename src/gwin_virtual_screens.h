#ifndef GWIN_VIRTUAL_SCREENS_H
#define GWIN_VIRTUAL_SCREENS_H

typedef struct{
  unsigned char R;
  unsigned char G;
  unsigned char B;
}gwin_virtual_pixel;

typedef struct{
   gwin_virtual_pixel *pixels;
}gwin_virtual_screen;

typedef struct gwin_virtual_screens_table_node gwin_virtual_screens_table_node;

struct gwin_virtual_screens_table_node{
  gwin_virtual_screen current_screen;
  gwin_virtual_screens_table_node *next_screen;
};

typedef struct{
  signed short virtual_screen_rows;
  signed short virtual_screen_columns;
  gwin_virtual_screens_table_node *first;
  gwin_virtual_screens_table_node *last;
}gwin_virtual_screens_table;

extern gwin_virtual_screens_table _gwin_virtual_screens_table;

signed char gwin_init_virtual_screens();
signed char gwin_request_virtual_screen(gwin_virtual_screen **where_to_store_virtual_screen_address);
signed char gwin_delete_virtual_screen(gwin_virtual_screen *screen);
signed char gwin_write_pixel_to_virtual_screen(gwin_virtual_screen *which_virtual_screen, signed short y, signed short x,
                                               unsigned char R, unsigned char G, unsigned char B);

#endif
