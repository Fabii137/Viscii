#pragma once

struct ConsoleSize {
  int width;
  int height;
};

ConsoleSize getConsoleSize();
void moveCursorTopLeft();
