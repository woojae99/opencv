#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

int main(void)
{
    std::string filename1 = "/home/wj/Pictures/dark_image.png";
    cv::Mat image1 = cv::imread(filename1, 0);
    image1 = image1*0.2;
    cv::Mat result;

    if(image1.empty())
    {
        return 1;
    }

    double minV = 0.0, maxV = 0.0;

    cv::minMaxLoc(image1,&minV,&maxV);

    if (maxV - minV < 1e-9) {
        return 1;
    }

    image1.convertTo(result,CV_8UC1,255/(maxV-minV),-minV * 255.0 / (maxV - minV));

    cv::imshow("raw", image1);
    cv::imshow("result",result);
    
    cv::waitKey(0);

    return 0;
}
