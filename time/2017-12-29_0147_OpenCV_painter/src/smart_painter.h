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
    void on_wheel(bool is_forward);
    void scaling_point(cv::Point & p, float scale);

    std::string _win_name;
    std::vector<cv::Point> _poliline;
    cv::Scalar _line_color = cv::Scalar(100, 100, 100);
    float _scale = 1;
    int _thickness = 4;
    cv::Point _move_position;
    cv::Point _wheel_position;
};
