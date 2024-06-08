#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

int main() {
    const char *fruitsImagePath = R"(fruits.jpg)";

    std::printf("%s\n", fruitsImagePath);

    cv::Mat image = cv::imread(fruitsImagePath);
    cv::Mat split_channels[3];
    split_channels[0] = cv::Mat(image.rows, image.cols, image.type());
    split_channels[1] = cv::Mat(image.rows, image.cols, image.type());
    split_channels[2] = cv::Mat(image.rows, image.cols, image.type());
    cv::split(image, split_channels);

    if (image.empty()) {
        std::cout << "Failed to load image" << std::endl;
        return 1;
    }
    split_channels[0].at<uchar>(0, 0) = 0;
    cv::Mat blueImage = cv::Mat(image.rows, image.cols, CV_8UC3);
    cv::Mat greenImage = cv::Mat(image.rows, image.cols, CV_8UC3);
    cv::Mat redImage = cv::Mat(image.rows, image.cols, CV_8UC3);
    for (int row = 0; row < image.rows; ++row) {
        auto *blueRowPointer = split_channels[0].ptr(row);
        auto *greenRowPointer = split_channels[1].ptr(row);
        auto *redRowPointer = split_channels[2].ptr(row);
        for (int col = 0; col < image.cols; ++col) {
            int bGrey = blueRowPointer[col];
            int gGrey = greenRowPointer[col];
            int rGrey = redRowPointer[col];
            blueImage.at<cv::Vec3b>(row, col) = cv::Vec3b(128, bGrey, bGrey);
            greenImage.at<cv::Vec3b>(row, col) = cv::Vec3b(gGrey, 128, gGrey);
            redImage.at<cv::Vec3b>(row, col) = cv::Vec3b(rGrey, rGrey, 128);
        }
    }

    std::cout << "Num channels:" << split_channels[0].channels() << std::endl;

    cv::namedWindow("blueImage", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("greenImage", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("redImage", cv::WINDOW_AUTOSIZE);
    cv::imshow("blueImage", blueImage);
    cv::imshow("greenImage", greenImage);
    cv::imshow("redImage", redImage);
    cv::waitKey(0);

    return 0;
}
