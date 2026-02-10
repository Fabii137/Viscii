#pragma once

#include <opencv2/core.hpp>

class AsciiConverter {
public:
  AsciiConverter(const std::string &asciiChars);

  std::string convert(const cv::Mat &frame) const;
  static void print(const std::string &ascii);
  static void clearConsole();

private:
  static std::string getColoredChar(const cv::Vec3b &pixel, char c);

private:
  const std::string &c_AsciiChars;
};
