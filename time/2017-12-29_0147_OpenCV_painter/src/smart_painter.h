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
    template<typename T>
    cv::Point_<T> scaling_point(const cv::Point_<T> &p, float scale);

    std::string _win_name;
    std::vector<std::vector<cv::Point2f>> _polilines;
    cv::Scalar _line_color = cv::Scalar(255, 255, 0);
    float _scale = 1;
    int _thickness = 4;
    cv::Point _move_position;
    cv::Point _wheel_position;
};
