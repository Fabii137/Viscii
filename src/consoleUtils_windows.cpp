#include "ConsoleUtils.hpp"
#include <cstdint>

#ifdef _WIN32
#include <windows.h>

ConsoleSize getConsoleSize() {
  CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &bufferInfo);
  return {static_cast<uint32_t>(bufferInfo.dwSize.X),
          static_cast<uint32_t>(bufferInfo.dwSize.Y)};
}

void moveCursorTopLeft() {
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleCursorPosition(hConsole, {0, 0});
}

#endif
