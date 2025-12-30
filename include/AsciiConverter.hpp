#include <Windows.h>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>

class AsciiConverter {
public:
  AsciiConverter(const std::string &asciiChars);

public:
  std::string convert(const cv::Mat &frame);
  void print(const std::string &ascii);

private:
  static std::string getColoredChar(const cv::Vec3b &pixel, char c);
  static int getConsoleWidth();

private:
  const std::string &c_AsciiChars;
};
