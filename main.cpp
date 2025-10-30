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

    // std::cout << cap.get(cv::CAP_PROP_FRAME_WIDTH) << std::endl;
    // std::cout << cap.get(cv::CAP_PROP_FRAME_HEIGHT) << std::endl;
    // std::cout << cap.get(cv::CAP_PROP_ZOOM) << std::endl;

    cap.set(cv::CAP_PROP_BRIGHTNESS, 150);
    cap.set(cv::CAP_PROP_AUTOFOCUS, 0);
    cap.set(cv::CAP_PROP_ZOOM, 100);

    cv::Mat frame;

    while (1)
    {
        if (!cap.read(frame))
            break;

        cv::imshow("test", frame);

        if (cv::waitKey(10) == 27)
            break;
    }

    return 0;
}