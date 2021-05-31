
#include "display.h"
#include "math.h"

void line_incremental(vec2 p1, vec2 p2) {
  int dx = p2.x - p1.x;
  int dy = p2.y - p1.y;
  int slope = dy ? dx / dy : 0;
  int y = p1.y;

  for (int i = p1.x; i <= p2.x; i++)
  {
    draw_pixel(i, y);
    y += slope;
  }
}

int main(void) {
  // reset all pixels to blank
  clearDisplay();

  // draw stuff
  line_incremental((vec2){0, 5}, (vec2){15, 20});
  line_incremental((vec2){0, 5}, (vec2){30, 5});
  line_incremental((vec2){15, 20}, (vec2){30, 5});

  // render frame
  printDisplay();

  // wait for signal to close
  getchar();
  return 0;
}
