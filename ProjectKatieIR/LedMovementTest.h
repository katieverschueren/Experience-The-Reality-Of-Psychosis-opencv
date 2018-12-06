#pragma once
#include "LedPair.h"

#define maxX 440
#define minX 200
#define maxY 380 
#define minY 100
#define movementDelay 0
#define stepSize 5



class LedMovementTest
{
public:
	static bool goingUp;
	static bool goingRight;
	static LedPair updateLeds();
	static void moveLeds(int x, int y, LedPair& led_pair);
	static void init (int distanceBetweenLeds);
	static LedPair mainLedPair;
	static int leds;
	static int skipIndex;
	

};
