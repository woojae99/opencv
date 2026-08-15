#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <algorithm>
#include <filesystem>

namespace fs = std::filesystem;

std::vector<cv::Point2f> findImageCorners(cv::Mat image, cv::Size boardSize);
std::vector<cv::Point3f> calObjectCorners(cv::Size boardsize, float squaresize);

int main(void)
{
    cv::Size board(10, 7), imageSize;
    float squareSize = 2.85;

    std::vector<std::string> files;

    for (const auto &entry : fs::directory_iterator("/home/wj/Pictures/webcam"))
    {
        if (entry.is_regular_file())
        {
            files.push_back(entry.path().string());
        }
    }

    std::vector<std::vector<cv::Point2f>> points_2d;
    std::vector<std::vector<cv::Point3f>> points_3d;

    for (int i = 0; i < files.size(); i++)
    {
        cv::Mat image = cv::imread(files[i], 1);

        if (image.empty())
        {
            return 1;
        }

        std::vector<cv::Point2f> imgPoints = findImageCorners(image, board);

        if (!imgPoints.empty())
        {
            points_2d.push_back(imgPoints);
            std::vector<cv::Point3f> objPoint = calObjectCorners(board, squareSize);
            points_3d.push_back(objPoint);
        }
    }

    std::vector<cv::Mat> tvec, rvec;
    cv::Mat cameraMatrix, distcoffs;
    cv::Mat undistorted;

    cv::Mat image = cv::imread("/home/wj/Pictures/webcam/2026-08-01-165055.jpg");

    if (image.empty())
    {
        return 1;
    }

    double rms = cv::calibrateCamera(points_3d, points_2d, image.size(), cameraMatrix, distcoffs, rvec, tvec);
    cv::undistort(image,undistorted,cameraMatrix,distcoffs);
    cv::imwrite("origin.jpg", image);
    cv::imwrite("undistorted.jpg", undistorted);
    std::cout<<"cameramatrix" <<std::endl<<cameraMatrix<<std::endl;
    printf("rms error : %f\n",rms);

    cv::imshow("original",image);
    cv::imshow("undistorted",undistorted);
    cv::waitKey(0);
    


    return 0;
}

std::vector<cv::Point2f> findImageCorners(cv::Mat image, cv::Size boardSize)
{
    static int cnt = 0;
    std::vector<cv::Point2f> imgPoints;
    cv::Mat gray;

    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
    bool found = cv::findChessboardCorners(gray, boardSize, imgPoints);
    if (found)
    {
        cv::cornerSubPix(gray, imgPoints, cv::Size(11, 11), cv::Size(-1, -1), cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 30, 0.001));
        cv::drawChessboardCorners(image, boardSize, imgPoints, found);
        cv::imshow("corner_image", image);
        cv::waitKey();
        cv::destroyWindow("corner_image");
    }

    return imgPoints;
}

std::vector<cv::Point3f> calObjectCorners(cv::Size boardsize, float squaresize)
{
    std::vector<cv::Point3f> corners;
    for (int i = 0; i < boardsize.height; i++)
    {
        for (int k = 0; k < boardsize.width; k++)
        {
            float x = float(k * squaresize);
            float y = float(i * squaresize);

            corners.push_back(cv::Point3f(x, y, 0));
        }
    }
    return corners;
}
