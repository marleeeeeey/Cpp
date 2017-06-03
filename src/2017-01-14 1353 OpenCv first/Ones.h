#pragma once

class Ones
{
public:
    cv::Mat & inpImage() { return m_inpImage; }
    cv::VideoCapture & videoCapture() { return m_inpVideo; }

private:
    friend Ones & ones();

    Ones();
    ~Ones() {}
    Ones(const Ones & other) = delete;
    void operator=(const Ones & other) = delete;

    cv::Mat m_inpImage;
    cv::VideoCapture m_inpVideo;
};

Ones & ones();
