#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

int main(void)
{
    std::string filename1 = "/home/wj/Pictures/nature.jpeg";
    std::string filename2 = "/home/wj/Pictures/icon.png";
    cv::Mat image1 = cv::imread(filename1, cv::IMREAD_COLOR);
    cv::Mat image2 = cv::imread(filename2, cv::IMREAD_COLOR);

    cv::Mat dst1, dst2;
    cv::resize(image1, dst1, cv::Size(255, 255));
    cv::resize(image2, dst2, cv::Size(255, 255));

    cv::Mat result1 = dst1*0.5 + dst2*0.5;

    cv::imshow("result",result1);
    cv::waitKey(0);

    return 0;
}
