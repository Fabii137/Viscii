#include <opencv2/opencv.hpp>
#include <iostream>
#include <windows.h>

const std::string ASCII_CHARS = " `.-':_,^=;><+!rc*/z?sLTv)J7(|Fi{C}fI31tlu[neoZ5Yxjya]2ESwqkP6h9d4VpOGbUAKXHm8RD#$Bg0MNWQ%&@";

int getConsoleWidth() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return csbi.dwSize.X;
}

std::string getColoredChar(const cv::Vec3b& pixel, char c) {
	// windows console color
	return std::format("\033[38;2;{};{};{}m{}\033[0m", 
		(int)pixel[2], // r
		(int)pixel[1], // g
		(int)pixel[0], // b
		c
	);
}

static std::string frameToAscii(const cv::Mat& frame) {
	cv::Mat resized;
	int width = getConsoleWidth();
	int height = frame.rows * width / frame.cols / 2.4;
	cv::resize(frame, resized, cv::Size(width, height));

	std::string ascii;
	for (int i = 0; i < resized.rows; i++) {
		for (int j = 0; j < resized.cols; j++) {
			cv::Vec3b pixel = resized.at<cv::Vec3b>(i, j);
			int gray = (int)(0.114 * pixel[0] + 0.587 * pixel[1] + 0.299 * pixel[2]); // convert pixel from bgr to gray
			char c = ASCII_CHARS[gray * (ASCII_CHARS.size() - 1) / 255];
			ascii += getColoredChar(pixel, c);
		}
		ascii += "\n";
	}
	return ascii;
}

int main(int argc, char *argv[]) {
	cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_WARNING);
	if (argc < 2) {
		std::cout << "Please add the absolute video path as the second argument";
		return -1;
	}
	std::cout << argv[1] << std::endl;
	cv::VideoCapture cap(argv[1]);
	cap.set(cv::CAP_PROP_FPS, 60);
	cv::Mat frame;

	if (!cap.isOpened()) {
		std::cout << "Could not find video!";
		return -1;
	}

	while (true) {
		cap.read(frame);
		if (frame.empty()) {
			std::cout << "Grabbed empty frame!";
			break;
		}
		std::string ascii = frameToAscii(frame);
		
		// start from beginning
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(hConsole, { 0, 0 });

		std::cout << ascii << std::endl;
	}
	return 0;
}