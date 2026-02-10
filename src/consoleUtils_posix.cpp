#include "ConsoleUtils.hpp"

#if !defined(_WIN32)

#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>

ConsoleSize getConsoleSize() {
  winsize w{};
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  return {w.ws_col, w.ws_row};
}

void moveCursorTopLeft() { std::cout << "\033[H"; }

#endif
