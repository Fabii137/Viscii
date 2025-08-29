#include <opencv2/opencv.hpp>

int main() {
	cv::Mat img = cv::imread("example.jpg");
	if (img.empty()) {
		std::cerr << "Could not read the image" << std::endl;
		return 1;
	}
	cv::imshow("Display window", img);
	cv::waitKey(0);
	return 0;
}