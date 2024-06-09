#include <iostream>
#include "single_frame.h"
#include "multi_frame.h"

void singleFrame() {
    std::string imagePath = "fruits.jpg";
    cv::Mat outputImage = convertToAsciiSingleFrame(imagePath, false);
    cv::imwrite("ascii.jpg", outputImage);
}

void multiFrame() {
    std::string imagePath = "shades.gif";
    convertToAsciiMultipleFrame(imagePath, "ascii-gif.gif", true);
}

int main() {
    singleFrame();
    return 0;
}
