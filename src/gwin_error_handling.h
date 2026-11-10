#define _XOPEN_SOURCE_EXTENDED
#include <ncursesw/ncurses.h>

typedef struct gwin_error_log_entry gwin_error_log_entry;

struct gwin_error_log_entry{
  gwin_error_log_entry *next_entry;
  char *what_function_failed;
  char *failure_reason;
};

typedef struct{
  gwin_error_log_entry *first_error;
  gwin_error_log_entry *last_error;
}gwin_error_log;

extern gwin_error_log _gwin_error_log;

signed char gwin_init_error_logging();
signed char gwin_log_function_error(char *what_function_failed, signed char failure_code);
