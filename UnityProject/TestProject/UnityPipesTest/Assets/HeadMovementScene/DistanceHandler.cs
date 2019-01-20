using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class DistanceHandler : MonoBehaviour {

	// Use this for initialization
    private float avgDistanceLastFrame = 0;
    private float ledBarSize = 29.7f;
    private float focalLenght = 531;

    private float closesedRealDistance = 20;
    private float furthestRealDistance = 180;

    private float closesedCameraDistance = 0.5f;
    private float furthesCameraDistance = -0.5f;

    public Text debugText;



    public float calculateDistance(LedBar bar)
    {
        float distanceOneToTwo = calculateDistanceBetweenLeds(bar.Leds[0], bar.Leds[1]);
        float distanceTwoToThree = calculateDistanceBetweenLeds(bar.Leds[1], bar.Leds[2]);

       // Debug.Log("Distance 1 = " + distanceOneToTwo);
       // Debug.Log("Distance tWo to Three is: " + distanceTwoToThree);
          
        float distance = (ledBarSize * focalLenght) / (distanceOneToTwo + distanceTwoToThree);

        //Debug.Log("distance from camera to head is: " +  distance + "CM");
        
       // debugText.text = "Distance to head is: " + distance.ToString("0.##") + "cm";


        return toCameraDistance(distance);
    }

    float toCameraDistance(float distance)
    {
        float normalisedDistance = distance - 20;
        float percentage = normalisedDistance / (furthestRealDistance - 20);

        float cameraDistance = closesedCameraDistance - percentage;


        return cameraDistance;
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
