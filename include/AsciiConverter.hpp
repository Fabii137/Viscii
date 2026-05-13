#pragma once

#include <cstdint>
#include <opencv2/core.hpp>

class AsciiConverter {
public:
  AsciiConverter(const std::string &asciiChars);

  std::string convert(const cv::Mat &frame) const;
  static void print(const std::string &ascii);
  static void clearConsole();

private:
  static std::uint8_t convertBGR2Gray(const cv::Vec3b &pixel);
  static void appendColoredChar(std::string &ascii, const cv::Vec3b &pixel,
                                char c);

private:
  const std::string &c_AsciiChars;
};
