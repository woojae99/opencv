#include <iostream>
#include <opencv2/opencv.hpp>

int main(void)
{
    std::string filename = "/home/wj/Videos/video.webm";

    cv::VideoCapture video(filename);

    if (!video.isOpened())
    {
        std::cerr << "동영상 파일을 열 수 없습니다: " << filename << std::endl;
        std::cerr << "FFmpeg 또는 코덱이 설치되어 있는지 확인하세요." << std::endl;
        return -1;
    }

    std::cout << video.get(cv::CAP_PROP_FRAME_WIDTH) << std::endl;
    std::cout << video.get(cv::CAP_PROP_FRAME_HEIGHT) << std::endl;
    std::cout << video.get(cv::CAP_PROP_ZOOM) << std::endl;

    video.set(cv::CAP_PROP_BRIGHTNESS, 0); // 이미 인코딩된 영상은 동작 x

    cv::Mat frame;

    while (1)
    {
        if (!video.read(frame))
            break;

        cv::imshow("test", frame);

        if (cv::waitKey(100) == 27)
            break;
    }

    return 0;
}