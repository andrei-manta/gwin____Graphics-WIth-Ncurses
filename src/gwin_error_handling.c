#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "gwin_error_handling.h"
#include "gwin_logging.h"
#include "gwin_constants.h"
#define _XOPEN_SOURCE_EXTENDED
#include <ncursesw/ncurses.h>

gwin_error_log _gwin_error_log;

signed char gwin_init_error_logging()
{
  _gwin_error_log.first_error = (gwin_error_log_entry *)NULL;
  _gwin_error_log.last_error = (gwin_error_log_entry *)NULL;

  return (signed char)0;
}

signed char gwin_log_function_error(char *what_function_failed, char *failure_reason, char *function_that_detected_the_failure)
{
  if(what_function_failed == (char *)NULL)
  {
    return (signed char)-1;
  }
  if(failure_reason == (char *)NULL)
  {
    return (signed char)-1;
  }

  if(function_that_detected_the_failure == (char*)NULL)
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
  }
  else
  {
    _gwin_error_log.last_error->next_entry = new_error_entry;
    _gwin_error_log.last_error = new_error_entry;
  }

  _gwin_error_log.last_error->what_function_failed = (char *)malloc((size_t)SIZE_OF_CHAR_BUFFER_FOR_ERROR_MESSAGES * sizeof(char));
  if(_gwin_error_log.last_error->what_function_failed == (char *)NULL)
  {
    return (signed char)-1;
  }
  _gwin_error_log.last_error->failure_reason = (char *)malloc((size_t)SIZE_OF_CHAR_BUFFER_FOR_ERROR_MESSAGES * sizeof(char));
  if(_gwin_error_log.last_error->failure_reason == (char *)NULL)
  {
    return (signed char)-1;
  }

  _gwin_error_log.last_error->function_that_detected_the_failure = (char *)malloc((size_t)SIZE_OF_CHAR_BUFFER_FOR_ERROR_MESSAGES * sizeof(char));
  if(_gwin_error_log.last_error->function_that_detected_the_failure == (char *)NULL)
  {
    return (signed char)-1;
  }

  strncpy(_gwin_error_log.last_error->what_function_failed, what_function_failed, (size_t)SIZE_OF_CHAR_BUFFER_FOR_ERROR_MESSAGES);
  _gwin_error_log.last_error->what_function_failed[(size_t)SIZE_OF_CHAR_BUFFER_FOR_ERROR_MESSAGES - (size_t)1] = (unsigned char)'\0';

  strncpy(_gwin_error_log.last_error->failure_reason, failure_reason, (size_t)SIZE_OF_CHAR_BUFFER_FOR_ERROR_MESSAGES);
  _gwin_error_log.last_error->failure_reason[(size_t)SIZE_OF_CHAR_BUFFER_FOR_ERROR_MESSAGES - (size_t)1] = (unsigned char)'\0';

  strncpy(_gwin_error_log.last_error->function_that_detected_the_failure, function_that_detected_the_failure,
          (size_t)SIZE_OF_CHAR_BUFFER_FOR_ERROR_MESSAGES);
  _gwin_error_log.last_error->failure_reason[(size_t)SIZE_OF_CHAR_BUFFER_FOR_ERROR_MESSAGES - (size_t)1] = (unsigned char)'\0';

  return (signed char)0;
}

signed char gwin_print_error_log()
{
  gwin_error_log_entry *current_entry = _gwin_error_log.first_error;

  while(current_entry != (gwin_error_log_entry *)NULL)
  {
    char buf[64];
    memset(buf, (char)0, (size_t)64);
    snprintf(buf, (size_t)64, "ERROR LOG ENTRY(what function failed, failure reason):");
    gwin_log(buf);
    gwin_log(current_entry->what_function_failed);
    gwin_log(current_entry->failure_reason);
    current_entry = current_entry->next_entry;
  }

  return (signed char)0;
}
