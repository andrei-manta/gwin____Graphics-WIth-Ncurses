#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
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
    return (signed char)-2;
  }
  if(function_that_detected_the_failure == (char*)NULL)
  {
    return (signed char)-3;
  }

  gwin_error_log_entry *new_error_entry = (gwin_error_log_entry *)malloc(sizeof(gwin_error_log_entry));
  
  if(new_error_entry == (gwin_error_log_entry *)NULL)
  {
    return (signed char)-4;
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
    return (signed char)-5;
  }
  _gwin_error_log.last_error->failure_reason = (char *)malloc((size_t)SIZE_OF_CHAR_BUFFER_FOR_ERROR_MESSAGES * sizeof(char));
  if(_gwin_error_log.last_error->failure_reason == (char *)NULL)
  {
    return (signed char)-6;
  }

  _gwin_error_log.last_error->function_that_detected_the_failure = (char *)malloc((size_t)SIZE_OF_CHAR_BUFFER_FOR_ERROR_MESSAGES * sizeof(char));
  if(_gwin_error_log.last_error->function_that_detected_the_failure == (char *)NULL)
  {
    return (signed char)-7;
  }

  _gwin_error_log.last_error->what_time_the_error_was_thrown_at = (char *)malloc((size_t)SIZE_OF_CHAR_BUFFER_FOR_ERROR_MESSAGES
                                                                                  * sizeof(char));
  if(_gwin_error_log.last_error->what_time_the_error_was_thrown_at == (char *)NULL)
  {
    return (signed char)-8;
  }

  strncpy(_gwin_error_log.last_error->what_function_failed, what_function_failed, (size_t)SIZE_OF_CHAR_BUFFER_FOR_ERROR_MESSAGES);
  _gwin_error_log.last_error->what_function_failed[(size_t)SIZE_OF_CHAR_BUFFER_FOR_ERROR_MESSAGES - (size_t)1] = (char)'\0';

  strncpy(_gwin_error_log.last_error->failure_reason, failure_reason, (size_t)SIZE_OF_CHAR_BUFFER_FOR_ERROR_MESSAGES);
  _gwin_error_log.last_error->failure_reason[(size_t)SIZE_OF_CHAR_BUFFER_FOR_ERROR_MESSAGES - (size_t)1] = (char)'\0';

  strncpy(_gwin_error_log.last_error->function_that_detected_the_failure, function_that_detected_the_failure,
          (size_t)SIZE_OF_CHAR_BUFFER_FOR_ERROR_MESSAGES);
  _gwin_error_log.last_error->failure_reason[(size_t)SIZE_OF_CHAR_BUFFER_FOR_ERROR_MESSAGES - (size_t)1] = (char)'\0';

  time_t current_UTC_time = time(NULL);
  struct tm current_UTC_time_in_pretty_format;
  struct tm *gmtime_r_return = gmtime_r(&current_UTC_time, &current_UTC_time_in_pretty_format);
  if(gmtime_r_return == (struct tm *)NULL)
  {
    return (signed char)-9;
  }

  snprintf(_gwin_error_log.last_error->what_time_the_error_was_thrown_at, (size_t)SIZE_OF_CHAR_BUFFER_FOR_ERROR_MESSAGES,
           " >>> error logged by error system at UTC time: %lld, in pretty format:%04d-%02d-%02d-%02d-%02d-%02d\n\n", current_UTC_time,
          current_UTC_time_in_pretty_format.tm_year + (int)1900, current_UTC_time_in_pretty_format.tm_mon + (int)1, 
          current_UTC_time_in_pretty_format.tm_mday, current_UTC_time_in_pretty_format.tm_hour,
          current_UTC_time_in_pretty_format.tm_min, current_UTC_time_in_pretty_format.tm_sec);

  return (signed char)0;
}

signed char gwin_print_error_log()
{
  gwin_error_log_entry *current_entry = _gwin_error_log.first_error;

  while(current_entry != (gwin_error_log_entry *)NULL)
  {
    char buf[128];
    memset(buf, (char)0, (size_t)128);
    snprintf(buf, (size_t)128, "ERROR LOG ENTRY(what function failed, failure reason, what function caught it):");
    gwin_log(buf);
    gwin_log(current_entry->what_function_failed);
    gwin_log(current_entry->failure_reason);
    gwin_log(current_entry->function_that_detected_the_failure);
    current_entry = current_entry->next_entry;
  }

  return (signed char)0;
}
