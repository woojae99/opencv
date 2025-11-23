#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

int main(void)
{
    cv::Mat m1(3, 6, CV_8UC1, cv::Scalar(10));
    cv::Mat m2(3, 6, CV_8UC1, cv::Scalar(60));

    cv::Mat add1, add2, sub, div1, div2;
    cv::Mat mask(m1.size(), CV_8UC1);

    cv::Rect rect(cv::Point(3, 0), cv::Size(3, 3));
    mask(rect).setTo(1);

    cv::add(m1, m2, add1);
    cv::add(m1, m2, add2, mask);

    std::cout << add1 << std::endl;
    std::cout << add2 << std::endl;

    return 0;
}
