#include <stdlib.h>
#include "gwin_2D_drawing_coordinator.h"
#include "gwin_virtual_screens.h"
#include "gwin_logging.h"
#include "gwin_error_handling.h"

gwin_2D_drawing_coordinator _gwin_2D_drawing_coordinator;

signed char gwin_init_2D_drawing_coordinator(void)
{
  _gwin_2D_drawing_coordinator.drawing_virtual_screen = (gwin_virtual_screen *)NULL;

  signed char gwin_request_virtual_screen_return =
    gwin_request_virtual_screen(&_gwin_2D_drawing_coordinator.drawing_virtual_screen);

  if(gwin_request_virtual_screen_return != (signed char)0)
  {
    gwin_log_function_error("gwin_request_virtual_screen()", "returned with error", gwin_request_virtual_screen_return,
                            "gwin_init_2D_drawing_coordinator()");

    return (signed char)-1;
  }

  return (signed char)0;
}

