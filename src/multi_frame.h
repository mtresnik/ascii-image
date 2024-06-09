

#ifndef ASCII_IMAGE_MULTI_FRAME_H
#define ASCII_IMAGE_MULTI_FRAME_H
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cstdlib>


void convertToAsciiMultipleFrame(std::string imagePath, const char* outputPath, bool applyImageTint);

#endif //ASCII_IMAGE_MULTI_FRAME_H
