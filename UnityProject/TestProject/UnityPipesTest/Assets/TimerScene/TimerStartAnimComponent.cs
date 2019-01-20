using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TimerStartAnimComponent : MonoBehaviour {

    // Use this for initialization
    public int startTime = 0;
    [Header("Set endTime to -1 to never stop")]
    public int endTime = 0;

    private Animator anim;


	void Start ()
	{
        TimerController.secondElapsed += TimerController_secondElapsed;
	    anim = GetComponent<Animator>();
	    anim.enabled = false;
	}

    private void TimerController_secondElapsed(int runTime)
    {
        if (runTime >= startTime)
        {
            onStartAnim();
        }
        if (runTime >= endTime && endTime != -1)
        {
            onStopAnim();
        }
    }

    void onStartAnim()
    {
        anim.enabled = true;
    }

    void onStopAnim()
    {
        anim.enabled = false;
    }
    
}
