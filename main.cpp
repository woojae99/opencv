#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

void tracs(cv::Mat img, cv::Mat &dst, cv::Point pt)
{
    cv::Rect rect(cv::Point(0, 0), img.size());
    dst = cv::Mat(img.size(), img.type(), cv::Scalar(0));

    for (int i = 0; i < dst.rows; i++)
    {
        for (int j = 0; j<dst.cols; j++)
        {
            cv::Point dst_pt(j, i);
            cv::Point img_pt = dst_pt-pt;
            if(rect.contains(img_pt))
            {
                dst.at<uchar>(dst_pt) = img.at<uchar>(img_pt);
            }
        }
    }
}

int main(void)
{
    std::string filename1 = "/home/wj/Pictures/nature.jpeg";
    cv::Mat raw_image = cv::imread(filename1, 0);

    if (raw_image.empty())
    {
        return 1;
    }

    cv::Mat dst;
    tracs(raw_image,dst,cv::Point(30,100));

    cv::imshow("raw image", raw_image);
    cv::imshow("dst",dst);
    cv::waitKey(0);

    return 0;
}
