#include <stdio.h>
#include <time.h>
#include "gwin_constants.h"
#include "gwin_logging.h"
#define _XOPEN_SOURCE_EXTENDED

signed char gwin_init_logging()
{
  FILE *f = fopen(GWIN_LOG_FILE_NAME, "a");
  fclose(f);

  return (signed char)0;
}

signed char gwin_log(char *message)
{
  FILE *f = fopen(GWIN_LOG_FILE_NAME, "a");

  time_t current_UTC_time = time(NULL);
  struct tm current_UTC_time_in_pretty_format;
  struct tm *gmtime_r_return = gmtime_r(&current_UTC_time, &current_UTC_time_in_pretty_format);
  if(gmtime_r_return == (struct tm *)NULL)
  {
    return (signed char)-1;
  }

  fputs(message, f);
  fprintf(f, " >>> logged by the logger at UTC time: %lld, in pretty format:%04d-%02d-%02d-%02d-%02d-%02d\n\n", current_UTC_time,
          current_UTC_time_in_pretty_format.tm_year + (int)1900, current_UTC_time_in_pretty_format.tm_mon + (int)1, 
          current_UTC_time_in_pretty_format.tm_mday, current_UTC_time_in_pretty_format.tm_hour,
          current_UTC_time_in_pretty_format.tm_min, current_UTC_time_in_pretty_format.tm_sec);

  fclose(f);
}

