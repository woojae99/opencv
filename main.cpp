#include <iostream>
#include <opencv2/opencv.hpp>


void onMouse(int event, int x, int y, int flags, void* userdata)
{
    if(event == cv::EVENT_LBUTTONDBLCLK)
    {
        std::cout<<"왼쪽 버튼 클릭"<<std::endl;
    }
}

int main(void)
{
    cv::Mat image1(300, 400, CV_8U, cv::Scalar(150));
    std::string name1 = "white";

    cv::namedWindow(name1, cv::WINDOW_NORMAL);
    cv::moveWindow(name1, 0, 0);
    cv::resizeWindow(name1, 100,100);

    cv::setMouseCallback(name1, onMouse,0);

    while(1)
    {
        cv::imshow(name1, image1);
        int  key = cv::waitKey(1);
        

        if(key == 27)
        {
            break;
        }
        else if(key == 'a')
        {
            std::cout<<"a = "<<key<<std::endl;
        }
    }

    cv::destroyAllWindows();


    return 0;
}
