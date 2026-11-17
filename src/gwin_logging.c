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
  fputs(message, f);
  fprintf(f, " >>> at UTC time: %lld\n\n", current_UTC_time);

  fclose(f);
}

