

#ifndef ASCII_IMAGE_SINGLE_FRAME_H
#define ASCII_IMAGE_SINGLE_FRAME_H
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cstdlib>

std::map< std::string, cv::Rect> getAsciiMap(std::string asciiRamp);

cv::Mat convertToAscii(cv::Mat colored, cv::Mat greyscale, std::string asciiRamp, std::map< std::string, cv::Rect> asciiMap, bool applyImageTint=false);

cv::Mat convertToAsciiSingleFrame(std::string imagePath, bool applyImageTint);

#endif //ASCII_IMAGE_SINGLE_FRAME_H
