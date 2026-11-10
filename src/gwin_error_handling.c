#include <stdlib.h>
#include <string.h>
#include "gwin_error_handling.h"
#define _XOPEN_SOURCE_EXTENDED
#include <ncursesw/ncurses.h>

gwin_error_log _gwin_error_log;

signed char gwin_init_error_logging()
{
  _gwin_error_log.first_error = (gwin_error_log_entry *)NULL;
  _gwin_error_log.last_error = (gwin_error_log_entry *)NULL;

  return (signed char)0;
}

signed char gwin_log_function_error(char *what_function_failed, char *failure_reason)
{
  if(what_function_failed == (char *)NULL)
  {
    return (signed char)-1;
  }
  if(failure_reason == (char *)NULL)
  {
    return (signed char)-1;
  }

  gwin_error_log_entry *new_error_entry = (gwin_error_log_entry *)malloc(sizeof(gwin_error_log_entry));
  
  if(new_error_entry == (gwin_error_log_entry *)NULL)
  {
    return (signed char)-1;
  }

  if(_gwin_error_log.first_error == (gwin_error_log_entry *)NULL)
  {
    _gwin_error_log.first_error = new_error_entry;
    _gwin_error_log.last_error = new_error_entry;

    _gwin_error_log.first_error.what_function_failed = (char *)malloc((size_t)128 * sizeof(char));
    if(_gwin_error_log.first_error.what_function_failed == (char *)NULL)
    {
      return (signed char)-1;
    }
    _gwin_error_log.first_error.failure_reason = (char *)malloc((size_t)128 * sizeof(char));
    if(_gwin_error_log.first_error.failure_reason == (char *)NULL)
    {
      return (signed char)-1;
    }
    strncpy(_gwin_error_log.first_error.what_function_failed, what_function_failed, ) //TODO incomplete
  }
}
