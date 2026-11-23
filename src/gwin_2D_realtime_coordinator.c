#include "gwin_2D_realtime_coordinator.h"
#include "gwin_2D_drawing_coordinator.h"
#include "gwin_virtual_screens.h"
#include "gwin_pixels.h"
#include "gwin_logging.h"
#include "gwin_error_handling.h"
#define _XOPEN_SOURCE_EXTENDED
#include <ncursesw/ncurses.h>

signed char gwin_2D_realtime_run(void)
{
  while(1)
  {
    signed char gwin_write_virtual_screen_to_physical_screen_return =
      gwin_write_virtual_screen_to_physical_screen(_gwin_2D_drawing_coordinator.drawing_virtual_screen);

    if(gwin_write_virtual_screen_to_physical_screen_return != (signed char)0)
    {
      gwin_log_function_error("gwin_write_virtual_screen_to_physical_screen()", "returned with error",
                              gwin_write_virtual_screen_to_physical_screen_return, "gwin_2D_realtime_run()");

      return (signed char)-1;
    }

    napms(16);
  }

  return (signed char)0;
}

