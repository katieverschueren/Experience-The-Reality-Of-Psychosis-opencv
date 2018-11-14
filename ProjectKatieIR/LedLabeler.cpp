#include "LedLabeler.h"
#include <opencv2/shape/hist_cost.hpp>
#include <valarray>

void LedLabeler::getLeds(cv::Mat &img)
{
	blobList.clear();
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

	lableBlobs(img);

}

void LedLabeler::lableBlobs(cv::Mat & img)
{
	std::vector<std::vector<cv::Point> > contour;
	cv::findContours(img, contour, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
	//cv::Mat singleLeds = cv::Mat(img.rows, img.cols, 16, Scalar(255, 255, 255));

	std::cout << contour.size() << std::endl;

	for (int i = 0; i < contour.size(); i++)
	{

		Rect rect = boundingRect(contour[i]);

		drawBoxes(rect, img);

		Point blobMiddle;
		blobMiddle.x = (rect.x + rect.width) - (rect.width / 2);
		blobMiddle.y = (rect.y + rect.height) - (rect.height / 2);

		drawCircles(blobMiddle, img);

		//BlobInfo blob = ;

		blobList.push_back(BlobInfo(contour[i], rect, rect.area(), blobMiddle, i));
	}

	checkColinear(img);
	//cv::imshow("debugCircles", singleLeds);
}




void LedLabeler::checkColinear(cv::Mat &img)
{
	float smallestSlope = 5;

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


					if (slopeDifference > 0 && slopeDifference < 0.025)
					{
						if (calculateDistance(blobList[i].center, blobList[ii].center, blobList[iii].center))
						{

							cv::line(img, blobList[i].center, blobList[ii].center, Scalar(255, 255, 255), 2);
							cv::line(img, blobList[ii].center, blobList[iii].center, Scalar(255, 255, 255), 2);
						}
					}


				}
			}
		}
	}

	std::cout << "slope index" << slopeIndex << std::endl;
	std::cout << "smallest Slope difference =" << smallestSlope << std::endl;
	cv::line(img, point1, point3, Scalar(255, 255, 255), 2);

	std::cout << "----------------------------------------------------------\n\n" << std::endl;
}


bool LedLabeler::calculateDistance(cv::Point point1, cv::Point point2, cv::Point point3)
{
	int lenght1_2 = 0;
	int lenght2_3 = 0;

	lenght1_2 = sqrt(((point1.y - point2.y) * (point1.y - point2.y)) + ((point1.x - point2.x)* (point1.x - point2.x)));
	lenght2_3 = sqrt(((point2.y - point3.y) * (point2.y - point3.y)) + ((point2.x - point3.x)* (point2.x - point3.x)));

	float difference = lenght1_2 - lenght2_3;


	if (difference < difference + 0.1 && difference > difference - 0.1)
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



void LedLabeler::drawBoxes(Rect rect, cv::Mat & img)
{
	Point pt1, pt2;
	pt1.x = rect.x;
	pt1.y = rect.y;
	pt2.x = rect.x + rect.width;
	pt2.y = rect.y + rect.height;
	// Draws the rect in the original image and show it
	cv::rectangle(img, pt1, pt2, (255, 255, 255), 1);

}

void LedLabeler::drawCircles(cv::Point middle, cv::Mat&img)
{

	cv::circle(img, middle, 4, Scalar(0, 0, 255), -1);
}
