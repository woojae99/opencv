#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

int main(void)
{
    cv::Mat image1(300, 300, CV_8U, cv::Scalar(0));
    cv::Mat image2(300, 300, CV_8U, cv::Scalar(0));

    cv::Mat image3,image4,image5;
    cv::Point middle = image1.size()/2;
    cv::circle(image1,middle,100,cv::Scalar(255),-1);
    cv::rectangle(image2,cv::Point(0,0),cv::Point(150,300),cv::Scalar(255),-1);

    cv::bitwise_or(image1,image2,image3);
    cv::bitwise_and(image1,image2,image4);
    cv::imshow("image3",image3);
    cv::imshow("image4",image4);
    cv::waitKey(0);

    return 0;
}
