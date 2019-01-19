using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class HeadRotationHandler : MonoBehaviour {

	// Use this for initialization

    public Text lookingLeftDebugText;
    public Text lookingRightDebugText;


    void Start () {
		
	}
	



	// Update is called once per frame
	void Update () {
		
	}


    public void calculateHeadRotation(LedBar ledbar)
    {
        float distanceOneToTwo = calculateDistanceBetweenLeds(ledbar.Leds[0], ledbar.Leds[1]);
        float distanceTwoToThree = calculateDistanceBetweenLeds(ledbar.Leds[1], ledbar.Leds[2]);

        int percentageRight = (int)(distanceOneToTwo / (distanceOneToTwo + distanceTwoToThree) * 100);
        int percentageLeft = 100 - percentageRight;

        


        lookingRightDebugText.text = "looking right = " + percentageRight + "%";
        lookingLeftDebugText.text = "looking left = " + percentageLeft + "%";

    }


    float calculateDistanceBetweenLeds(Led led1, Led led2)
    {
        //Pyht 
        float a;
        float b;
        float c;

        a = led1.Y - led2.Y;
        b = led1.X - led2.X;

        c = Mathf.Sqrt((a * a) + (b * b));

        return c;
    }
}
