using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TimerController : MonoBehaviour {

    // Use this for initialization
    public delegate void OnSecondElapsed(int runTime);
    public static event OnSecondElapsed secondElapsed;

    private int totalTime = 0;
    float deltaTime = 0;

    void Start()
    {
        secondElapsed(totalTime);
    }
	
	// Update is called once per frame
	void Update ()
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
