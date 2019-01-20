using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Video;

public class TimerVideoPlayerComponent : MonoBehaviour {

    // Use this for initialization
    public int startTime = 0;
    [Header("Set endTime to -1 to never stop")]
    public int endTime = 0;

    void Start () {
        TimerController.secondElapsed += TimerController_secondElapsed;
    }

    // Update is called once per frame
    private void TimerController_secondElapsed(int runTime)
    {
        if (runTime >= startTime)
        {
            GetComponent<VideoPlayer>().Play();
        }

        if (runTime >= endTime && endTime != -1)
        {
            GetComponent<VideoPlayer>().Stop();
        }
    }
}
