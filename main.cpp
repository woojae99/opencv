#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

int main(void)
{
    std::string filename1 = "/home/wj/Pictures/nature.jpeg";
    cv::Mat raw_image = cv::imread(filename1, 0);
    cv::Mat min_img, max_img;

    if (raw_image.empty())
    {
        return 1;
    }

    cv::Mat dst(raw_image.size(), CV_8U, cv::Scalar(0));
    cv::Size msize(5, 5);
    cv::Point mid = msize / 2;

    for(int i=mid.y;i<raw_image.rows-mid.y;i++)
    {
        for(int k=mid.x;k<raw_image.cols-mid.x;k++)
        {
            cv::Point start = cv::Point(k,i) - mid;
            cv::Rect roi(start,msize);
            cv::Mat mask, sort;
            raw_image(roi).copyTo(mask);

            cv::Mat one_row = mask.reshape(1,1);
            cv::sort(one_row,sort,cv::SORT_EVERY_ROW);

            int median_idx = (int)one_row.total()/2;
            dst.at<uchar>(i,k) = sort.at<uchar>(median_idx);
        }
    }

    cv::imshow("raw_image", raw_image);
    cv::imshow("result", dst);
    cv::waitKey(0);

    return 0;
}
