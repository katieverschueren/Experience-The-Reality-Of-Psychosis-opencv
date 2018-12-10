using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ResponseHandler : MonoBehaviour {

    // Use this for initialization
    LedBar ledPositions;

    public GameObject led1;
    public GameObject led2;
    public GameObject led3;

    public LedBar ledBar;

    float cameraMaxX = 324;
    float cameraMinX = 316;
    float cameraMaxY = 244;
    float cameraMinY = 236;

    float dataMaxX = 640;
    float dataMaxY = 480;


    // camera x = (((324 - 316)/640) * data) + 316;
    // camera y = (((244 - 236)/480) * data) + 236;

    Vector3 calculateCameraPosition(float x, float y)
    {
        x = dataMaxX - x;

        float cameraX = (((cameraMaxX - cameraMinX) / dataMaxX) * x) + cameraMinX;
        float cameraY = (((cameraMaxY - cameraMinY) / dataMaxY) * y) + cameraMinY;




        Vector3 cameraPos = new Vector3(cameraX, cameraY, 0);
        Debug.Log(cameraPos);
        return cameraPos;
    }

	void Start () {
        PipeClient.onResponse += PipeClient_onResponse;
	}

    private void PipeClient_onResponse(string response)
    {
        ledBar = JsonUtility.FromJson<LedBar>(response);
    }


    public void setLedBar(LedBar bar)
    {
        ledBar = bar;
        led1.transform.position = new Vector3(ledBar.Leds[0].X, 480 - ledBar.Leds[0].Y, 0);
        led2.transform.position = new Vector3(ledBar.Leds[1].X, 480 - ledBar.Leds[1].Y, 0);
        led3.transform.position = new Vector3(ledBar.Leds[2].X, 480 - ledBar.Leds[2].Y, 0);

        Vector3 lerp = Vector3.Lerp(Camera.main.transform.position, calculateCameraPosition(ledBar.Leds[1].X, 480 - ledBar.Leds[1].Y), 0);

        Camera.main.transform.position = lerp;
    }

    // Update is called once per framevect
    void Update () {
        if (ledBar != null)
        {
            led1.transform.position = new Vector3(ledBar.Leds[0].X, 480 - ledBar.Leds[0].Y, 0);
            led2.transform.position = new Vector3(ledBar.Leds[1].X, 480 - ledBar.Leds[1].Y, 0);
            led3.transform.position = new Vector3(ledBar.Leds[2].X, 480 - ledBar.Leds[2].Y, 0);
            Camera.main.transform.position = calculateCameraPosition(ledBar.Leds[1].X, 480 - ledBar.Leds[1].Y);
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
