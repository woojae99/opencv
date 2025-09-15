#include <iostream>
#include <opencv2/opencv.hpp>


int main(void)
{
    cv::Size s1(10,10);
    cv::Rect rect1(1,1,10,10);
    std::cout<<rect1.area()<<std::endl;
    std::cout<<rect1.x<<std::endl;
    std::cout<<rect1.br()<<std::endl;


    return 0;
}
