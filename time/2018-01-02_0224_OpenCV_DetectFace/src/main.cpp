#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>
using namespace std;
using namespace cv;

CascadeClassifier face_cascade;
String window_name = "Face Detection";

/**
 * Detects faces and draws an ellipse around them
 */
void detectFaces(Mat frame) {

  std::vector<Rect> faces;
  Mat frame_gray;
  cvtColor(frame, frame_gray, COLOR_BGR2GRAY);  // Convert to gray scale
  equalizeHist(frame_gray, frame_gray);   	// Equalize histogram

  // Detect faces
  face_cascade.detectMultiScale(frame_gray, faces, 1.1, 3,
                0|CASCADE_SCALE_IMAGE, Size(30, 30));

  // Iterate over all of the faces
  for( size_t i = 0; i < faces.size(); i++ ) {

    // Find center of faces
    Point center(faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2);

    // Draw ellipse around face
    ellipse(frame, center, Size(faces[i].width/2, faces[i].height/2),
        0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );
  }


  cv::namedWindow("Eye Tracker", cv::WINDOW_NORMAL);
  cv::resizeWindow("Eye Tracker", frame.cols, frame.rows);
      cv::setWindowProperty("Eye Tracker",CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);//set fullscreen property
  cv::imshow( "Eye Tracker", frame );


 // //cv::namedWindow(window_name);
 // //imshow(window_name, frame);  // Display frame
 // namedWindow( window_name, WINDOW_NORMAL | WINDOW_FULLSCREEN );
 // //setWindowProperty(window_name,CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);
 // imshow( window_name, frame );

}

int main() {

  VideoCapture cap(0);        // Open default camera
  Mat frame;

  // Load preconstructed classifier
  face_cascade.load("/home/marleeeeeey/my_dev/rtsoft/smr-ar/ar_main/classifiers/haarcascade_frontalface_default.xml");

  while(cap.read(frame)) {
    detectFaces(frame);       // Call function to detect faces
    if( waitKey(30) >= 0)     // Pause key
        break;
  }
  return 0;
}
