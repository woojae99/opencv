#include <iostream>
#include <opencv2/opencv.hpp>


int main(void)
{
    float data[] = {1,5,3,6,7,4,98,1,10};

    cv::Mat m1(3,3,CV_32F, data);
    std::cout<<m1<<std::endl<<std::endl;;

    cv::Mat m2 = m1.t();
    std::cout << m2 << std::endl;

    std::cout<<m2.inv()<<std::endl;



    return 0;
}
