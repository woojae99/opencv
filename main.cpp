#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

int main(void)
{
    std::string filename1 = "/home/wj/Pictures/nature.jpeg";
    cv::Mat image1 = cv::imread(filename1, 0);

    if (image1.empty())
    {
        return 1;
    }

    cv::Mat edge;
    cv::Mat dst = cv::Mat(image1.size(), CV_8U, cv::Scalar(0));
    cv::Point mid(3 / 2, 3 / 2);

    for (int i = mid.y; i < image1.rows - mid.y; i++)
    {
        for (int k = mid.x; k < image1.cols - mid.x; k++)
        {
            float max = 0;
            for (int u = 0; u < 3; u++)
            {
                for (int v = 0; v < 3; v++)
                {
                    int y = i + u - mid.y;
                    int x = k + v - mid.x;
                    float diff = abs(image1.at<uchar>(i, k) - image1.at<uchar>(y, x));
                    if (diff > max)
                    {
                        max = diff;
                    }
                }
            }
            dst.at<uchar>(i, k) = max;
        }
    }

    cv::imshow("raw", image1);
    cv::imshow("result", dst);
    cv::waitKey(0);

    return 0;
}
