#include "gwin_colors.h"

#include <math.h>
#include "gwin_constants.h"
#define _XOPEN_SOURCE_EXTENDED
#include <ncursesw/ncurses.h>

signed char gwin_init_color()
{
  start_color();

  for(int fg = 1; fg < 256; fg++)
  {
    for(int bg = 1; bg < 256; bg++)
    {
      init_extended_pair(fg * 256 + bg, fg, bg);
    }
  }

  return (signed char)0;
}

unsigned char gwin_RGB_to_ncurses_solid_color_with_alpha(unsigned char R, unsigned char G, unsigned char B)
{
  unsigned char R_to_color_cube_r = (unsigned char)(roundf((float)R / (float)255.0 * 5.0));
  unsigned char G_to_color_cube_g = (unsigned char)(roundf((float)G / (float)255.0 * 5.0));
  unsigned char B_to_color_cube_b = (unsigned char)(roundf((float)B / (float)255.0 * 5.0));

  unsigned char resulting_color = R_to_color_cube_r * 6 * 6 + G_to_color_cube_g * 6 + B_to_color_cube_b + 16;

  return resulting_color;
}

