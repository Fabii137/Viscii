#pragma once

#include <cstdint>

struct ConsoleSize {
  uint32_t width;
  uint32_t height;
};

ConsoleSize getConsoleSize();
void moveCursorTopLeft();
