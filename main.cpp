#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

float data1[] = {0, 1, 0, 1, -4, 1, 0, 1, 0};
float data2[] = {1, 1, 1, 1, -8, 1, 1, 1, 1};

int main(void)
{
    std::string filename1 = "/home/wj/Pictures/nature.jpeg";
    cv::Mat image = cv::imread(filename1,0);
    cv::Mat dst,dst1,dst2,mask1(3,3,CV_32F,data1), mask2(3,3,CV_32F,data2);

    if(image.empty())
    {
        return 1;
    }


    cv::filter2D(image,dst1,CV_32F,mask1);
    cv::filter2D(image,dst2,CV_32F,mask2);
    cv::Laplacian(image,dst,CV_32F,1);
    cv::convertScaleAbs(dst1,dst1);
    cv::convertScaleAbs(dst2,dst2);
    cv::convertScaleAbs(dst,dst);

    cv::imshow("1",dst1);
    cv::imshow("2",dst2);
    cv::imshow("laplacian",dst);
    cv::waitKey(0);

    return 0;
}
