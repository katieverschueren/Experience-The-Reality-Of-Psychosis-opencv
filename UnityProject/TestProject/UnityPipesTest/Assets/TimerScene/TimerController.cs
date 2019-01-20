using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TimerController : MonoBehaviour {

    // Use this for initialization
    public delegate void OnSecondElapsed(int runTime);
    public static event OnSecondElapsed secondElapsed;

    private static int totalTime = 0;
    float deltaTime = 0;

    public static bool started = false;


    public static void startScene()
    {
        secondElapsed(totalTime);
        started = true;
    }
	
	// Update is called once per frame
	void Update ()
	{
	    if (started)
	    {
	        deltaTime += Time.deltaTime;
	        if (deltaTime >= 1)
	        {
	            deltaTime = 0;
	            totalTime++;
	            secondElapsed(totalTime);
	        }
	    }
	}
}
