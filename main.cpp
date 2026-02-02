#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

void minMaxFilter(cv::Mat image, cv::Mat &dst, int size, int flag = 1)
{
    dst = cv::Mat(image.size(), CV_8U, cv::Scalar(0));
    cv::Size msize(size, size);
    cv::Point mid = msize / 2;

    for (int i = mid.y; i < image.rows - mid.y; i++)
    {
        for (int k = mid.x; k < image.cols - mid.x; k++)
        {
            cv::Point start = cv::Point(k, i) - mid;
            cv::Rect roi(start, msize);
            cv::Mat mask = image(roi);

            double min, max;
            cv::minMaxLoc(mask, &min, &max);

            if (flag == 1)
            {
                dst.at<uchar>(i, k) = max;
            }
            else
            {
                dst.at<uchar>(i, k) = min;
            }
        }
    }
}

int main(void)
{
    std::string filename1 = "/home/wj/Pictures/nature.jpeg";
    cv::Mat raw_image = cv::imread(filename1, 0);
    cv::Mat min_img, max_img;

    if (raw_image.empty())
    {
        return 1;
    }

    minMaxFilter(raw_image, min_img, 5, 0);
    minMaxFilter(raw_image, max_img, 5, 1);

    cv::imshow("raw", raw_image);
    cv::imshow("min", min_img);
    cv::imshow("max", max_img);
    cv::waitKey(0);

    return 0;
}
