#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

uchar bilinear_value(cv::Mat img, double x, double y)
{
    cv::Point pt((int)x, (int)y);
    int a = img.at<uchar>(pt);
    int b = img.at<uchar>(pt + cv::Point(0, 1));
    int c = img.at<uchar>(pt + cv::Point(1, 0));
    int d = img.at<uchar>(pt + cv::Point(1, 1));

    double alpha = y - pt.y;
    double beta = x - pt.x;
    int m1 = a + (int)cvRound(alpha*(b-a));
    int m2 = c + (int)cvRound(alpha*(d-c));
    int p = m1 + (int)cvRound(m2-m1);
    return cv::saturate_cast<uchar>(p);
}

void bilinear(cv::Mat img, cv::Mat &dst, cv::Size size)
{
    dst = cv::Mat(size, img.type(), cv::Scalar(0));
    double ratioy = (double)size.height / img.rows;
    double ratiox = (double)size.width / img.cols;

    for (int i = 0; i < dst.rows; i++)
    {
        for (int k = 0; k < dst.cols; k++)
        {
            int x = (int)cvRound(k / ratiox);
            int y = (int)cvRound(i / ratioy);

            dst.at<char>(i, k) = bilinear_value(img, x, y);
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

    cv::Mat dst,dst2;
    bilinear(raw_image, dst, cv::Size(1000, 700));

    cv::resize(raw_image,dst2,cv::Size(1000,700),0,0,cv::INTER_NEAREST);

    cv::imshow("image", raw_image);
    cv::imshow("dst", dst);
    cv::imshow("dst2",dst2);
    cv::waitKey(0);

    return 0;
}
