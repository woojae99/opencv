#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

int main(void)
{
    std::string filename1 = "/home/wj/Pictures/nature.jpeg";
    std::string filename2 = "/home/wj/Pictures//icon.png";

    cv::Mat image = cv::imread(filename1, cv::IMREAD_COLOR);
    cv::Mat logo = cv::imread(filename2, cv::IMREAD_COLOR);

    cv::Mat result;
    cv::resize(image,image,logo.size());
    cv::subtract(logo,image,result);

    cv::imshow("result", result);
    cv::waitKey(0);

    return 0;
}
