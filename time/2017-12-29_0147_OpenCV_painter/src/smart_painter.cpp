#include "smart_painter.h"
#include <sstream>

SmartPainter::SmartPainter(std::string win_name)
    : _win_name(win_name)
{
    _polilines.resize(2);
    std::vector<cv::Point2f> points
    {
        cv::Point2f(10.02, 10.04),
        cv::Point2f(10.06, 10.04),
        cv::Point2f(10.09, 10.04),
    };

    auto & v = _polilines.at(1);
    v.insert(v.end(), points.begin(), points.end());

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

    enum MouseEventFlagsADV
    {
        EVENT_FLAG_WHEELFORWARD = 0x20000,
    };

    cv::Point p(x, y);

    if(event == EVENT_LBUTTONDOWN)
    {
        p = scaling_point(p, 1/_scale);
         _polilines[0].push_back(p);
    }

    if(event == EVENT_MOUSEWHEEL)
    {
        if(flags & EVENT_FLAG_WHEELFORWARD)
        {
            on_wheel(true);
        }
        else
        {
            on_wheel(false);
        }
    }

    if ( event == EVENT_MOUSEMOVE )
    {
         // cout << "Mouse move over the window - position (" << x << ", " << y << ")" << endl;
        _move_position = p;
    }
    else
    {
        std::cout
                << "event = " << event << "; "
                << "flags = " << std::hex << flags << std::dec << "; "
                //<< "EVENT_FLAG_LBUTTON = "  << (bool)( flags & EVENT_FLAG_LBUTTON  ) << "; "
                //<< "EVENT_FLAG_RBUTTON = "  << (bool)( flags & EVENT_FLAG_RBUTTON  ) << "; "
                //<< "EVENT_FLAG_MBUTTON = "  << (bool)( flags & EVENT_FLAG_MBUTTON  ) << "; "
                //<< "EVENT_FLAG_CTRLKEY = "  << (bool)( flags & EVENT_FLAG_CTRLKEY  ) << "; "
                //<< "EVENT_FLAG_SHIFTKEY = " << (bool)( flags & EVENT_FLAG_SHIFTKEY ) << "; "
                //<< "EVENT_FLAG_ALTKEY = "   << (bool)( flags & EVENT_FLAG_ALTKEY   ) << "; "
                //<< "EVENT_FLAG_WHEELFORWARD = "   << (bool)( flags & EVENT_FLAG_WHEELFORWARD   ) << "; "
                << std::endl;
    }
}


void SmartPainter::draw(cv::Mat canvas)
{
    std::vector<std::vector<cv::Point>> pls;

    for(const auto & pl : _polilines)
    {
        pls.push_back(std::vector<cv::Point>());
        auto & new_pl = pls.back();
        for (const auto & p : pl)
        {
            new_pl.emplace_back(scaling_point(p, _scale));
            cv::circle(canvas, new_pl.back(), 10, _line_color, _thickness);
        }
    }

    bool is_closed = true;
    cv::polylines(canvas, pls, is_closed, _line_color, _thickness);

    std::stringstream ss;
    ss << "scale = " << _scale;
    cv::putText(canvas, ss.str(), cv::Point(30, 30), 1, 2, _line_color, _thickness);
}

void SmartPainter::on_wheel(bool is_forward)
{
    _wheel_position = _move_position;

    float scale_step = 1.1;
    if(is_forward)
    {
        _scale *= scale_step;
    }
    else
    {
        _scale /= scale_step;
    }

    if(_scale < 0.001) _scale = 0.001;
    if(_scale > 10000) _scale = 10000;
}

template<typename T>
cv::Point_<T> SmartPainter::scaling_point(const cv::Point_<T> &p, float scale)
{
    cv::Point_<T> center = _wheel_position;
    cv::Point_<T> normal = p - center;
    normal *= scale;
    cv::Point_<T> ret = center + normal;

    std::cout
            << "SmartPainter::scaling_point: "
            << "p=" << p << "; "
            << "scale=" << scale << "; "
            << "center=" << center << "; "
            << "normal=" << p << "; "
            << "ret=" << ret << "; "
            << std::endl;

    return ret;
}
