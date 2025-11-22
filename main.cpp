#include <iostream>
#include <opencv2/opencv.hpp>

int main(void)
{
    std::string filename = "/home/wj/Pictures/icon.png";

    cv::Mat image1 = cv::imread(filename, cv::IMREAD_COLOR);

    cv::Mat axis_x, axis_y, repeat, trans;

    cv::flip(image1, axis_x, 0);
    cv::flip(image1, axis_y, 1);
    cv::repeat(image1, 2, 1, repeat);
    cv::transpose(image1,trans);

    cv::imshow("show1", image1);
    // cv::imshow("show2", axis_x);
    // cv::imshow("show3", axis_y);
    // cv::imshow("repeat",repeat);
    cv::imshow("repeat",trans);
    cv::waitKey(0);

    return 0;
}
