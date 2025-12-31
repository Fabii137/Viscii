#include "AsciiConverter.hpp"
#include <chrono>
#include <iostream>
#include <opencv2/core/utils/logger.hpp>
#include <thread>

#include "opencv2/videoio.hpp"

constexpr int FPS = 60;
constexpr float FRAME_DURATION = 1.f / FPS;

const std::string ASCII_CHARS =
    " `.-':_,^=;><+!rc*/"
    "z?sLTv)J7(|Fi{C}fI31tlu[neoZ5Yxjya]2ESwqkP6h9d4VpOGbUAKXHm8RD#$Bg0MNWQ%&@";

int main(int argc, char *argv[]) {
  cv::VideoCapture cap;
  AsciiConverter converter(ASCII_CHARS);

  cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);
  if (argc < 2) {
    cap = cv::VideoCapture(std::string(RESOURCES_PATH) +
                           "test_videos/Kaleidoscope.mp4");
  } else if (argc > 2) {
    std::cout
        << "Correct usage:\n\tviscii <path/to/video>\n\tviscii (default video)"
        << std::endl;
    return -1;
  } else {
    cap = cv::VideoCapture(argv[1]);
  }

  if (!cap.isOpened()) {
    std::cout << "Could not find video!" << std::endl;
    return -1;
  }

  cv::Mat frame;
  auto lastTime = std::chrono::high_resolution_clock::now();

  AsciiConverter::clearConsole();

  while (true) {
    const auto now = std::chrono::high_resolution_clock::now();
    const double elapsed =
        std::chrono::duration<double>(now - lastTime).count();
    if (elapsed < FRAME_DURATION) {
      std::this_thread::sleep_for(
          std::chrono::duration<double>(FRAME_DURATION - elapsed));
      continue;
    }
    lastTime = now;

    cap.read(frame);
    if (frame.empty()) {
      break;
    }
    const std::string ascii = converter.convert(frame);
    AsciiConverter::print(ascii);
  }
  return 0;
}
