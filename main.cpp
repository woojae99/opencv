#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

int main(void)
{
    unsigned char data[] = {10,200,5,7,9,15,35,68,35,100,2,55,37,90, 1};

    double minval, maxval;
    int minidx[2], maxidx[2];
    cv::Point minloc, maxloc;

    cv::Mat m1(3,5,CV_8U,data);
    cv::Mat m2 (3,5,CV_8U,cv::Scalar(50));
    cv::Mat m_min, m_max;

    cv::min(m1,m2,m_min);
    cv::max(m1,m2,m_max);

    cv::minMaxIdx(m1, &minval,&maxval,minidx,maxidx);
    cv::minMaxLoc(m1,0,0,&minloc,&maxloc);
    
    std::cout<<minval<<","<<maxval<<std::endl;
    std::cout<<minidx[1]<<","<<minidx[0]<<std::endl;
    std::cout<<minloc<<","<<maxloc<<std::endl;

    return 0;
}
