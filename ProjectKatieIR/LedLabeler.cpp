#include "LedLabeler.h"
#include <opencv2/shape/hist_cost.hpp>

void LedLabeler::getLeds(cv::Mat &img)
{
	img.convertTo(img, CV_16S);
	cv::Mat blobs = cv::Mat::zeros(img.rows, img.cols, img.type());
	std::vector<cv::Point2d *> firstpixelVec2;
	std::vector<cv::Point2d *> posVec2;
	std::vector<int> areaVec2;

	std::vector<std::vector<cv::Point>> contourVec;
	if (img.data == NULL)
		return; 
	labelBLOBsInfo(img, blobs, firstpixelVec2, posVec2, areaVec2);
	img.convertTo(img, CV_8U);

	lableLeds(img);
	
}

void LedLabeler::lableLeds(cv::Mat & img)
{
	std::vector<std::vector<cv::Point> > contour;
	cv::findContours(img, contour, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
	cv::Mat singleLeds = cv::Mat(img.rows, img.cols, 16, Scalar(255, 255, 255));

	std::cout << contour.size() << std::endl;

	for (int i = 0; i < contour.size(); i++)
	{
		Rect rect = boundingRect(contour[i]);
		Point pt1, pt2;
		pt1.x = rect.x;
		pt1.y = rect.y;
		pt2.x = rect.x + rect.width;
		pt2.y = rect.y + rect.height;
		
		// Draws the rect in the original image and show it
		rectangle(img, pt1, pt2, (255, 255, 255), 1);

		
		Point ledMiddle;
		ledMiddle.x = pt2.x - (rect.width / 2);
		ledMiddle.y = pt2.y - (rect.height / 2);
		cv::circle(singleLeds, ledMiddle , 4, Scalar(0, 0, 255), -1);
		
	}
	imshow("single leds", singleLeds);

}
