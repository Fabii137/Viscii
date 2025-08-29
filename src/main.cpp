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
	cv::VideoCapture cap;
	const float FPS = 60;

	if (argc < 2) {
		std::cout << "No video file path given as param, taking default";
		cap = cv::VideoCapture(std::string(RESOURCES_PATH) + "test_videos/BlueBird.mp4");
	}
	else {
		cap = cv::VideoCapture(argv[1]);
	}

	if (!cap.isOpened()) {
		std::cout << "Could not find video!";
		return -1;
	}

	cv::Mat frame;
	auto lastTime = std::chrono::high_resolution_clock::now();
	float frameDuration = 1.0 / FPS;

	while (true) {
		auto now = std::chrono::high_resolution_clock::now();
		double elapsed = std::chrono::duration<double>(now - lastTime).count();
		if (elapsed < frameDuration) {
			std::this_thread::sleep_for(std::chrono::duration<double>(frameDuration - elapsed));
			continue;
		}
		lastTime = now;

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