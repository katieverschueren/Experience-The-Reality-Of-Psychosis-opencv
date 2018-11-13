#pragma once
#include "opencv2/opencv.hpp"
#include <iostream>
#include <string>
 class Main
{
 public:
	Main();
	~Main();
	void runCam();
	 void getLeds(cv::Mat&img);
	 void labelBlobs(cv::Mat img);
 };