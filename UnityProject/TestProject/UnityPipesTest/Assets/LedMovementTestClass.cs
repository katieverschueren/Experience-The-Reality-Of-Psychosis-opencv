using System.Collections;
using System.Collections.Generic;
using UnityEngine;



public class LedMovementTestClass : MonoBehaviour {

    public ResponseHandler responseHandler;
    int minX = 0;
    int maxX = 640;
    int minY = 0;
    int maxY = 480;
    int speed = 10;

    int distanceBetween = 10;

    LedBar ledBar = new LedBar();
    Led led1 = new Led();
    Led led2 = new Led();
    Led led3 = new Led();

    // Use this for initialization
    void Start () {
        ledBar.Leds = new List<Led>();

        led1.X = distanceBetween * 2 + minX;
        led1.Y = minY;
        led2.X = distanceBetween + minX;
        led2.Y = minY;
        led3.X = minX;
        led3.Y = minY;

        
    }
	
	// Update is called once per frame
	void Update () {
        
		if(Input.GetKey("w"))
        {
            led1.Y -= speed;
            led2.Y -= speed;
            led3.Y -= speed;
        }
        if (Input.GetKey("a"))
        {
            led1.X -= speed;
            led2.X -= speed;
            led3.X -= speed;
        }
        if (Input.GetKey("s"))
        {
            led1.Y += speed;
            led2.Y += speed;
            led3.Y += speed;
        }
        if (Input.GetKey("d"))
        {
            led1.X += speed;
            led2.X += speed;
            led3.X += speed;
        }
        ledBar.Leds.Add(led1);
        ledBar.Leds.Add(led2);
        ledBar.Leds.Add(led3);

        responseHandler.setLedBar(ledBar);
        ledBar.Leds.Clear();
    }
}
