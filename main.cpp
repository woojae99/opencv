#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

int main(void)
{
    cv::Mat m1 = cv::Mat::ones(3, 3, CV_32F) * 3;
    m1.at<float>(0, 1) = 1;

    for (int i = 0; i < 3; i++)
    {
        for (int k = 0; k < 3; k++)
        {
            std::cout << m1.at<float>(i, k);
            std::cout << ", ";
        }
        std::cout << std::endl;
    }

    cv::Mat m2 = cv::Mat::ones(3,3,CV_32F);
    m2.at<float>(1,0) = 10;
    float *ptr_m2 = m2.ptr<float>(1,0);
    *(ptr_m2 + 1) = 11;
    std::cout<<m2<<std::endl;

    return 0;
}
