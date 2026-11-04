#include<ncurses.h>
#include<math.h>

signed char gwin_init_color()
{
  start_color();

  for(int i = 1; i < 256; i++)
  {
    init_pair(i, i, i);
  }

  return (signed char)0;
}

chtype gwin_RGB_to_ncurses_solid_color(unsigned char R, unsigned char G, unsigned char B)
{
  unsigned char R_to_color_cube_r = (unsigned char)(roundf((float)R / (float)255.0 * 5.0));
  unsigned char G_to_color_cube_g = (unsigned char)(roundf((float)G / (float)255.0 * 5.0));
  unsigned char B_to_color_cube_b = (unsigned char)(roundf((float)B / (float)255.0 * 5.0));

  unsigned char resulting_color = R_to_color_cube_r * 6 * 6 + G_to_color_cube_g * 6 + B_to_color_cube_b + 16;

  return COLOR_PAIR(resulting_color);
}
