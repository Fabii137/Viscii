#include "ConsoleUtils.hpp"

#if !defined(_WIN32)

#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>
/*
ConsoleSize getConsoleSize() {
  winsize w{};
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  return {}
}
*/

#endif
