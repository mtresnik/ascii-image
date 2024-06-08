#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

int main() {
    const char *fruitsImagePath = R"(fruits.jpg)";

    std::printf("%s\n", fruitsImagePath);

    cv::Mat image = cv::imread(fruitsImagePath);
    if (image.empty()) {
        std::cout << "Failed to load image" << std::endl;
        return 1;
    }

    cv::namedWindow("Image", cv::WINDOW_AUTOSIZE);
    cv::imshow("Image", image);
    cv::waitKey(0);

    return 0;
}
