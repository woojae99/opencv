#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

int main(void)
{
    std::string filename1 = "/home/wj/Pictures/nature.jpeg";
    cv::Mat image1 = cv::imread(filename1, 1);

    if (image1.empty())
    {
        return 1;
    }

    float data[] = {1.0f / 9, 1.0f / 9, 1.0f / 9, 1.0f / 9, 1.0f / 9, 1.0f / 9, 1.0f / 9, 1.0f / 9, 1.0f / 9};
    cv::Mat mask(3, 3, CV_32F, data);
    cv::Mat blur(image1.size(), CV_8UC3, cv::Scalar(0,0,0));
    cv::Point m_h = mask.size() / 2;

    for (int i = m_h.y; i < image1.rows; i++)
    {
        for (int j = m_h.x; j < image1.cols; j++)
        {
            cv::Vec3b sum;
            for (int u = 0; u < mask.rows; u++)
            {
                for (int v = 0; v < mask.cols; v++)
                {
                    int y = i + u - m_h.y;
                    int x = j + v - m_h.x;
                    float w = mask.at<float>(u,v);
                    cv::Vec3b tmp = image1.at<cv::Vec3b>(y, x);
                    sum[0] += w * (float)tmp[0];
                    sum[1] += w * (float)tmp[1];
                    sum[2] += w * (float)tmp[2];
                }
            }
            blur.at<cv::Vec3b>(i, j) = cv::Vec3b((uchar)sum[0],(uchar)sum[1],(uchar)sum[2]);
        }
    }

    cv::imshow("raw", image1);
    cv::imshow("blur", blur);
    cv::waitKey(0);

    return 0;
}
