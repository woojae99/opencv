#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <algorithm>

void cornerharris(cv::Mat image, cv::Mat &corner, int bSize, int ksize, float k);
cv::Mat draw_corner(cv::Mat corner, cv::Mat image, int thresh);
cv::Mat image, corner1, corner2;
void cornerHarris_demo(int thresh, void *);

int main(void)
{
    std::string filename1 = "/home/wj/Pictures/스크린샷 2026-06-20 23-42-57.png";
    image = cv::imread(filename1, 1);

    if (image.empty())
    {
        return 0;
    }

    int blocksize = 4;
    int aperturesize = 3;
    double k = 0.04;
    int thresh = 5;
    cv::Mat gray;

    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
    cornerharris(gray, corner1, blocksize, aperturesize, k);
    cv::cornerHarris(gray, corner2, blocksize, aperturesize, k);

    cv::namedWindow("image1");
    cv::namedWindow("image2");

    cornerHarris_demo(thresh, 0);
    cv::createTrackbar("Threshold : ", "image1", &thresh, 100, cornerHarris_demo);
    cv::waitKey(0);

    return 0;
}

void cornerharris(cv::Mat image, cv::Mat &corner, int bSize, int ksize, float k)
{
    cv::Mat dx, dy, dxy, dx2, dy2;
    corner = cv::Mat(image.size(), CV_32F, cv::Scalar(0));

    Sobel(image, dx, CV_32F, 1, 0, ksize);
    Sobel(image, dy, CV_32F, 0, 1, ksize);
    multiply(dx, dx, dx2);
    multiply(dx, dy, dxy);
    multiply(dy, dy, dy2);

    cv::Size msize(5, 5);
    cv::GaussianBlur(dx2, dx2, msize, 0);
    cv::GaussianBlur(dy2, dy2, msize, 0);
    cv::GaussianBlur(dxy, dxy, msize, 0);

    for (int i = 0; i < image.rows; i++)
    {
        for (int j = 0; j < image.cols; j++)
        {
            float a = dx2.at<float>(i, j);
            float b = dy2.at<float>(i, j);
            float c = dxy.at<float>(i, j);

            corner.at<float>(i, j) = (a * b - c * c) - k * (a + b) * (a + b);
        }
    }
}

cv::Mat draw_corner(cv::Mat corner, cv::Mat image, int thresh)
{
    int cnt = 0;
    cv::Mat norm_corner;
    normalize(corner, norm_corner, 0, 100, cv::NORM_MINMAX, CV_32FC1, cv::Mat());

    for (int i = 1; i < norm_corner.rows - 1; i++)
    {
        for (int j = 1; j < norm_corner.cols - 1; j++)
        {
            float cur = norm_corner.at<float>(i, j);
            if (cur > thresh)
            {
                if (cur > norm_corner.at<float>(i - 1, j) && cur > norm_corner.at<float>(i + 1, j) && cur > norm_corner.at<float>(i, j - 1) && cur > norm_corner.at<float>(i, j + 1))
                {
                    cv::circle(image, cv::Point(j, i), 2, cv::Scalar(255, 0, 0), -1);
                    cnt++;
                }
            }
        }
    }
    std::cout << "코너 개수 : " << cnt << std::endl;
    return image;
}

void cornerHarris_demo(int thresh, void *)
{
    cv::Mat img1 = draw_corner(corner1, image.clone(), thresh);
    cv::Mat img2 = draw_corner(corner2, image.clone(), thresh);
    cv::imshow("image1", img1);
    cv::imshow("image2", img2);
}
