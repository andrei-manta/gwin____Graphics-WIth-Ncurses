gcc -Wconversion -Wsign-compare -fsanitize=undefined gwin_entry_point.c gwin_colors.c gwin_pixels.c gwin_2D_drawing.c gwin_PPM_file_handling.c gwin_terminal_capabilities.c gwin_logging.c gwin_error_handling.c gwin_3D_rendering.c gwin_virtual_screens.c gwin_2D_realtime_coordinator.c -lm -lncursesw
compile_return=$?
if [ $compile_return -eq 1 ]; then
  echo "Compile error"
  exit 1
fi
if [ $compile_return -eq 0 ]; then
  echo "Compile succesful"
  exit 0
fi
