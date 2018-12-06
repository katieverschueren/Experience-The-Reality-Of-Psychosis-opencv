#include "LedPairTestFill.h"


std::vector<LedPair> LedPairTestFill::createTestList()
{
	std::vector<LedPair> testLlist;

	testLlist.push_back(LedPair(
		cv::Point(4, 5),
		cv::Point(1, 5),
		cv::Point(9, 5),
		10,
		5,
		5));
	testLlist.push_back(LedPair(
		cv::Point(4, 5),
		cv::Point(1, 5),
		cv::Point(14, 5),
		10,
		5,
		5));
	testLlist.push_back(LedPair(
		cv::Point(4, 5),
		cv::Point(5, 5),
		cv::Point(64, 5),
		10,
		5,
		5));
	testLlist.push_back(LedPair(
		cv::Point(1, 5),
		cv::Point(9, 5),
		cv::Point(4, 5),
		10,
		5,
		5));

	testLlist.push_back(LedPair(
		cv::Point(64, 5),
		cv::Point(5, 5),
		cv::Point(4, 5),
		10,
		5,
		5));

	return testLlist;
}