#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <algorithm>

void hough_coord(cv::Mat image, cv::Mat &acc_mat, double rho, double theta);
void acc_mask(cv::Mat acc_mat, cv::Mat &acc_dst, cv::Size, int thresh);
void thres_lines(cv::Mat acc_dst, cv::Mat &lines, double _rho, double theta, int thresh);
void sort_lines(cv::Mat lines, std::vector<cv::Vec2f> &s_line);
void houghLines(cv::Mat src, std::vector<cv::Vec2f> &s_lines, double rho, double theta, int thresh);
void draw_houghLines(cv::Mat src, cv::Mat &dst, std::vector<cv::Vec2f> lines, int nline);

int main(void)
{
    std::string filename1 = "/home/wj/Pictures/nature.jpeg";
    cv::Mat raw_image = cv::imread(filename1, 0);

    if (raw_image.empty())
    {
        return 0;
    }

    double rho = 1, theta = CV_PI / 180;
    cv::Mat canny, dst1, dst2;
    cv::GaussianBlur(raw_image, canny, cv::Size(5, 5), 2, 2);
    cv::Canny(canny, canny, 100, 150, 3);

    std::vector<cv::Vec2f> lines1, lines2;
    houghLines(canny, lines1, rho, theta, 50);
    HoughLines(canny, lines2, rho, theta, 50);
    draw_houghLines(canny, dst1, lines1, 10);
    draw_houghLines(canny, dst2, lines2, 10);
    

    cv::imshow("raw", raw_image);
    cv::imshow("my hough", dst1);
    cv::imshow("opencv hough", dst2);
    cv::waitKey(0);
    return 0;
}

void hough_coord(cv::Mat image, cv::Mat &acc_mat, double rho, double theta)
{
    int acc_h = (image.rows + image.cols) * 2 / rho;
    int acc_w = CV_PI / theta;
    acc_mat = cv::Mat(acc_h, acc_w, CV_32S, cv::Scalar(0));

    for (int y = 0; y < image.rows; y++)
    {
        for (int x = 0; x < image.cols; x++)
        {
            cv::Point pt(x, y);
            if (image.at<uchar>(pt) > 0)
            {
                for (int i = 0; i < acc_w; i++)
                {
                    double radian = i * theta;
                    double r = pt.x * cos(radian) + pt.y * sin(radian);
                    r = cvRound(r / rho + acc_mat.rows / 2);
                    acc_mat.at<int>(r, i)++;
                }
            }
        }
    }
}

void acc_mask(cv::Mat acc_mat, cv::Mat &acc_dst, cv::Size size, int thresh)
{
    acc_dst = cv::Mat(acc_mat.size(), CV_32S, cv::Scalar(0));
    cv::Point h_m = size / 2;

    for (int r = h_m.y; r < acc_mat.rows - h_m.y; r++)
    {
        for (int t = h_m.x; t < acc_mat.cols - h_m.x; t++)
        {
            cv::Point center(t, r);
            int c_value = acc_mat.at<int>(center);
            if (c_value >= thresh)
            {
                double max = 0;
                for (int u = 0; u < size.height; u++)
                {
                    for (int v = 0; v < size.width; v++)
                    {
                        cv::Point start = center + cv::Point(v, u) - h_m;
                        if (start != center && acc_mat.at<int>(start) > max)
                        {
                            max = acc_mat.at<int>(start);
                        }
                    }
                }

                cv::Rect rect(center - h_m, size);
                if (c_value >= max)
                {
                    acc_dst.at<int>(center) = c_value;
                    acc_mat(rect).setTo(0);
                }
            }
        }
    }
}

void thres_lines(cv::Mat acc_dst, cv::Mat &lines, double _rho, double theta, int thresh)
{
    for (int r = 0; r < acc_dst.rows; r++)
    {
        for (int t = 0; t < acc_dst.cols; t++)
        {
            float value = (float)acc_dst.at<int>(r, t);
            if (value >= thresh)
            {
                float rho = (float)((r - acc_dst.rows / 2) * _rho);
                float radian = (float)(t * theta);

                cv::Matx13f line(rho, radian, value);
                lines.push_back((cv::Mat)line);
            }
        }
    }
}

void sort_lines(cv::Mat lines, std::vector<cv::Vec2f> &s_line)
{
    cv::Mat acc = lines.col(2), idx;
    sortIdx(acc, idx, cv::SORT_EVERY_COLUMN + cv::SORT_DESCENDING);

    for (int i = 0; i < idx.rows; i++)
    {
        int id = idx.at<int>(i);
        float rho = lines.at<float>(id, 0);
        float radian = lines.at<float>(id, 1);
        s_line.push_back(cv::Vec2f(rho, radian));
    }
}

void houghLines(cv::Mat src, std::vector<cv::Vec2f> &s_lines, double rho, double theta, int thresh)
{
    cv::Mat acc_mat, acc_dat, lines;
    hough_coord(src, acc_mat, rho, theta);
    acc_mask(acc_mat, acc_dat, cv::Size(3, 7), thresh);
    thres_lines(acc_dat, lines, rho, theta, thresh);
    sort_lines(lines, s_lines);
}

void draw_houghLines(cv::Mat src, cv::Mat &dst, std::vector<cv::Vec2f> lines, int nline)
{
    cvtColor(src, dst, cv::COLOR_GRAY2BGR);
    for (int i = 0; i < std::min((int)lines.size(), nline); i++)
    {
        float rho = lines[i][0], theta = lines[i][1];
        double a = cos(theta), b = sin(theta);
        cv::Point2d pt(a * rho, b * rho);
        cv::Point2d delta(1000 * -b, 1000 * a);
        line(dst,pt+delta,pt-delta,cv::Scalar(0,255,0),1,cv::LINE_AA);
    }
}
