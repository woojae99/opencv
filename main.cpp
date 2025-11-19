#include <iostream>
#include <opencv2/opencv.hpp>

int main(void)
{
    std::string filename = "/home/wj/Pictures/icon.png";

    cv::Mat image = cv::imread(filename,cv::IMREAD_COLOR);

    cv::Vec3b pixel = image.at<cv::Vec3b>(100,200);
    std::cout<<(int)pixel[0]<<std::endl;
    std::cout<<(int)pixel[1]<<std::endl;
    std::cout<<(int)pixel[2]<<std::endl;

    image.at<cv::Vec3b>(5,5) = cv::Vec3b(0,0,255);
    image -= cv::Scalar(100, 0, 0);
    image = image * 0.2;

    cv::imshow("image", image);
    cv::waitKey(0);

    return 0;
}
