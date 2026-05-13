#include "AsciiConverter.hpp"
#include <chrono>
#include <opencv2/core/utils/logger.hpp>
#include <stdexcept>
#include <thread>

#include "opencv2/videoio.hpp"

cv::VideoCapture openVideo(int argc, char *argv[]);

const std::string ASCII_CHARS =
    " `.-':_,^=;><+!rc*/"
    "z?sLTv)J7(|Fi{C}fI31tlu[neoZ5Yxjya]2ESwqkP6h9d4VpOGbUAKXHm8RD#$Bg0MNWQ%&@";

using Clock = std::chrono::steady_clock;

int main(int argc, char *argv[]) {
  cv::VideoCapture cap = openVideo(argc, argv);
  AsciiConverter converter(ASCII_CHARS);

  cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);

  const double videoFps = cap.get(cv::CAP_PROP_FPS);
  const double frameDuration = (videoFps > 0) ? (1.0 / videoFps) : (1.0 / 30.0);
  const auto frameStep = std::chrono::duration_cast<Clock::duration>(
      std::chrono::duration<double>(frameDuration));

  cv::Mat frame;
  auto nextFrameTime = Clock::now();

  AsciiConverter::clearConsole();

  while (true) {
    auto now = Clock::now();

    if (now < nextFrameTime) {
      std::this_thread::sleep_until(nextFrameTime);
    }

    if (!cap.read(frame) || frame.empty()) {
      break;
    }

    AsciiConverter::print(converter.convert(frame));

    nextFrameTime += frameStep;

    // catch up if behind
    now = Clock::now();
    while (nextFrameTime < now) {
      if (!cap.grab())
        break;
      nextFrameTime += frameStep;
    }
  }
}

cv::VideoCapture openVideo(int argc, char *argv[]) {
  cv::VideoCapture cap;

  if (argc < 2) {
    cap = cv::VideoCapture(std::string(RESOURCES_PATH) +
                           "test_videos/Kaleidoscope.mp4");
  } else if (argc > 2) {
    throw std::runtime_error(
        "Usage:\n\tviscii <path/to/video>\n\tviscii (default video)");
  } else {
    cap = cv::VideoCapture(argv[1]);
  }

  if (!cap.isOpened()) {
    throw std::runtime_error("Could not find video!");
  }

  return cap;
}
