#include <iostream>
#include <opencv2/opencv.hpp>


int main(void)
{
    cv::Mat image1(300, 400, CV_8U, cv::Scalar(150));
    std::string name1 = "white";

    cv::namedWindow(name1, cv::WINDOW_NORMAL);
    cv::moveWindow(name1, 0, 0);

    cv::imshow(name1, image1);
    cv::waitKey(0);
    cv::destroyAllWindows();


    return 0;
}
