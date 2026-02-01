#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

void trace(cv::Mat max_so, cv::Mat &pos_ck, cv::Mat &result, cv::Point pt, int low)
{
    cv::Rect rect(cv::Point(0, 0), pos_ck.size());
    if (!rect.contains(pt))
        return;

    if (pos_ck.at<uchar>(pt) == 0 && max_so.at<float>(pt) > low)
    {
        pos_ck.at<uchar>(pt) = 1;
        result.at<uchar>(pt) = 255;

        trace(max_so, pos_ck, result, pt + cv::Point(-1, -1), low);
        trace(max_so, pos_ck, result, pt + cv::Point(0, -1), low);
        trace(max_so, pos_ck, result, pt + cv::Point(1, -1), low);
        trace(max_so, pos_ck, result, pt + cv::Point(-1, 0), low);
        trace(max_so, pos_ck, result, pt + cv::Point(1, 0), low);
        trace(max_so, pos_ck, result, pt + cv::Point(-1, 1), low);
        trace(max_so, pos_ck, result, pt + cv::Point(0, 1), low);
        trace(max_so, pos_ck, result, pt + cv::Point(1, 1), low);
    }
}

void hysteresis(cv::Mat max_so, cv::Mat &result, int low, int high)
{
    cv::Mat pos_ck(max_so.size(), CV_8U, cv::Scalar(0));
    result = cv::Mat(max_so.size(), CV_8U, cv::Scalar(0));

    for (int i = 0; i < max_so.rows; i++)
    {
        for (int k = 0; k < max_so.cols; k++)
        {
            if (max_so.at<float>(i, k) > high)
            {
                trace(max_so, pos_ck, result, cv::Point(k, i), low);
            }
        }
    }
}

float data1[] = {0, 1, 0, 1, -4, 1, 0, 1, 0};
float data2[] = {1, 1, 1, 1, -8, 1, 1, 1, 1};

int main(void)
{
    std::string filename1 = "/home/wj/Pictures/nature.jpeg";
    cv::Mat raw_image = cv::imread(filename1, 0);
    cv::Mat canny_img;
    cv::Mat gaussian_img, gx, gy, sobel, direct, dst, result;

    if (raw_image.empty())
    {
        return 1;
    }

    // 가우시안 블러링
    cv::GaussianBlur(raw_image, gaussian_img, cv::Size(5, 5), 0.3);

    // 소벨 마스크 적용
    cv::Sobel(gaussian_img, gx, CV_32F, 1, 0, 3);
    cv::Sobel(gaussian_img, gy, CV_32F, 0, 1, 3);

    sobel = abs(gx) + abs(gy);

    // 기울기 방향 찾기
    direct.create(gy.size(), CV_8U);

    for (int i = 0; i < direct.rows; i++)
    {
        for (int k = 0; k < direct.cols; k++)
        {
            float tmp_gx = gx.at<float>(i, k);
            float tmp_gy = gy.at<float>(i, k);
            int theta = int(cv::fastAtan2(tmp_gy, tmp_gx) / 45);
            direct.at<uchar>(i, k) = theta % 4;
        }
    }

    // 비최대치 억제
    dst = cv::Mat(sobel.size(), CV_32F, cv::Scalar(0));

    for (int i = 1; i < sobel.rows - 1; i++)
    {
        for (int k = 1; k < sobel.cols - 1; k++)
        {
            int dir = direct.at<uchar>(i, k);
            float v1, v2;

            if (dir == 0)
            {
                v1 = sobel.at<float>(i, k - 1);
                v2 = sobel.at<float>(i, k + 1);
            }
            else if (dir == 1)
            {
                v1 = sobel.at<float>(i + 1, k + 1);
                v2 = sobel.at<float>(i - 1, k - 1);
            }
            else if (dir == 2)
            {
                v1 = sobel.at<float>(i - 1, k);
                v2 = sobel.at<float>(i + 1, k);
            }
            else if (dir == 3)
            {
                v1 = sobel.at<float>(i + 1, k - 1);
                v2 = sobel.at<float>(i - 1, k + 1);
            }

            float center = sobel.at<float>(i, k);
            if (center > v1 && center > v2)
            {
                dst.at<float>(i, k) = center;
            }
            else
            {
                dst.at<float>(i, k) = 0;
            }
        }
    }

    // 히스테리시스 스레시 홀딩
    hysteresis(dst,result,100,150);
    cv::Canny(raw_image,canny_img,100,150);

    cv::imshow("raw_image",gaussian_img);
    cv::imshow("canny_make", result);
    cv::imshow("canny_cv",canny_img);
    cv::waitKey(0);

    return 0;
}
