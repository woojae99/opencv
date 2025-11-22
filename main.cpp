#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

int main(void)
{
    std::string filename = "/home/wj/Pictures/nature.jpeg";

    cv::Mat image = cv::imread(filename, cv::IMREAD_COLOR);
    cv::Mat bgr[3], result;
    cv::split(image,bgr);
    cv::merge(bgr,3, result);

    cv::imshow("show1", image);
    cv::imshow("blue",bgr[0]);
    cv::imshow("green",bgr[1]);
    cv::imshow("red",bgr[2]);
    cv::imshow("combine",result);
    cv::waitKey(0);

    return 0;
}
