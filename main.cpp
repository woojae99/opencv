#include <iostream>
#include <opencv2/opencv.hpp>

int main(void)
{
    cv::Scalar blue(255, 0, 0), green(0, 255, 0), red(0, 0, 255), white(255, 255, 255);
    cv::Mat image(800, 800, CV_8UC3, white);

    cv::Point pt1(100, 100), pt2(200, 200), pt3(300, 300);
    cv::Rect r1(pt1, cv::Size(50, 50));

    cv::line(image, cv::Point(100, 100), cv::Point(200, 100), red, 1, cv::LINE_4);
    cv::line(image, cv::Point(100, 110), cv::Point(200, 110), red, 1, cv::LINE_4);

    cv::rectangle(image, cv::Point(50, 50), cv::Point(300, 300), blue, 1, cv::LINE_4);

    cv::putText(image, "hello world", cv::Point(100, 400), cv::FONT_HERSHEY_DUPLEX, 1, red, 1);
    cv::putText(image, "hello world", cv::Point(100, 600), cv::FONT_HERSHEY_DUPLEX, 2, red, 4);
    cv::circle(image, cv::Point(0, 0), 50, blue);
    cv::ellipse(image, cv::Point(600,600),cv::Size(100,60),0,0,360,red,4);

    cv::imshow("test", image);
    cv::waitKey(0);

    return 0;
}
