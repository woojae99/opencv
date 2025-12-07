#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

int main(void)
{
    std::string filename = "/home/wj/Pictures/스크린샷/스크린샷 2025-12-08 00-04-47.png";
    cv::Mat image_orin = cv::imread(filename, cv::IMREAD_COLOR);
    cv::Mat image = image_orin.clone();

    double max, min;
    cv::minMaxIdx(image, &min, &max);

    double ratio = (max - min) / 255.0;
    cv::Mat result = (image - min) / ratio;

    std::cout<<min<<","<<max<<std::endl;

    cv::imshow("result", result);
    cv::imshow("raw", image_orin);
    cv::waitKey(0);

    return 0;
}
