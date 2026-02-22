#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

int main(void)
{
    std::string filename1 = "/home/wj/Pictures/nature.jpeg";
    cv::Mat raw_image = cv::imread(filename1, 0);
    cv::Mat th_img, open, close;

    if (raw_image.empty())
    {
        return 1;
    }

    cv::threshold(raw_image, th_img, 128, 255, cv::THRESH_BINARY);

    cv::Mat mask = (cv::Mat_<uchar>(3,3) <<
    0,1,0,
    1,1,1,
    0,1,0
);

    cv::morphologyEx(th_img, open, cv::MORPH_OPEN, mask, cv::Point(-1, -1), 1);
    cv::morphologyEx(th_img, close, cv::MORPH_CLOSE, mask, cv::Point(-1, -1), 1);

    cv::imshow("raw", raw_image);
    cv::imshow("open", open);
    cv::imshow("close", close);
    cv::waitKey(0);

    return 0;
}
