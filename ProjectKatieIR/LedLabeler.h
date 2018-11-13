#pragma once
#include "avansvisionlib.h"

class LedClass
{
public:
	cv::Point2d centerPixel;
};


class LedLabeler
{
public:
	
	static std::vector<LedClass> LEDList;
	static cv::Point LeftLed;
	static cv::Point MiddleLed;
	static cv::Point RightLed;


	static void getLeds(cv::Mat & img);

private:
	static void lableLeds(cv::Mat & img);
};

