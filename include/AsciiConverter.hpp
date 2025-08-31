#include <opencv2/opencv.hpp>
#include <Windows.h>

class AsciiConverter {
public:
	AsciiConverter(const std::string& asciiChars);
public:
	std::string convert(const cv::Mat& frame);
	void print(std::string ascii);
private:
	static std::string getColoredChar(const cv::Vec3b pixel, char c);
	static int getConsoleWidth();
private:
	const std::string& m_AsciiChars;
};