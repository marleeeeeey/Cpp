#pragma once
#include <opencv2/opencv.hpp>

class SmartPainter
{
public:
    SmartPainter(std::string win_name = "default name");

private:
    void show_loop();
    static void on_mouse(int event, int x, int y, int flags, void *userdata);
    void on_mouse(int event, int x, int y, int flags);
    void draw(cv::Mat canvas);

    std::string _win_name;
    std::vector<cv::Point> _poliline;
    cv::Scalar _line_color = cv::Scalar(100, 100, 100);
};
