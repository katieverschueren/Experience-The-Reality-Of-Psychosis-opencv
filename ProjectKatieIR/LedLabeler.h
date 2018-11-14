#pragma once
#include "avansvisionlib.h"

class LedClass
{
public:
	cv::Point2d centerPixel;
};

class BlobInfo
{
public:
	std::vector<cv::Point> contour;
	cv::Rect rect;
	int area;
	cv::Point center;
	int index;

	BlobInfo(std::vector<cv::Point> Contour, cv::Rect Rect, int Area, cv::Point Center, int Index)
	{
		contour = Contour;
		rect = Rect;
		area = Area;
		center = Center;
		index = Index;
	}
};



class LedLabeler
{
public:

	std::vector<LedClass> LEDList;
	std::vector<BlobInfo> blobList;

	std::vector<std::vector<BlobInfo>> possibleLeds;

	cv::Point LeftLed;
	cv::Point MiddleLed;
	cv::Point RightLed;

	bool ledsFound = false;


	void getLeds(cv::Mat & img);

private:
	void lableBlobs(cv::Mat & img);
	void checkColinear(cv::Mat & img);
	bool calculateDistance(cv::Point point1, cv::Point point2, cv::Point point3);
	void blobAreaFilter();
	void drawBoxes(Rect rect, cv::Mat& img);
	void drawCircles(cv::Point middle, cv::Mat& img);
};

