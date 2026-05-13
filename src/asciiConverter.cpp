#include "AsciiConverter.hpp"
#include "ConsoleUtils.hpp"

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string>

#include "opencv2/imgproc.hpp"

constexpr const char *RESET_COLOR = "\033[0m";
constexpr const char *CLEAR = "\033[2J\033[H";
// ratio of character height to width in the terminal
constexpr float CHAR_RATIO = 2.4f;

AsciiConverter::AsciiConverter(const std::string &asciiChars)
    : c_AsciiChars(asciiChars) {}

std::string AsciiConverter::convert(const cv::Mat &frame) const {
  cv::Mat resized;
  ConsoleSize consoleSize = getConsoleSize();
  int width = consoleSize.width;
  int height = static_cast<int>(static_cast<double>(frame.rows) * width /
                                frame.cols / CHAR_RATIO);

  int maxHeight = std::max(consoleSize.height - 2, 1);
  // resize if video is bigger than terminal
  if (height > maxHeight) {
    height = maxHeight;
    width = static_cast<int>(frame.cols * CHAR_RATIO * height / frame.rows);
  }

  cv::resize(frame, resized, {width, height});
  std::string ascii;
  ascii.reserve(height * width * 32);

  for (int i = 0; i < height; ++i) {
    const cv::Vec3b *row = resized.ptr<cv::Vec3b>(i);
    for (int j = 0; j < width; ++j) {
      const cv::Vec3b &pixel = row[j];
      std::uint8_t grayPixel = convertBGR2Gray(pixel);
      const char c = c_AsciiChars[grayPixel * (c_AsciiChars.size() - 1) / 255];

      appendColoredChar(ascii, pixel, c);
    }
    ascii += "\n";
  }
  ascii += RESET_COLOR;
  return ascii;
}

void AsciiConverter::print(const std::string &ascii) {
  moveCursorTopLeft();
  std::cout << ascii;
}

void AsciiConverter::clearConsole() { std::cout << CLEAR; }

std::uint8_t AsciiConverter::convertBGR2Gray(const cv::Vec3b &pixel) {
  return static_cast<std::uint8_t>(pixel[0] * 0.114f + // b
                                   pixel[1] * 0.587f + // g
                                   pixel[2] * 0.299f); // r
}

void AsciiConverter::appendColoredChar(std::string &ascii,
                                       const cv::Vec3b &pixel, char c) {
  ascii += "\033[38;2;";
  ascii += std::to_string(pixel[2]); // r
  ascii += ";";
  ascii += std::to_string(pixel[1]); // g
  ascii += ";";
  ascii += std::to_string(pixel[0]); // b
  ascii += "m";
  ascii += c;
}
