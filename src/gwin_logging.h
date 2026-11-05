#include <stdio.h>
#include "gwin_constants.h"
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

  fputs(message, f);
  fputs("\n\n", f);

  fclose(f);
}
