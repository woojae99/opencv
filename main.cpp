#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

int main(void)
{
    std::string filename1 = "/home/wj/Pictures/nature.jpeg";
    cv::Mat image1 = cv::imread(filename1, cv::IMREAD_COLOR);

    cv::Scalar avg = mean(image1) / 2.0;
    cv::Mat result1 = image1 * 2;
    cv::Mat result2 = image1 * 2 - avg;
    

    cv::imshow("raw", image1);
    cv::imshow("result", result1);
        cv::imshow("result2", result2);
    
    cv::waitKey(0);

    return 0;
}
