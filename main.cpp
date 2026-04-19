#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

int main(void)
{
    std::string filename1 = "/home/wj/Pictures/nature.jpeg";
    cv::Mat raw_image = cv::imread(filename1);

    if(raw_image.empty())
    {
        return 0;
    }

    cv::Point2f pt1[4] = {cv::Point2f(90,170),cv::Point2f(300,120),cv::Point2f(90,285),cv::Point2f(300,320)};
    cv::Point2f pt2[4] = {cv::Point2f(60,120),cv::Point2f(340,110),cv::Point2f(60,280),cv::Point2f(340,280)};

    cv::Mat dst(raw_image.size(),CV_8U);
    cv::Mat perspect_map = cv::getPerspectiveTransform(pt1,pt2);
    cv::warpPerspective(raw_image,dst,perspect_map,raw_image.size(),cv::INTER_CUBIC);


    


    cv::imshow("raw", raw_image);
    cv::imshow("result",dst);
    cv::waitKey(0);
    return 0;
}
