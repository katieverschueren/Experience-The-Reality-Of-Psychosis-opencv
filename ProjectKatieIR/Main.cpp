#include "Main.h"
#include "LedLabeler.h"


Main::Main()
{
}

Main::~Main()
{
}

int main(int, char**)
{
	Main main;
	main.runCam();
	
}

void Main::runCam()
{
	cv::VideoCapture cap(0); // open the default camera

	if (!cap.isOpened())  // check if we succeeded
		return; // exit program


	// Mat is een afbeelding 
	cv::Mat frame;
	cv::Mat grayFrame;
	cv::Mat thresholdImage;


	cv::namedWindow("Feed", 1);
	for (;;)
	{
		
		cap >> frame; // get a new frame from camera
		imshow("Feed", frame);
		//std::cout << frame.type() << std::endl;
		cvtColor(frame, grayFrame, CV_BGR2GRAY);
		imshow("grey", grayFrame);

		// gray image per pixel van 0 tot 255
		// 0 is zwart 
		// 255 is maximaal dus wit. 


		threshold(grayFrame, thresholdImage, 250, 1, 0);  // alles boven de 250 als pixel waarde maak je een 1 van.

		LedLabeler::getLeds(thresholdImage);
		//getLeds(thresholdImage);
		imshow("threshold", thresholdImage*255);
		if (cv::waitKey(1) >= 0) break;
	}
	// the camera will be deinitialized automatically in VideoCapture destructor
	return;
}



