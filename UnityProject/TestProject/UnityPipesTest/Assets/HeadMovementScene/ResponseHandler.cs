using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ResponseHandler : MonoBehaviour {

    // Use this for initialization
    LedBar ledPositions;



    public LedBar ledBar;
    public Camera camera;

    float cameraMaxX = 0.5f;
    float cameraMinX = -0.5f;
    float cameraMaxY = 0.5f;
    float cameraMinY = -0.5f;

    float dataMaxX = 640;
    float dataMaxY = 480;

    public DistanceHandler distanceHandler;
    public HeadRotationHandler headRotationHandler;

    private float movementSpeed = 0;


    // camera x = (((324 - 316)/640) * data) + 316;
    // camera y = (((244 - 236)/480) * data) + 236;

    Vector3 calculateCameraPosition(float x, float y, LedBar bar)
    {
        x = dataMaxX - x;

        float cameraX = (((cameraMaxX - cameraMinX) / dataMaxX) * x) + cameraMinX;
        float cameraY = (((cameraMaxY - cameraMinY) / dataMaxY) * y) + cameraMinY;


        float cameraDistance = distanceHandler.calculateDistance(bar);
        headRotationHandler.calculateHeadRotation(bar);
        Vector3 cameraPos = new Vector3(cameraX, cameraY, cameraDistance);

        float mainCameraX = camera.transform.localPosition.x;
        float mainCameraY = camera.transform.localPosition.y;

        float maxJumpThreshold = 0.1f;




        // keep speed in check and check if it does not jump to much. 
        // without speed you lose the camera tracking

        if (cameraPos.x < mainCameraX + maxJumpThreshold && cameraPos.x > mainCameraX - maxJumpThreshold)
        {
            if (cameraPos.y < mainCameraY + maxJumpThreshold && cameraPos.y > mainCameraY - maxJumpThreshold)
            {
               // Debug.Log(cameraPos);
                return cameraPos;
            }
        }

      //  return cameraPos;

        return camera.transform.localPosition;
    }

	void Start () {
        PipeClient.onResponse += PipeClient_onResponse;
	    Cursor.visible = false;
    }

    private void PipeClient_onResponse(string response)
    {
        ledBar = JsonUtility.FromJson<LedBar>(response);
    }


    public void setLedBar(LedBar bar)
    {
        ledBar = bar;

        
         //@todo calculate position based on all three leds not just the first one.
        
    }

    // Update is called once per framevect
    void Update () {
        if (ledBar.Leds.Count > 0)
        {
          

            Vector3 lerp = Vector3.Lerp(camera.transform.localPosition, calculateCameraPosition(ledBar.Leds[1].X, 480 - ledBar.Leds[1].Y, ledBar), 1);

            camera.transform.localPosition = lerp;





            //Camera.main.transform.position = calculateCameraPosition(ledBar.Leds[1].X, 480 - ledBar.Leds[1].Y);
        }
    }



}

[Serializable]
public class LedBar
{
    public List<Led> Leds;
}
[Serializable]
public class Led
{
    public int X;
    public int Y;
}
