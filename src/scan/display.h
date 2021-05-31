#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define WIDTH 50
#define HEIGHT 26

char display[WIDTH][HEIGHT];

void clearDisplay(void) { memset(display, ' ', sizeof(display)); }

void printDisplay(void) {
  for (short row = 0; row < HEIGHT; row++) {
    for (short col = 0; col < WIDTH; col++) {
      printf("%c", display[col][row]);
    }
    printf("\n");
  }
}

bool visible(int x, int y) {
  return (x >= 0 && x < WIDTH) && (y >= 0 && y < HEIGHT);
}

void draw_pixel(int x, int y) {
  if (visible(x, y)) {
    display[x][y] = '.';
  }
}
