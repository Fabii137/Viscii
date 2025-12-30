#include "AsciiConverter.hpp"
#include <format>
#include <iostream>

AsciiConverter::AsciiConverter(const std::string &asciiChars)
    : c_AsciiChars(asciiChars) {}

std::string AsciiConverter::convert(const cv::Mat &frame) {
  cv::Mat resized, gray;
  int width = getConsoleWidth();
  int height = (double)frame.rows * width / frame.cols / 2.4;
  cv::resize(frame, resized, cv::Size(width, height));
  cv::cvtColor(resized, gray, cv::COLOR_BGR2GRAY);

  std::string ascii;
  for (int i = 0; i < gray.rows; i++) {
    for (int j = 0; j < gray.cols; j++) {
      uchar grayPixel = gray.at<uchar>(i, j);
      char c = c_AsciiChars[grayPixel * (c_AsciiChars.size() - 1) / 255];

      cv::Vec3b pixel = resized.at<cv::Vec3b>(i, j);
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

  std::cout << ascii << std::endl;
}

std::string AsciiConverter::getColoredChar(const cv::Vec3b &pixel, char c) {
  // windows console color
  return std::format("\033[38;2;{};{};{}m{}\033[0m",
                     (int)pixel[2], // r
                     (int)pixel[1], // g
                     (int)pixel[0], // b
                     c);
}

int AsciiConverter::getConsoleWidth() {
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
  return csbi.dwSize.X;
}
