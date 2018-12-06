#pragma once
#pragma once
#include <opencv2/core/mat.hpp>
#include "LedPair.h"


#define LEDS_IN_A_PAIR 3

class RecognizerLogic
{
public:

	cv::Mat debugPairImg;
	cv::Mat clearImg;

	std::vector<LedPair> blobPairsPreviousFrame;

	std::vector<LedPair> posibleLeds;



	void init(cv::Mat img);
	void visualizeBlobPairs(LedPair leds);
	void MoveLeftRecognizer(std::vector<LedPair> ledsCurrentFrame);
	bool ProximityChecker(LedPair ledpair1, LedPair ledpair2, int distance = 50);
	//void drawPoints(std::)

};
