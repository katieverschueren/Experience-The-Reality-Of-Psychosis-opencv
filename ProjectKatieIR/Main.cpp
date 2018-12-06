#include "Main.h"
#include "LedLabeler.h"
#include "RecognizerLogic.h"
#include "LedMovementTest.h"
#include "PipeCommunication.h"


Main::Main()
{
	state = RECOGNIZING;
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

	LedLabeler ledLabeler;

	cv::namedWindow("Feed", 1);

	cap >> frame; // get a new frame from camera

	RecognizerLogic recognizer;
	recognizer.init(frame);
	LedMovementTest::init(10);


	PipeCommunication pipeCom = PipeCommunication();

	for (;;)
	{

		//cap >> frame; // get a new frame from camera
		/*if (!cap.VideoCapture::read(frame))
			return;*/

		cv::imshow("Feed", frame);
		cvtColor(frame, grayFrame, CV_BGR2GRAY);

		//imshow("grey", grayFrame);

		// gray image per pixel van 0 tot 255
		// 0 is zwart 
		// 255 is maximaal dus wit. 


		threshold(grayFrame, thresholdImage, 125, 1, 0);  // alles boven de 250 als pixel waarde maak je een 1 van.

		if (state == RECOGNIZING)
		{
			//if ()
			//{
			LedPair Testleds = LedMovementTest::updateLeds();
			recognizer.visualizeBlobPairs(Testleds);
			pipeCom.sendViaPipe(Testleds);
				//recognizer.MoveLeftRecognizer(ledLabeler.getLeds(thresholdImage));
				//getLeds(thresholdImage);
			//}
		}



		cv::imshow("threshold", thresholdImage * 255);


		if (cv::waitKey(1) >= 0) break;
	}
	// the camera will be deinitialized automatically in VideoCapture destructor
	return;
}



