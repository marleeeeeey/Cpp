#include "smart_painter.h"

SmartPainter::SmartPainter(std::string win_name)
    : _win_name(win_name)
{
    cv::namedWindow(_win_name);
    cv::setMouseCallback(_win_name, on_mouse, this);

    show_loop();
}

void SmartPainter::show_loop()
{
    cv::VideoCapture cap;
    if(!cap.open(0))
        return;

    for(;;)
    {
        cv::Mat frame;
        cap >> frame;

        if( frame.empty() )
            break;

        draw(frame);

        cv::imshow(_win_name, frame);

        if( cv::waitKey(10) == 27 )
            break;
    }
}

void SmartPainter::on_mouse(int event, int x, int y, int flags, void *userdata)
{
    SmartPainter & sp = *(SmartPainter *)userdata;
    sp.on_mouse(event, x, y, flags);
}

void SmartPainter::on_mouse(int event, int x, int y, int flags)
{
    using namespace std;
    using namespace cv;

    cv::Point p(x, y);

    if  ( event == EVENT_LBUTTONDOWN )
    {
         _poliline.push_back(p);
    }

    if ( event == EVENT_MOUSEMOVE )
    {
         // cout << "Mouse move over the window - position (" << x << ", " << y << ")" << endl;
    }
    else
    {
        std::cout
                << "event = " << event << "; "
                << "flags = " << flags << "; "
                << std::endl;
    }
}

void SmartPainter::draw(cv::Mat canvas)
{
    for (cv::Point & p : _poliline)
    {
        cv::circle(canvas, p, 10, _line_color);
    }

    std::vector<std::vector<cv::Point>> polilines;
    polilines.push_back(_poliline);
    bool is_closed = true;
    cv::polylines(canvas, polilines, is_closed, _line_color);
}
