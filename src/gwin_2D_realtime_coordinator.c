#include <stdlib.h>
#include "gwin_2D_realtime_coordinator.h"
#include "gwin_virtual_screens.h"
#include "gwin_pixels.h"
#include "gwin_logging.h"
#include "gwin_error_handling.h"
#define _XOPEN_SOURCE_EXTENDED
#include <ncursesw/ncurses.h>

gwin_2D_realtime_queue _gwin_2D_realtime_queue;

signed char gwin_init_2D_realtime_queue(void)
{
  _gwin_2D_realtime_queue.first = (gwin_2D_realtime_queue_node *)NULL;
  _gwin_2D_realtime_queue.last = (gwin_2D_realtime_queue_node *)NULL;

  return (signed char)0;
}

signed char gwin_2D_realtime_enqueue_virtual_screen(gwin_virtual_screen *which_virtual_screen)
{
  if(which_virtual_screen == (gwin_virtual_screen *)NULL)
  {
    gwin_log_function_error("this function itself", "received NULL pointer as parameter", -1,
                            "gwin_2D_realtime_enqueue_virtual_screen()");

    return (signed char)-1;
  }

  gwin_2D_realtime_queue_node *new_node = (gwin_2D_realtime_queue_node *)malloc(sizeof(gwin_2D_realtime_queue_node));

  if(new_node == (gwin_2D_realtime_queue_node *)NULL)
  {
    gwin_log_function_error("malloc()", "returned NULL", -1, "gwin_2D_realtime_enqueue_virtual_screen()");

    return (signed char)-2;
  }

  new_node->virtual_screen = which_virtual_screen;
  new_node->next_node = (gwin_2D_realtime_queue_node *)NULL;

  if(_gwin_2D_realtime_queue.first == (gwin_2D_realtime_queue_node *)NULL)
  {
    _gwin_2D_realtime_queue.first = new_node;
    _gwin_2D_realtime_queue.last = new_node;
  }
  else
  {
    _gwin_2D_realtime_queue.last->next_node = new_node;
    _gwin_2D_realtime_queue.last = new_node;
  }

  return (signed char)0;
}

signed char gwin_2D_realtime_run(signed short frames_per_second)
{
  if(frames_per_second <= (signed short)0)
  {
    gwin_log_function_error("this function itself", "frames_per_second is not positive", -1, "gwin_2D_realtime_run()");

    return (signed char)-1;
  }

  int milliseconds_per_frame = (int)1000 / (int)frames_per_second;

  while(1)
  {
    gwin_2D_realtime_queue_node *node_to_render = _gwin_2D_realtime_queue.first;

    if(node_to_render != (gwin_2D_realtime_queue_node *)NULL)
    {
      _gwin_2D_realtime_queue.first = node_to_render->next_node;

      if(_gwin_2D_realtime_queue.first == (gwin_2D_realtime_queue_node *)NULL)
      {
        _gwin_2D_realtime_queue.last = (gwin_2D_realtime_queue_node *)NULL;
      }

      signed char gwin_write_virtual_screen_to_physical_screen_return =
        gwin_write_virtual_screen_to_physical_screen(node_to_render->virtual_screen);

      signed char gwin_delete_virtual_screen_return = gwin_delete_virtual_screen(node_to_render->virtual_screen);

      free(node_to_render);

      if(gwin_write_virtual_screen_to_physical_screen_return != (signed char)0)
      {
        gwin_log_function_error("gwin_write_virtual_screen_to_physical_screen()", "returned with error",
                                gwin_write_virtual_screen_to_physical_screen_return, "gwin_2D_realtime_run()");

        return (signed char)-2;
      }

      if(gwin_delete_virtual_screen_return != (signed char)0)
      {
        gwin_log_function_error("gwin_delete_virtual_screen()", "returned with error",
                                gwin_delete_virtual_screen_return, "gwin_2D_realtime_run()");

        return (signed char)-3;
      }
    }

    napms(milliseconds_per_frame);
  }

  return (signed char)0;
}
