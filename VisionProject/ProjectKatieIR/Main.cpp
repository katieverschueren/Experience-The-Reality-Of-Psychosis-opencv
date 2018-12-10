#include "Main.h"
#include "LedLabeler.h"
#include "RecognizerLogic.h"
#include "LedMovementTest.h"
#include "PipeCommunication.h"

double PCFreq = 0.0;
__int64 CounterStart = 0;

void StartCounter()
{
	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li))
		cout << "QueryPerformanceFrequency failed!\n";

	PCFreq = double(li.QuadPart) / 1000.0;

	QueryPerformanceCounter(&li);
	CounterStart = li.QuadPart;
}

double GetCounter()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	return double(li.QuadPart - CounterStart) / PCFreq;
}
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
	cv::VideoCapture cap(1); // open the default camera

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
		StartCounter();
		//cap >> frame; // get a new frame from camera
		if (!cap.VideoCapture::read(frame))
			return;

		cv::imshow("Feed", frame);
		cvtColor(frame, grayFrame, CV_BGR2GRAY);

		// gray image per pixel van 0 tot 255
		// 0 is zwart 
		// 255 is maximaal dus wit. 


		threshold(grayFrame, thresholdImage, 125, 1, 0);  // alles boven de 250 als pixel waarde maak je een 1 van.

		if (state == RECOGNIZING)
		{


			//LedPair Testleds = LedMovementTest::updateLeds();
			//recognizer.visualizeBlobPairs(Testleds);
			
			

			std::vector<LedPair> ledList = ledLabeler.getLeds(thresholdImage);


			if(ledList.size() > 0)
				pipeCom.sendViaPipe(ledList[0]);

				//recognizer.MoveLeftRecognizer(ledLabeler.getLeds(thresholdImage));
				//getLeds(thresholdImage);
			
		}
	


		cv::imshow("threshold", thresholdImage * 255);

		std::cout << "fps is: " << 1 / (GetCounter() / 1000) << std::endl;
		if (cv::waitKey(1) >= 0) break;
	}
	// the camera will be deinitialized automatically in VideoCapture destructor
	return;
}



