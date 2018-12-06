#include "RecognizerLogic.h"
#include <opencv2/shape/hist_cost.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include "LedMovementTest.h"

void RecognizerLogic::init(cv::Mat img)
{
	debugPairImg = cv::Mat(img.rows, img.cols, 16);
	clearImg = cv::Mat::zeros(img.rows, img.cols, 16);
}

void RecognizerLogic::visualizeBlobPairs(LedPair leds)
{
	

	cv::circle(debugPairImg, leds.LED1, 3, cv::Scalar(255, 0, 255, 0));
	cv::circle(debugPairImg, leds.LED2, 3, cv::Scalar(255, 0, 255, 0));
	cv::circle(debugPairImg, leds.LED3, 3, cv::Scalar(255, 0, 255, 0));
	
	cv::imshow("ledPairs", debugPairImg);
	cvWaitKey(1);
	cv::imshow("ledPairs", clearImg);
	cvWaitKey(1);

}



// move left recognizerlogic 

void RecognizerLogic::MoveLeftRecognizer(std::vector<LedPair> ledsCurrentFrame)
{
	/*if (blobPairsPreviousFrame.size() == 0)
	{
		blobPairsPreviousFrame = ledsCurrentFrame;
		return; 
	}*/


	for(int currentFrameLeds = 0; currentFrameLeds < ledsCurrentFrame.size(); currentFrameLeds++)
	{
		for(int lastFrameLeds = 0; lastFrameLeds < blobPairsPreviousFrame.size(); lastFrameLeds++)
		{

			LedPair led1 = blobPairsPreviousFrame[lastFrameLeds];
			LedPair led2 = ledsCurrentFrame[currentFrameLeds];
			if (blobPairsPreviousFrame[lastFrameLeds].LED1 == ledsCurrentFrame[currentFrameLeds].LED1 &&
				blobPairsPreviousFrame[lastFrameLeds].LED2 == ledsCurrentFrame[currentFrameLeds].LED2 &&
				blobPairsPreviousFrame[lastFrameLeds].LED3 == ledsCurrentFrame[currentFrameLeds].LED3)
			{
			}
			else {
			
				if (ProximityChecker(blobPairsPreviousFrame[lastFrameLeds], ledsCurrentFrame[currentFrameLeds], 10))
				{
					std::cout << "Pair inside proximity" << std::endl;

				}
				else
				{
					std::cout << "Pair not inside proximity" << std::endl;
				}
			}
		}
	}
	blobPairsPreviousFrame = ledsCurrentFrame;
	std::cout << blobPairsPreviousFrame.size() << std::endl;
}

bool RecognizerLogic::ProximityChecker(LedPair ledpair1, LedPair ledpair2, int distance)
{
	bool isInProximity = false;
	//for(int i = 0; i < LEDS_IN_A_PAIR; i++)
	//{
	//	//if(ledpair1.)
	//}


	


	if (ledpair2.LED1.x > (ledpair1.LED1.x - distance) && ledpair2.LED1.x < (ledpair1.LED1.x + distance))
	{
		if (ledpair2.LED1.y > (ledpair1.LED1.y - distance) && ledpair2.LED1.y < (ledpair1.LED1.y + distance))
		{
			isInProximity = true;
		}
		else
			return false;
	}
	else
		return false;
	if (ledpair2.LED2.x > (ledpair1.LED2.x - distance) && ledpair2.LED2.x < (ledpair1.LED2.x + distance))
	{
		if (ledpair2.LED2.y > (ledpair1.LED2.y - distance) && ledpair2.LED2.y < (ledpair1.LED2.y + distance))
		{
			isInProximity = true;
		}
		else
			return false;
	}
	else
		return false;
	if (ledpair2.LED3.x > (ledpair1.LED3.x - distance) && ledpair2.LED3.x < (ledpair1.LED3.x + distance))
	{
		if (ledpair2.LED3.y > (ledpair1.LED3.y - distance) && ledpair2.LED3.y < (ledpair1.LED3.y + distance))
		{
			isInProximity = true;
		}
		else
			return false;
	}
	else
		return false;


	return isInProximity;
}
