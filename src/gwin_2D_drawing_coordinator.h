#ifndef GWIN_2D_DRAWING_COORDINATOR_H
#define GWIN_2D_DRAWING_COORDINATOR_H

#include "gwin_virtual_screens.h"

typedef struct{
  gwin_virtual_screen *drawing_virtual_screen;
}gwin_2D_drawing_coordinator;

extern gwin_2D_drawing_coordinator _gwin_2D_drawing_coordinator;

signed char gwin_init_2D_drawing_coordinator(void);

#endif
