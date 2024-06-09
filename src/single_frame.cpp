

#include "single_frame.h"
#include "util.h"

std::map< std::string, cv::Rect> getAsciiMap(std::string asciiRamp){
    std::map< std::string, cv::Rect> asciiMap;

    for (char c : asciiRamp) {
        std::string s(1, c);
        cv::Mat baseImage = cv::Mat(64,64, CV_8UC3, cv::Scalar(1));
        cv::putText(baseImage, s, cv::Point(0, baseImage.rows/2), cv::FONT_HERSHEY_DUPLEX, 0.75, CV_RGB(255, 255, 255), 1);
        int minRow = INT_MAX, minCol = INT_MAX, maxRow = 0, maxCol = 0;
        for (int row = 0; row < baseImage.rows; ++row) {
            auto rowPtr = baseImage.ptr<cv::Vec3b>(row);
            for (int col = 0; col < baseImage.cols; ++col) {
                if(rowPtr[col][0] > 64) {
                    minRow = min(minRow, row);
                    minCol = min(minCol, col);
                    maxRow = max(maxRow, row);
                    maxCol = max(maxCol, col);
                }
            }
        }
        cv::Rect rect = cv::Rect_<int>(cv::Point_<int>(minCol, minRow), cv::Point_<int>(maxCol, maxRow));
        asciiMap[s] = rect;
    }
    return asciiMap;
}

cv::Mat convertToAscii(cv::Mat colored, cv::Mat greyscale, std::string asciiRamp, std::map< std::string, cv::Rect> asciiMap, bool applyImageTint) {
    cv::Mat outputImage = cv::Mat(colored.rows * 32, colored.cols * 32, CV_8UC3);

    for (int row = 0; row < outputImage.rows; ++row) {
        for (int col = 0; col < outputImage.cols; ++col) {
            outputImage.at<cv::Vec3b>(row, col) = cv::Vec3b (255,255,255);
        }
    }

    if (applyImageTint){
        for (int row = 0; row < greyscale.rows; ++row) {
            auto greyscalePtr = greyscale.ptr<uchar>(row);
            auto coloredPtr = colored.ptr<cv::Vec3b>(row);
            for (int col = 0; col < greyscale.cols; ++col) {
                float greyscaleValue = greyscalePtr[col];
                float greyscaleScalar = greyscaleValue / 255.0f;
                int asciiIndex = static_cast<int>(greyscaleScalar *
                                                  (asciiRamp.size() - 1)); // NOLINT(*-narrowing-conversions)
                char asciiChar = asciiRamp[asciiIndex];
                std::string asciiString(1, asciiChar);
                auto coloredPixel = coloredPtr[col];
                // Tint the output image using parameterization
                float a = 0.80f;
                int blue = (1.0f - a) * coloredPixel[0] + a * 255;
                int green = (1.0f - a) * coloredPixel[1] + a * 255;
                int red = (1.0f - a) * coloredPixel[2] + a * 255;
                cv::rectangle(outputImage, cv::Point(32 * col, 32 * row), cv::Point(32 * col + 32, 32 * row - 32 * 2),
                              cv::Scalar(blue, green, red), cv::FILLED);
            }
        }
    }
    for (int row = 0; row < greyscale.rows; ++row) {
        auto greyscalePtr = greyscale.ptr<uchar>(row);
        auto coloredPtr = colored.ptr<cv::Vec3b>(row);
        for (int col = 0; col < greyscale.cols; ++col) {
            float greyscaleValue = greyscalePtr[col];
            float greyscaleScalar = 1.0f - (greyscaleValue / 255.0f);
            int asciiIndex = static_cast<int>(greyscaleScalar * (asciiRamp.size() - 1)); // NOLINT(*-narrowing-conversions)
            char asciiChar = asciiRamp[asciiIndex];
            auto coloredPixel = coloredPtr[col];
            std::string asciiString(1, asciiChar);
            std::string s(1, asciiChar);
            cv::Rect rect = asciiMap[s];
            int y = (32 - rect.height) / 2;
            int x = (32 - rect.width) / 2;
            int newRow = 32 * row + y + rect.height;
            int newCol = 32 * col + x;
            int blue = coloredPixel[0];
            int green = coloredPixel[1];
            int red = coloredPixel[2];
            cv::putText(outputImage, s, cv::Point(newCol,newRow), cv::FONT_HERSHEY_DUPLEX, 0.75, CV_RGB(red, green, blue), 3);
        }
    }
    return outputImage;
}

cv::Mat convertToAsciiSingleFrame(std::string imagePath, bool applyImageTint) {
    std::string asciiRamp = ".,;><+!rc*/z?sLTv)J7(|Fi{C}fI31tlu[neoZ5Yxjya]2ESwqkP6h9d4VpOGbUAKXHm8RD#$Bg0MNWQ%&@";
    std::map< std::string, cv::Rect> asciiMap = getAsciiMap(asciiRamp);
    cv::Mat greyscaleFull = cv::imread(imagePath, 0);
    cv::Mat greyscale = cv::Mat(128, 128, CV_8UC3);
    cv::Mat coloredFull = cv::imread(imagePath);
    cv::Mat colored = cv::Mat(128, 128, CV_8UC3);
    cv::resize(greyscaleFull, greyscale, colored.size.operator()());
    cv::resize(coloredFull, colored, colored.size.operator()());
    return convertToAscii(colored, greyscale, asciiRamp, asciiMap, applyImageTint);
}