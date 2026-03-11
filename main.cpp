#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

void scaling(cv::Mat img, cv::Mat &dst, cv::Size size)
{
    dst = cv::Mat(size, img.type(), cv::Scalar(0));
    double ratioy = (double)size.height / img.rows;
    double ratiox = (double)size.width / img.cols;

    for (int i = 0; i < img.rows; i++)
    {
        for (int k = 0; k < img.cols; k++)
        {
            int x = (int)(k*ratiox);
            int y = (int)(i*ratioy);

            dst.at<char>(y,x) = img.at<char>(i,k);
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

    cv::Mat dst1, dst2;
    scaling(raw_image,dst1,cv::Size(1000,700));
    scaling(raw_image,dst2,cv::Size(500,250));

    cv::imshow("image",raw_image);
    cv::imshow("dst1",dst1);
    cv::imshow("dst2",dst2);
    cv::waitKey(0);    

    return 0;
}
