#include "gwin_constants.h"
#include "gwin_colors.h"
#include "gwin_virtual_screens.h"
#include "gwin_logging.h"
#include "gwin_error_handling.h"
#include "gwin_terminal_capabilities.h"
#define _XOPEN_SOURCE_EXTENDED
#include <ncursesw/ncurses.h>

gwin_virtual_screens_table _gwin_virtual_screens_table;

signed char gwin_init_virtual_screens()
{
  signed short lines;
  signed short columns;

  signed char gwin_get_terminal_size_return = gwin_get_terminal_size(&lines, &columns);
  
  if(gwin_get_terminal_size_return != (signed char)0)
  {
    gwin_log_function_error("gwin_get_terminal_size()", "returned with error", gwin_get_terminal_size_return, 
                            "gwin_init_virtual_screens()");
  }

  _gwin_virtual_screens_table.first = (gwin_virtual_screen *)NULL;
  _gwin_virtual_screens_table.last = (gwin_virtual_screen *)NULL;

  return (signed char)0;
}
