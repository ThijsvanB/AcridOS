#include "serial_port.h"

#define VGA_VIDMEM 0xA0000L

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200
#define COLORS 256

void vga_setup();

void clrscr();
void draw_pixel_13h(int xpos, int ypos, int color);
void draw_char_13h(int xpos, int ypos, int code, int color);