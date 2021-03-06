#include "LedMovementTest.h"
#include <iostream>
#include <windows.h>
#include <conio.h>

LedPair LedMovementTest::mainLedPair = LedPair(cv::Point(minX, minY), cv::Point(minX, minY), cv::Point(minX, minY), 0, minX, minX);
int LedMovementTest::skipIndex = 0;
bool LedMovementTest::goingRight = true;
bool LedMovementTest::goingUp = false;

LedPair LedMovementTest::updateLeds()
{
	bool hasToMove = false;
	//std::cout << "Led1 x is: " << mainLedPair.LED1.x << " Led1 y is: " << mainLedPair.LED1.y << std::endl;
	if(skipIndex > movementDelay)
	{
		skipIndex = 0;

		//moveLeds(0, 1, mainLedPair);

		if (goingUp)
		{
			if (mainLedPair.LED1.y <= minY)
			{
				goingUp = false;
				hasToMove = true;
			}
			else
			{
				moveLeds(0, -1, mainLedPair);
			}
		}
		else
		{
			if (mainLedPair.LED1.y >= maxY)
			{
				goingUp = true;
				hasToMove = true;
			}
			else
			{
				moveLeds(0, 1, mainLedPair);
			}
		}
		if (hasToMove)
		{

			if (goingRight)
			{
				if (mainLedPair.LED1.x >= maxX)
				{
					goingRight = false;
				}
				else
				{
					moveLeds(1, 0, mainLedPair);
				}
			}
			if(!goingRight)
			{
				if (mainLedPair.LED3.x <= minX)
				{
					goingRight = true;
				}
				else
				{
					moveLeds(-1, 0, mainLedPair);
				}
			}
		}


		return mainLedPair;
	}
	skipIndex++;
}


LedPair LedMovementTest::updateLedsArrows()
{
	
	char key = _getch();
	int asciiValue = key;

	std::cout << "key pressed: " << asciiValue << std::endl;
	if (asciiValue == 97) //a
	{
		mainLedPair.LED1.x -= 1;
		mainLedPair.LED2.x -= 1;
		mainLedPair.LED3.x -= 1;
	}
	if (asciiValue == 115) //s
	{
		mainLedPair.LED1.y += 1;
		mainLedPair.LED2.y += 1;
		mainLedPair.LED3.y += 1;
	}
	if (asciiValue == 100) //d
	{
		mainLedPair.LED1.x += 1;
		mainLedPair.LED2.x += 1;
		mainLedPair.LED3.x += 1;
	}
	if (asciiValue == 119) //w
	{
		mainLedPair.LED1.y -= 1;
		mainLedPair.LED2.y -= 1;
		mainLedPair.LED3.y -= 1;
	}

	return mainLedPair;
}

void LedMovementTest::moveLeds(int x, int y, LedPair & led_pair)
{
	x = x * stepSize;
	y = y * stepSize;
	led_pair.LED1 += cv::Point(x, y);
	led_pair.LED2 += cv::Point(x, y);
	led_pair.LED3 += cv::Point(x, y);
}

void LedMovementTest::init(int distanceBetweenLeds)
{
	mainLedPair = LedPair(cv::Point(minX + distanceBetweenLeds * 2, minY), cv::Point(minX + distanceBetweenLeds, minY), cv::Point(minX, minY), 0, distanceBetweenLeds, distanceBetweenLeds);

}

