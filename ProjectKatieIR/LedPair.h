#pragma once
#include <opencv2/core/mat.hpp>


class LedPair
{
public:
	cv::Point LED1; //This is the center of mass of the contour of the blob
	cv::Point LED2; //This is the center of mass of the contour of the blob
	cv::Point LED3; //This is the center of mass of the contour of the blob

	float colinearOffset; //the offset from a perfect line trough the points

	float distanceLED1_LED2;
	float distanceLED2_LED3;

	int foundIndex; // amount of times found without skipping a frame


	LedPair(cv::Point _LED1, cv::Point _LED2, cv::Point _LED3, float _colinearOffset, float _distanceLED1_LED2, float _distanceLED2_LED3)
	{
		LED1 = _LED1;
		LED2 = _LED2;
		LED3 = _LED3;
		colinearOffset = _colinearOffset;
		distanceLED1_LED2 = _distanceLED1_LED2;
		distanceLED2_LED3 = _distanceLED2_LED3;

	}


};
