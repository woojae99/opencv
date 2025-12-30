#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

int main(void)
{
    std::string filename1 = "/home/wj/Pictures/dark_image.png";
    cv::Mat image1 = cv::imread(filename1, 0);
    image1 = image1 * 0.2;

    if (image1.empty())
    {
        return 1;
    }

    cv::imshow("raw", image1);

    int L = 256;
    int total = image1.rows * image1.cols;

    // histogram
    std::vector<int> hist(L, 0);
    for (int y = 0; y < image1.rows; y++)
    {
        for (int x = 0; x < image1.cols; x++)
        {
            uchar tmp = image1.at<uchar>(y, x);
            hist[tmp]++;
        }
    }

    // cdf 누적합
    std::vector<int> cdf(L, 0);
    int tmp = 0;

    for (int i = 0; i < L; i++)
    {
        tmp += hist[i];
        cdf[i] = tmp;
    }

    // cdf 최소값
    int cdf_min = 0;

    for (int i = 0; i < L; i++)
    {
        if (cdf[i] != 0)
        {
            cdf_min = cdf[i];
            break;
        }
    }

    //lut 만들기
    std::vector<uchar> lut(L, 0);

    if (total == cdf_min)
    {
        for (int i = 0; i < L; ++i)
        {
            lut[i] = static_cast<uchar>(i);
        }
    }
    else
    {
        for (int i = 0; i < L; i++)
        {
            float norm = float(cdf[i]-cdf_min)/float(total - cdf_min);
            int mapped = int(norm*255.0 + 0.5f);
            if (mapped < 0) mapped = 0;
            if (mapped > 255) mapped = 255;

            lut[i] = uchar(mapped);
        }
    }

    // result
    cv::Mat result(image1.size(), image1.type());

    for(int y=0;y<image1.rows;y++)
    {
        for(int x=0;x<image1.cols;x++)
        {
            uchar v = image1.at<uchar>(y, x);   // 입력 픽셀 밝기(0~255)
            result.at<uchar>(y, x) = lut[v];
        }
    }

    cv::imshow("result",result);

    cv::waitKey(0);

    return 0;
}
