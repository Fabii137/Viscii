#include "AsciiConverter.hpp"
#include <format>
#include <iostream>

#include "opencv2/imgproc.hpp"

// ratio of character height to width in the terminal
constexpr float CHAR_RATIO = 2.4f;

AsciiConverter::AsciiConverter(const std::string &asciiChars)
    : c_AsciiChars(asciiChars) {}

std::string AsciiConverter::convert(const cv::Mat &frame) const {
  cv::Mat resized, gray;
  const COORD consoleSize = getConsoleSize();
  int width = consoleSize.X;
  int height = static_cast<int>(static_cast<double>(frame.rows) * width /
                                frame.cols / CHAR_RATIO);

  const SHORT maxHeight = consoleSize.Y - 2;
  // resize if video is bigger than terminal
  if (height > maxHeight) {
    height = maxHeight;
    width = static_cast<int>(frame.cols * CHAR_RATIO * height / frame.rows);
  }

  cv::resize(frame, resized, cv::Size(width, height));
  cv::cvtColor(resized, gray, cv::COLOR_BGR2GRAY);

  std::string ascii;
  ascii.reserve(height * width);
  for (int i = 0; i < gray.rows; i++) {
    for (int j = 0; j < gray.cols; j++) {
      const uchar grayPixel = gray.at<uchar>(i, j);
      const char c = c_AsciiChars[grayPixel * (c_AsciiChars.size() - 1) / 255];

      const cv::Vec3b pixel = resized.at<cv::Vec3b>(i, j);
      ascii += getColoredChar(pixel, c);
    }
    ascii += "\n";
  }
  return ascii;
}

void AsciiConverter::print(const std::string &ascii) {
  // start from beginning
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleCursorPosition(hConsole, {0, 0});

  std::cout << ascii;
}

void AsciiConverter::clearConsole() { std::cout << "\033[2J\033[H"; }

std::string AsciiConverter::getColoredChar(const cv::Vec3b &pixel, char c) {
  return std::format("\033[38;2;{};{};{}m{}\033[0m",
                     static_cast<int>(pixel[2]), // r
                     static_cast<int>(pixel[1]), // g
                     static_cast<int>(pixel[0]), // b
                     c);
}

COORD AsciiConverter::getConsoleSize() {
  CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &bufferInfo);
  return bufferInfo.dwSize;
}
