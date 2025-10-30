#include <iostream>
#include <opencv2/opencv.hpp>

int main(void)
{
    std::string filename = "/home/wj/Pictures/icon.png";
    
    cv::Mat image = cv::imread(filename, cv::IMREAD_COLOR);

    std::vector<int> jpg, png;

    jpg.push_back(cv::IMWRITE_JPEG_QUALITY);
    jpg.push_back(30);
    png.push_back(cv::IMWRITE_JPEG_QUALITY);
    png.push_back(100);

    cv::imwrite("test30.jpg",image,jpg);
    cv::imwrite("test2100.jpg",image,png);
    
    

    return 0;
}
