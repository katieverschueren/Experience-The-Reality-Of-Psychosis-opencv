#include "LedLabeler.h"
#include <opencv2/shape/hist_cost.hpp>
#include <valarray>
#include "LedPairTestFill.h"

std::vector<LedPair> LedLabeler::getLeds(cv::Mat &img)
{
	blobList.clear();
	ledPairs.clear();
	/*img.convertTo(img, CV_16S);
	cv::Mat blobs = cv::Mat::zeros(img.rows, img.cols, img.type());
	std::vector<cv::Point2d *> firstpixelVec2;
	std::vector<cv::Point2d *> posVec2;
	std::vector<int> areaVec2;

	std::vector<std::vector<cv::Point>> contourVec;
	if (img.data == NULL)
		return;
	labelBLOBsInfo(img, blobs, firstpixelVec2, posVec2, areaVec2);
	img.convertTo(img, CV_8U);*/

	return lableBlobs(img);

}

std::vector<LedPair> LedLabeler::lableBlobs(cv::Mat & img)
{
	std::vector<std::vector<cv::Point> > contour; 
	cv::findContours(img, contour, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
	//cv::Mat singleLeds = cv::Mat(img.rows, img.cols, 16, Scalar(255, 255, 255));

	//std::cout << contour.size() << std::endl;	//std::cout is printen wat er binnen de << staat

	for (int i = 0; i < contour.size(); i++)
	{
		cv::Rect rect = boundingRect(contour[i]); // vraag de boundingbox van elke contour op. 

		drawBoxes(rect, img);

		cv::Point blobMiddle = CenterOffMass(contour[i]); // pak het werkelijke midden van de blob.

		

		drawCircles(blobMiddle, img); 

		//BlobInfo blob = ;
		if(blobMiddle.x >= 0 && blobMiddle.y >= 0)
			blobList.push_back(BlobInfo(contour[i], rect, rect.area(), blobMiddle, i));
	}

	return checkColinear(img);
	//cv::imshow("debugCircles", singleLeds);
}

cv::Point LedLabeler::CenterOffMass(std::vector<cv::Point> contour) // berken het midden van de blob
{
	cv::Moments moment = cv::moments(contour, true);
	return cv::Point(moment.m10 / moment.m00, moment.m01 / moment.m00);

}


std::vector<LedPair> LedLabeler::checkColinear(cv::Mat &img)	// colinear is dat punten door de zelfde lijn gaan.
{

	cv::Point point1;
	cv::Point point2;
	cv::Point point3;

	int slopeIndex = 0;

	for (int i = 0; i < blobList.size(); i++)
	{
		for (int ii = 0; ii < blobList.size(); ii++)
		{
			for (int iii = 0; iii < blobList.size(); iii++)
			{
				if (blobList[i].index != blobList[ii].index && blobList[i].index != blobList[iii].index && blobList[iii].index != blobList[ii].index)
				{
					float x1 = blobList[i].center.x;
					float y1 = blobList[i].center.y;
					float x2 = blobList[ii].center.x;
					float y2 = blobList[ii].center.y;
					float x3 = blobList[iii].center.x;
					float y3 = blobList[iii].center.y;


					float slope1 = (y2 - y1) / (x2 - x1);
					float slope2 = (y3 - y2) / (x3 - x2);

					if (slope1 < 0)
						slope1 = slope1 * -1;

					if (slope2 < 0)
						slope2 = slope2 * -1;

					float slopeDifference = slope1 - slope2;

					if (slopeDifference < 0)
						slopeDifference = slopeDifference * -1;


					ledPairs.push_back(LedPair(
						blobList[i].center,
						blobList[ii].center,
						blobList[iii].center,
						slopeDifference,
						calculateDistance(blobList[i].center, blobList[ii].center),
						calculateDistance(blobList[ii].center, blobList[iii].center)));


					//if (slopeDifference > 0 && slopeDifference < 0.5)
					//{
					//	if (calculateDistance(blobList[i].center, blobList[ii].center, blobList[iii].center))
					//	{
					//		// hierzo
					//		ledPairs.push_back(LedPair(
					//			blobList[i].center,
					//			blobList[ii].center,
					//			blobList[iii].center,
					//			slopeDifference,
					//			calculateDistance(blobList[i].center, blobList[ii].center),
					//			calculateDistance(blobList[ii].center, blobList[iii].center)));
					//		//cv::line(img, blobList[i].center, blobList[ii].center, Scalar(255, 255, 255), 2);
					//		//cv::line(img, blobList[ii].center, blobList[iii].center, Scalar(255, 255, 255), 2);
					//	}
					//}


				}
			}
		}
	}


	return removeDuplicates();

}

struct myclass {
	bool operator() (cv::Point pt1, cv::Point pt2) {
		if (pt1.y < pt2.y)
			return true;
		if (pt1.y == pt2.y)
			if (pt1.x < pt2.x)
				return true;
			else
				return false;
		else
			return  false;

	}
} mySort;

bool inList(cv::Point point1, cv::Point point2, cv::Point point3, std::vector<std::vector<cv::Point>>& PointsOnly)
{
	vector<cv::Point> points;
	points.push_back(point1);
	points.push_back(point2);
	points.push_back(point3);

	std::sort(points.begin(), points.end(), mySort);

	if(PointsOnly.size() > 0)
	{
		for( int i = 0; i < PointsOnly.size(); i++)
		{
			if(PointsOnly[i] == points)
			{
				return false;
			}
		}
	}
	return true; 
}



std::vector<LedPair> LedLabeler::removeDuplicates()
{
	if (ledPairs.size() == 0)
		return ledPairs;

	
		vector<LedPair> ledPairsNoduplicates;
		std::vector<std::vector<cv::Point>> PointsOnly;
	if (ledPairs.size() < 1000)
	{
		std::vector<cv::Point> points;
		ledPairsNoduplicates.push_back(ledPairs[0]);
		points.push_back(ledPairs[0].LED1);
		points.push_back(ledPairs[0].LED2);
		points.push_back(ledPairs[0].LED3);
		PointsOnly.push_back(points);
		std::sort(PointsOnly[0].begin(), PointsOnly[0].end(), mySort);

		for (int i = 0; i < ledPairs.size(); i++)
		{
			if (inList(ledPairs[i].LED1, ledPairs[i].LED2, ledPairs[i].LED3, PointsOnly))
			{
				ledPairsNoduplicates.push_back(ledPairs[i]);
				points.clear();
				points.push_back(ledPairs[i].LED1);
				points.push_back(ledPairs[i].LED2);
				points.push_back(ledPairs[i].LED3);
				PointsOnly.push_back(points);
				std::sort(PointsOnly[PointsOnly.size() - 1].begin(), PointsOnly[PointsOnly.size() - 1].end(), mySort);
			}
		}
	}
	return ledPairsNoduplicates;
}




float LedLabeler::calculateDistance(cv::Point point1, cv::Point point2)
{
	return sqrt(((point1.y - point2.y) * (point1.y - point2.y)) + ((point1.x - point2.x)* (point1.x - point2.x)));
}

bool LedLabeler::calculateDistance(cv::Point point1, cv::Point point2, cv::Point point3)
{
	int lenght1_2 = 0;
	int lenght2_3 = 0;

	lenght1_2 = sqrt(((point1.y - point2.y) * (point1.y - point2.y)) + ((point1.x - point2.x)* (point1.x - point2.x)));
	lenght2_3 = sqrt(((point2.y - point3.y) * (point2.y - point3.y)) + ((point2.x - point3.x)* (point2.x - point3.x)));

	//float difference = lenght1_2 - lenght2_3;

	float sum = lenght1_2 + lenght2_3;


	if (lenght1_2 < sum/2 + 300 && lenght1_2 > sum - 300)
		return true;

	return false;
}

//void LedLabeler::blobAreaFilter()
//{
//
//	std::vector<std::vector<BlobInfo>> areaList;
//	for(int i = 0; i < blobList.size(); i++ )
//	{
//		areaList[i][0] = blobList[i];
//	}
//
//	for(int i = 0; i < areaList.size(); i++)
//	{
//		for(int ii = 0; ii < blobList.size(); i++)
//		{
//			if(areaList[i][0].index != blobList[i].index)
//			{
//				
//			}
//		}
//	}
//
//}



void LedLabeler::drawBoxes(cv::Rect rect, cv::Mat & img)
{
	cv::Point pt1, pt2;
	pt1.x = rect.x;
	pt1.y = rect.y;
	pt2.x = rect.x + rect.width;
	pt2.y = rect.y + rect.height;
	// Draws the rect in the original image and show it
	cv::rectangle(img, pt1, pt2, (255, 255, 255), 1);

}

void LedLabeler::drawCircles(cv::Point middle, cv::Mat&img)
{

	cv::circle(img, middle, 4, cv::Scalar(0, 0, 0), -1);
}
