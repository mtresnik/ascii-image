

#include "multi_frame.h"
#include <opencv2/videoio.hpp>
#include <filesystem>
#include "single_frame.h"

void convertToAsciiMultipleFrame(std::string imagePath, const char* outputPath, bool applyImageTint) {
    std::string asciiRamp = ".,;><+!rc*/z?sLTv)J7(|Fi{C}fI31tlu[neoZ5Yxjya]2ESwqkP6h9d4VpOGbUAKXHm8RD#$Bg0MNWQ%&@";
    std::map< std::string, cv::Rect> asciiMap = getAsciiMap(asciiRamp);
    auto videoCapture = cv::VideoCapture(imagePath, cv::CAP_FFMPEG);
    if (!videoCapture.isOpened()) {
        throw std::runtime_error("Failed to open video file");
    }
    cv::Mat frameRef;
    int numFrames = 0;
    while (videoCapture.read(frameRef)) {
        char buff[100];
        snprintf(buff, sizeof(buff), "input-%d.jpg", numFrames);
        std::string buffAsStdStr = buff;
        cv::imwrite(buffAsStdStr, frameRef);
        cv::Mat asciiFrameLarge = convertToAsciiSingleFrame(buffAsStdStr, applyImageTint);
        cv::Mat asciiFrame = cv::Mat(1024, 1024, CV_8UC3);
        cv::resize(asciiFrameLarge, asciiFrame, asciiFrameLarge.size.operator()());
        std::vector<uint8_t> converted(asciiFrame.rows * asciiFrame.cols * 4, 0);
        char buff1[100];
        snprintf(buff1, sizeof(buff1), "%d.jpg", numFrames);
        std::string buffAsStdStr1 = buff1;
        cv::imwrite(buffAsStdStr1, asciiFrame);
        numFrames++;
    }
    try {
        std::filesystem::remove("video.avi");
    }
    catch(const std::filesystem::filesystem_error& err) {
        std::cout << "filesystem error: " << err.what() << '\n';
    }
    system("ffmpeg -f image2 -i %d.jpg video.avi");
    for (int i = 0; i < numFrames; ++i) {
        char buff1[100];
        snprintf(buff1, sizeof(buff1), "%d.jpg", i);
        std::string buffAsStdStr1 = buff1;
        try {
            std::filesystem::remove(buffAsStdStr1);
        }
        catch(const std::filesystem::filesystem_error& err) {
            std::cout << "filesystem error: " << err.what() << '\n';
        }
    }
    try {
        std::filesystem::remove(outputPath);
    }
    catch(const std::filesystem::filesystem_error& err) {
        std::cout << "filesystem error: " << err.what() << '\n';
    }
    char buff1[100];
    snprintf(buff1, sizeof(buff1), "ffmpeg -i video.avi -pix_fmt rgb24 %s", outputPath);
    system(buff1);
}