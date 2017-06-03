#include "Ones.h"

Ones & ones()
{
    static Ones oneObj;
    return oneObj;
}

Ones::Ones()
{
	// "d:\\_share\\_read\\wallpapers\\download 017.jpg";
	// "d:\\downloads\\__rt\\video\\cyprus.mov";
	
	string imgfileName = "c:\\Users\\marle\\Downloads\\pic.jpg"; 
	string videoFileName = "e:\\_video\\cyprus.mov"; 

    AVAR(imgfileName);
    AVAR(videoFileName);

    m_inpImage = cv::imread(imgfileName);
    cv::resize(m_inpImage, m_inpImage, cv::Size(400, 300));   

    AMSG("image " + imgfileName + " succsesfull open");

    m_inpVideo = cv::VideoCapture(videoFileName);           // open the video file for reading
    if (!m_inpVideo.isOpened())
        error("!m_inpVideo.isOpened()");
    
    AMSG("video " + videoFileName + " succsesfull open");
}
