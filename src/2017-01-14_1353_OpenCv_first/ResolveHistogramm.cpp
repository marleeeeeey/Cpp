#include "ResolveHistogramm.h"

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;


class HistSaver
{
public:
	HistSaver(const std::string & fileName)
	{
		m_fileName = fileName + m_ext;
	}

	void saveHist(const Mat & hist)
	{
		string s = to_string(hist);
		for (auto & ch : string("[]; "))
			s.erase(std::remove(s.begin(), s.end(), ch), s.end());

		std::ofstream ost;
		ost.open(m_fileName);
		ost << s;
	}

	Mat loadHist()
	{
		std::ifstream ist;
		ist.open(m_fileName);

		Mat m;

		while (!ist.eof())
		{
			int val;
			ist >> val;
			m.push_back(val);
		}

		return m;
	}

private:
	std::string m_ext = ".txt";
	std::string m_fileName;
};




void drawHist(int histSize, Mat &b_hist, Mat &g_hist, Mat &r_hist)
{

	// Draw the histograms for B, G and R
	int hist_w = 512; int hist_h = 400;
	int bin_w = cvRound((double)hist_w / histSize);

	Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));

	/// Normalize the result to [ 0, histImage.rows ]
	normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

	/// Draw for each channel
	for (int i = 1; i < histSize; i++)
	{
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))),
			Point(bin_w*(i), hist_h - cvRound(b_hist.at<float>(i))),
			Scalar(255, 0, 0), 2, 8, 0);
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(g_hist.at<float>(i - 1))),
			Point(bin_w*(i), hist_h - cvRound(g_hist.at<float>(i))),
			Scalar(0, 255, 0), 2, 8, 0);
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(r_hist.at<float>(i - 1))),
			Point(bin_w*(i), hist_h - cvRound(r_hist.at<float>(i))),
			Scalar(0, 0, 255), 2, 8, 0);
	}

	/// Display
	namedWindow("calcHist Demo", CV_WINDOW_AUTOSIZE);
	imshow("calcHist Demo", histImage);
}

int resolveHistogramm()
{
	AFUN;


	Mat src, dst;

	/// Load image
	src = ones().inpImage();

	if (!src.data)
	{
		return -1;
	}

	/// Separate the image in 3 places ( B, G and R )
	vector<Mat> bgr_planes;
	split(src, bgr_planes);

	/// Establish the number of bins
	int histSize = 256;

	/// Set the ranges ( for B,G,R) )
	float range[] = { 0, 256 };
	const float* histRange = { range };

	bool uniform = true; 
	bool accumulate = false;

	Mat b_hist, g_hist, r_hist;

	/// Compute the histograms:
	calcHist(&bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate);
	calcHist(&bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate);
	calcHist(&bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate);


	HistSaver histSaver("test");
	histSaver.saveHist(b_hist);
	Mat m = histSaver.loadHist();


	//drawHist(histSize, b_hist, g_hist, r_hist);



	waitKey(0);

	return 0;
}
