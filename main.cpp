#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

bool check_match(cv::Mat img, cv::Point start, cv::Mat mask, int mode = 0)
{
    for (int u = 0 ; u< mask.rows;u++)
    {
        for(int v = 0;v<mask.cols;v++)
        {
            cv::Point pt(v,u);
            int m = mask.at<uchar>(pt);
            int p = img.at<uchar>(start+pt);

            bool ch = (p==255);
            if(m==1 && ch==mode)
            {
                return false;
            }
        }
    }
    return true;
}

void erosion(cv::Mat img, cv::Mat& dst, cv::Mat mask)
{
    dst = cv::Mat(img.size(), CV_8U, cv::Scalar(0));

    cv::Point mid = mask.size() / 2;
    for (int i = mid.y; i < img.rows - mid.y; i++)
    {
        for(int k = mid.x; k<img.cols - mid.x;k++)
        {
            cv::Point start = cv::Point(k,i) - mid;
            bool check = check_match(img,start,mask,0);
            dst.at<uchar>(i,k) = (check) ? 255:0;
        }
    }
}

int main(void)
{
    std::string filename1 = "/home/wj/Pictures/nature.jpeg";
    cv::Mat raw_image = cv::imread(filename1, 0);
    cv::Mat th_img, dst1;

    if (raw_image.empty())
    {
        return 1;
    }

    cv::threshold(raw_image,th_img,128,255,cv::THRESH_BINARY);

    uchar data[] = {0,1,0,1,1,1,0,1,0};
    cv::Mat mask(3,3,CV_8UC1,data);

    erosion(th_img,dst1,(cv::Mat)mask);

    cv::imshow("raw", raw_image);
    cv::imshow("dst", dst1);
    cv::waitKey(0);    

    return 0;
}
