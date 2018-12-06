#pragma once
#include "avansvisionlib.h"
#include <vector>
#include "LedPair.h"

//class LedClass
//{
//public:
//	cv::Point2d centerPixel;
//};

class BlobInfo
{
public:
	std::vector<cv::Point> contour; // eigen contour punten lijst
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

	//std::vector<LedClass> LEDList;
	std::vector<BlobInfo> blobList;   //lijst met blobs 
	std::vector<LedPair> ledPairs;
	//std::vector<std::vector<BlobInfo>> possibleLeds;

	//cv::Point LeftLed;
	//cv::Point MiddleLed;
	//cv::Point RightLed;

	//bool ledsFound = false;


	std::vector<LedPair> getLeds(cv::Mat & img);

private:
	std::vector<LedPair> lableBlobs(cv::Mat & img);
	cv::Point CenterOffMass(std::vector<cv::Point> contour);
	std::vector<LedPair> checkColinear(cv::Mat & img);
	std::vector<LedPair> removeDuplicates();
	float calculateDistance(cv::Point point1, cv::Point point2);
	bool calculateDistance(cv::Point point1, cv::Point point2, cv::Point point3);
	void blobAreaFilter();
	void drawBoxes(cv::Rect rect, cv::Mat& img);
	void drawCircles(cv::Point middle, cv::Mat& img);
};

