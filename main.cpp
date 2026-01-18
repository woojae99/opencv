#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

float data1[] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};
float data2[] = {1, 1, 1, 0, 0, 0, -1, -1, -1};
// float data2[] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};

int main(void)
{
    std::string filename1 = "/home/wj/Pictures/nature.jpeg";
    cv::Mat image = cv::imread(filename1, 0);
    cv::Mat dst, dst1, dst2, mask1(3, 3, CV_32F, data1), mask2(3, 3, CV_32F, data2);

    if (image.empty())
    {
        return 1;
    }

    cv::filter2D(image,dst1,CV_32F,mask1);
    cv::filter2D(image,dst2,CV_32F,mask2);
    cv::magnitude(dst1,dst2,dst);
    dst.convertTo(dst,CV_8U);
    dst1.convertTo(dst1,CV_8U);
    dst2.convertTo(dst2,CV_8U);

    cv::imshow("raw",image);
    cv::imshow("result",dst);
    cv::imshow("result_x",dst1);
    cv::imshow("result_y",dst2);
    cv::waitKey(0);
    
    

    return 0;
}
