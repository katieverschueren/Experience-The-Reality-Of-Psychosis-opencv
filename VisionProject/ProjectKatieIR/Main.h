#pragma once
#include "opencv2/opencv.hpp"
#include <iostream>
#include <string>
#include <thread>


enum State { RECOGNIZING, TRACKING, LOSTPOINTS };

class Main
{
public:
	State state;
	Main();
	~Main();
	void runCam();
};