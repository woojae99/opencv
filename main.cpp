#include <iostream>
#include <opencv2/opencv.hpp>

int main(void)
{
    cv::VideoCapture cap(0);

    if (!cap.isOpened())
    {
        std::cerr << "카메라 연결을 확인하세요. " << std::endl;
        return -1;
    }

    cv::Mat frame;

    int fps = 10;
    int delay = cvRound(1000 / fps);
    int fourcc = cv::VideoWriter::fourcc('M', 'J', 'P', 'G');

    cv::VideoWriter writer;
    cv::Size size(
        (int)cap.get(cv::CAP_PROP_FRAME_WIDTH),
        (int)cap.get(cv::CAP_PROP_FRAME_HEIGHT));
    writer.open("./test_video.avi", fourcc, fps, size);

    while (1)
    {
        cap >> frame;
        writer << frame;

        cv::imshow("test", frame);

        if (cv::waitKey(10) == 27)
            break;
    }

    return 0;
}