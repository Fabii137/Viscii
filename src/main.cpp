#include <opencv2/opencv.hpp>
#include <iostream>
#include <windows.h>

#include "AsciiConverter.hpp"

const std::string ASCII_CHARS = " `.-':_,^=;><+!rc*/z?sLTv)J7(|Fi{C}fI31tlu[neoZ5Yxjya]2ESwqkP6h9d4VpOGbUAKXHm8RD#$Bg0MNWQ%&@";

int main(int argc, char *argv[]) {
	cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_WARNING);
	cv::VideoCapture cap;
	AsciiConverter converter(ASCII_CHARS);
	const float FPS = 60;

	if (argc < 2) {
		std::cout << "No video file path given as param, taking default";
		cap = cv::VideoCapture(std::string(RESOURCES_PATH) + "test_videos/Gurenge.mp4");
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
		std::string ascii = converter.convert(frame);
		converter.print(ascii);
	}
	return 0;
}