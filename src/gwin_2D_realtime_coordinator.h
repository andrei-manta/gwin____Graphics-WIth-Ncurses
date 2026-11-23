#ifndef GWIN_2D_REALTIME_COORDINATOR_H
#define GWIN_2D_REALTIME_COORDINATOR_H

#include "gwin_virtual_screens.h"

typedef struct gwin_2D_realtime_queue_node gwin_2D_realtime_queue_node;

struct gwin_2D_realtime_queue_node{
  gwin_virtual_screen *virtual_screen;
  gwin_2D_realtime_queue_node *next_node;
};

typedef struct{
  gwin_2D_realtime_queue_node *first;
  gwin_2D_realtime_queue_node *last;
}gwin_2D_realtime_queue;

extern gwin_2D_realtime_queue _gwin_2D_realtime_queue;

signed char gwin_init_2D_realtime_queue(void);

signed char gwin_2D_realtime_enqueue_virtual_screen(gwin_virtual_screen *which_virtual_screen);

signed char gwin_2D_realtime_run(signed short frames_per_second);

#endif
