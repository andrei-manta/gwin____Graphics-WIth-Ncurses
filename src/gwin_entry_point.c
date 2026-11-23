// remember to add each .c file in the kwargs of the compiler

#include <stdio.h>
#include "gwin_terminal_capabilities.h"
#include "gwin_logging.h"
#include "gwin_error_handling.h"
#include "gwin_2D_drawing.h"
#include "gwin_2D_realtime_coordinator.h"
#include "gwin_PPM_file_handling.h"
#define _XOPEN_SOURCE_EXTENDED
#include <ncursesw/ncurses.h>

signed int main()
{

  signed char gwin_init_terminal_graphics_return = gwin_init_terminal_graphics();

  if(gwin_init_terminal_graphics_return != (signed char)0)
  {
    printf("Error number:%d in gwin initialisation. Aborting.\n", (signed int)gwin_init_terminal_graphics_return);

    return (signed int)-1;
  }

  char debug_buf[64];
  snprintf(debug_buf, 64, "Started gwin entry point...");
  gwin_log(debug_buf);

  gwin_virtual_screen *screen = (gwin_virtual_screen *)NULL;
  gwin_request_virtual_screen(&screen);
  gwin_draw_circle_made_of_one_color(screen, 20, 40, 10, 255, 0, 0);
  gwin_2D_realtime_enqueue_virtual_screen(screen);

  signed char gwin_2D_realtime_run_return = gwin_2D_realtime_run((signed short)60);

  if(gwin_2D_realtime_run_return != (signed char)0)
  {
    gwin_log_function_error("gwin_2D_realtime_run()", "returned with error", gwin_2D_realtime_run_return, "main()");
    gwin_end_terminal_graphics();

    return (signed int)-1;
  }

  gwin_end_terminal_graphics();

  return (signed int)0;
}
