#include <stdlib.h>
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
  signed char gwin_get_terminal_size_return = gwin_get_terminal_size(&_gwin_virtual_screens_table.virtual_screen_lines,
                                                                     &_gwin_virtual_screens_table.virtual_screen_columns);
  
  if(gwin_get_terminal_size_return != (signed char)0)
  {
    gwin_log_function_error("gwin_get_terminal_size()", "returned with error", gwin_get_terminal_size_return, 
                            "gwin_init_virtual_screens()");

    return (signed char)-1;
  }

  _gwin_virtual_screens_table.first = (gwin_virtual_screens_table_node *)NULL;
  _gwin_virtual_screens_table.last = (gwin_virtual_screens_table_node *)NULL;

  return (signed char)0;
}

signed char gwin_request_virtual_screen(gwin_virtual_screen **where_to_store_virtual_screen_address)
{
  if(where_to_store_virtual_screen_address == NULL)
  {
    gwin_log_function_error("this function itself", "received NULL pointer as parameter", -1, "gwin_request_virtual_screen()");

    return (signed char)-1;
  }

  gwin_virtual_screens_table_node *new_virtual_screen = (gwin_virtual_screens_table_node *)malloc(sizeof(gwin_virtual_screens_table_node));

  if(new_virtual_screen == (gwin_virtual_screens_table_node *)NULL)
  {
    gwin_log_function_error("malloc()", "returned NULL", -1, "gwin_request_virtual_screen()");
    return (signed char)-2;
  }

  new_virtual_screen->current_screen.pixels = (gwin_virtual_pixel *)calloc(
    (size_t)_gwin_virtual_screens_table.virtual_screen_lines * (size_t)_gwin_virtual_screens_table.virtual_screen_columns,
    sizeof(gwin_virtual_pixel));

  if(new_virtual_screen->current_screen.pixels == (gwin_virtual_pixel *)NULL)
  {
    gwin_log_function_error("calloc()", "returned NULL", -1, "gwin_request_virtual_screen()");
    free(new_virtual_screen);
    return (signed char)-3;
  }

  new_virtual_screen->next_screen = (gwin_virtual_screens_table_node *)NULL;

  if(_gwin_virtual_screens_table.first == (gwin_virtual_screens_table_node *)NULL)
  {
    _gwin_virtual_screens_table.first = new_virtual_screen;
    _gwin_virtual_screens_table.last = new_virtual_screen;
  }
  else
  {
    _gwin_virtual_screens_table.last->next_screen = new_virtual_screen;
    _gwin_virtual_screens_table.last = new_virtual_screen;
  }

  *where_to_store_virtual_screen_address = &_gwin_virtual_screens_table.last->current_screen;

  return (signed char)0;
}

signed char gwin_delete_virtual_screen(gwin_virtual_screen *screen)
{
  if(screen == NULL)
  {
    gwin_log_function_error("this function itself", "received NULL pointer as parameter", -1, "gwin_delete_virtual_screen()");
    return (signed char)-1;
  }

  gwin_virtual_screens_table_node *prev = NULL;
  gwin_virtual_screens_table_node *node = _gwin_virtual_screens_table.first;

  while(node != NULL && &node->current_screen != screen)
  {
    prev = node;
    node = node->next_screen;
  }

  if(node == NULL)
  {
    gwin_log_function_error("this function itself", "virtual screen not found in table", -1, "gwin_delete_virtual_screen()");
    return (signed char)-2;
  }

  if(prev == NULL)
    _gwin_virtual_screens_table.first = node->next_screen;
  else
    prev->next_screen = node->next_screen;

  if(node == _gwin_virtual_screens_table.last)
    _gwin_virtual_screens_table.last = prev;   // NULL if list is now empty

  free(node->current_screen.pixels);
  free(node);

  return (signed char)0;
}
