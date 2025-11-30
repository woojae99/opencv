#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

int main(void)
{
    std::string filename1 = "/home/wj/Pictures/nature.jpeg";
    std::string filename2 = "/home/wj/Pictures//icon.png";

    cv::Mat image = cv::imread(filename1, cv::IMREAD_COLOR);
    cv::Mat logo = cv::imread(filename2, cv::IMREAD_COLOR);

    cv::Mat logo_th, masks[5], background, foreground, dst;
    cv::threshold(logo,logo_th, 70, 255, cv::THRESH_BINARY);
    cv::split(logo_th,masks);
    
    cv::bitwise_or(masks[0],masks[1],masks[3]);
    cv::bitwise_or(masks[2],masks[3],masks[3]);
    cv::bitwise_not(masks[3],masks[4]);

    cv::Point center1 = image.size()/2;
    cv::Point center2 = logo.size()/2;
    cv::Point start = center1 - center2;
    cv::Rect roi(start,logo.size());

    cv::bitwise_and(logo,logo,foreground,masks[3]);
    cv::bitwise_and(image(roi),image(roi),background,masks[4]);

    cv::add(foreground, background,dst);
    dst.copyTo(image(roi));

    cv::imshow("image", dst);
    cv::imshow("image2", image);
    cv::waitKey(0);
    

    return 0;
}
