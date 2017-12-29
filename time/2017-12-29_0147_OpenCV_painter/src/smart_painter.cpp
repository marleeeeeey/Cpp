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
    enum MouseEventFlagsADV
    {
        EVENT_FLAG_WHEELFORWARD = 0x20000,
    };

    using namespace std;
    using namespace cv;

    cv::Point p(x, y);

    if(event == EVENT_LBUTTONDOWN)
    {
         _poliline.push_back(p);
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
    std::vector<cv::Point> pl = _poliline;

    for (cv::Point & p : pl)
    {
        p.x *= _scale;
        p.y *= _scale;
        cv::circle(canvas, p, 10, _line_color, _thickness);
    }

    std::vector<std::vector<cv::Point>> polilines;
    polilines.push_back(pl);
    bool is_closed = true;
    cv::polylines(canvas, polilines, is_closed, _line_color, _thickness);
}

void SmartPainter::on_wheel(bool is_forward)
{
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
    if(_scale > 100) _scale = 100;

}
