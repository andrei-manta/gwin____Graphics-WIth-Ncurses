// remember to add each .c file in the kwargs of the compiler

#include <stdio.h>
#include "gwin_terminal_capabilities.h"
#include "gwin_logging.h"
#include "gwin_error_handling.h"
#include "gwin_virtual_screens.h"
#include "gwin_2D_drawing.h"
#include "gwin_2D_realtime_coordinator.h"
#include "gwin_PPM_file_handling.h"
#define _XOPEN_SOURCE_EXTENDED
#include <ncursesw/ncurses.h>

signed int main()
{

  signed char gwin_init_terminal_graphics_return = gwin_init_terminal_graphics();

  if(gwin_init_terminal_graphics_return != (signed char)0)
  {
    printf("Error number:%d in gwin initialisation. Aborting.\n", (signed int)gwin_init_terminal_graphics_return);

    return (signed int)-1;
  }

  char debug_buf[64];
  snprintf(debug_buf, 64, "Started gwin entry point...");
  gwin_log(debug_buf);

  int last_y = (int)_gwin_terminal_capabilities.logical_rows - (int)1;
  int last_x = (int)_gwin_terminal_capabilities.logical_columns - (int)1;

  signed short frames_per_second = (signed short)30;
  int total_frames = 60;

  // all the frames are drawn and queued first, then the realtime loop shows one per tick and deallocates it
  for(int frame_number = 0; frame_number < total_frames; frame_number++)
  {
    gwin_virtual_screen *frame_virtual_screen = (gwin_virtual_screen *)NULL;

    signed char gwin_request_virtual_screen_return = gwin_request_virtual_screen(&frame_virtual_screen);

    if(gwin_request_virtual_screen_return != (signed char)0)
    {
      gwin_log_function_error("gwin_request_virtual_screen()", "returned with error", gwin_request_virtual_screen_return, "main()");
      gwin_end_terminal_graphics();

      return (signed int)-1;
    }

    // goes from 2 to last_x - 2 over the frames
    int sweep_x = 2 + frame_number * (last_x - 4) / (total_frames - 1);

    // goes from 8 to last_x - 8 over the frames
    int circle_x = 8 + frame_number * (last_x - 16) / (total_frames - 1);

    int failed_draw_calls = 0;

    // red line, fixed at the top left, its other end sweeps along the bottom (starts vertical, then turns into diagonals)
    failed_draw_calls += (gwin_draw_line_made_of_one_color(frame_virtual_screen, (signed short)2, (signed short)2,
                                                           (signed short)(last_y - 2), (signed short)sweep_x,
                                                           255, 0, 0) != (signed char)0);

    // white point, moves along the middle row from right to left
    failed_draw_calls += (gwin_draw_point(frame_virtual_screen, (signed short)(last_y / 2), (signed short)(last_x - sweep_x),
                                          255, 255, 255) != (signed char)0);

    // cyan circle, moves along the lower part from left to right
    failed_draw_calls += (gwin_draw_circle_made_of_one_color(frame_virtual_screen, (signed short)(last_y - 10),
                                                             (signed short)circle_x, (signed short)6,
                                                             0, 255, 255) != (signed char)0);

    if(failed_draw_calls != 0)
    {
      gwin_log_function_error("gwin_draw_*()", "some draw calls returned error", failed_draw_calls, "main()");
      gwin_end_terminal_graphics();

      return (signed int)-1;
    }

    signed char gwin_2D_realtime_enqueue_virtual_screen_return = gwin_2D_realtime_enqueue_virtual_screen(frame_virtual_screen);

    if(gwin_2D_realtime_enqueue_virtual_screen_return != (signed char)0)
    {
      gwin_log_function_error("gwin_2D_realtime_enqueue_virtual_screen()", "returned with error",
                              gwin_2D_realtime_enqueue_virtual_screen_return, "main()");
      gwin_end_terminal_graphics();

      return (signed int)-1;
    }
  }

  // after the last frame the screen just stays on it, the loop only ends on error (or Ctrl+C)
  signed char gwin_2D_realtime_run_return = gwin_2D_realtime_run(frames_per_second);

  if(gwin_2D_realtime_run_return != (signed char)0)
  {
    gwin_log_function_error("gwin_2D_realtime_run()", "returned with error", gwin_2D_realtime_run_return, "main()");
    gwin_end_terminal_graphics();

    return (signed int)-1;
  }

  gwin_end_terminal_graphics();

  return (signed int)0;
}
