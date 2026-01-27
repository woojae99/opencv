#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

float data1[] = {0, 1, 0, 1, -4, 1, 0, 1, 0};
float data2[] = {1, 1, 1, 1, -8, 1, 1, 1, 1};

int main(void)
{
    std::string filename1 = "/home/wj/Pictures/nature.jpeg";
    cv::Mat image = cv::imread(filename1, 0);
    cv::Mat result;

    if (image.empty())
    {
        return 1;
    }

    cv::Size size(5, 5);
    double sigmaX = 0.3 * ((size.width * 0.5) - 1) + 0.8;
    double sigmaY = 0.3 * ((size.height * 0.5) - 1) + 0.8;

    cv::GaussianBlur(image,result,size,sigmaX,sigmaY);

    cv::imshow("result",result);
    cv::imshow("raw",image);
    cv::waitKey(0);
    

    return 0;
}
