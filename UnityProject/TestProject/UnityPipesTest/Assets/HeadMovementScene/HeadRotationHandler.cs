using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class HeadRotationHandler : MonoBehaviour {

	// Use this for initialization

    public Text lookingLeftDebugText;
    public Text lookingRightDebugText;

    public delegate void OnLookingLeft(bool isLooking);
    public static event OnLookingLeft lookingLeft;

    public delegate void OnLookingRight(bool isLooking);
    public static event OnLookingRight lookingRight;

    private bool isLookingLeft = false;
    private bool isLookingRight = false;
    private bool off = false;

    private int index = 0;
    private int totalPercentageRight = 0;



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

        if (index < 10)
        {
            totalPercentageRight += percentageRight;
            index++;
        }
        else
        {
           
            int percentageRAVG = totalPercentageRight / 10;
            int percentageLAVG = 100 - percentageRAVG;
            checkLooking(percentageRAVG, percentageLAVG);
           // Debug.Log(percentageRAVG);
            index = 0;
            totalPercentageRight = 0;
        }

        
    }

    public void checkLooking(int percentageRight, int percentageLeft)
    {
        if (percentageRight > 52 || percentageRight < 48)
        {
            if (!off)
            {
                lookingLeft(true);
                lookingRight(true);
                off = true;
            }
        }
        else
        {
            if (off)
            {
                lookingLeft(false);
                lookingRight(false);
                off = false;
            }
        }








        //if (isLookingLeft)
        //{
        //    if (percentageLeft > 53)
        //        return;
        //    else
        //    {
        //        lookingLeft(false);
        //        isLookingLeft = false;
        //    }
        //}
        //else if (isLookingRight)
        //{
        //    if(percentageRight > 53)
        //        return;
        //    else
        //    {
        //        lookingRight(false);
        //        isLookingRight = false;
        //    }
        //}

        //if (percentageRight > 53)
        //{
        //    lookingRight(true);
        //    isLookingRight = true;
        //}
        //else if (percentageLeft > 53)
        //{
        //    lookingLeft(true);
        //    isLookingLeft = true;
        //}
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
