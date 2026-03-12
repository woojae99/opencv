#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

void scaling_near(cv::Mat img, cv::Mat &dst, cv::Size size)
{
    dst = cv::Mat(size, img.type(), cv::Scalar(0));
    double ratioy = (double)size.height / img.rows;
    double ratiox = (double)size.width / img.cols;

    for (int i = 0; i < dst.rows; i++)
    {
        for (int k = 0; k < dst.cols; k++)
        {
            int x = (int)cvRound(k/ratiox);
            int y = (int)cvRound(i/ratioy);

            dst.at<char>(i,k) = img.at<char>(y,x);
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
    scaling_near(raw_image,dst,cv::Size(1000,700));

    cv::imshow("image",raw_image);
    cv::imshow("dst",dst);
    cv::waitKey(0);    

    return 0;
}
