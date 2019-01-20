using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TimerShowObjectComponent : MonoBehaviour {

	// Use this for initialization

    public int startTime = 0;
    [Header("Set endTime to -1 to never stop")]
    public int endTime = 0;

    private bool started = false;
    private bool stopped = false;
    private bool running = false;

	void Start () {
        TimerController.secondElapsed += TimerController_secondElapsed;
	    hideObject();
	}

    private void hideObject()
    {

        //GetComponent<MeshRenderer>().enabled = false;
        setMeshRecursive(this.gameObject, false);
    }
    private void showObject()
    {
        //GetComponent<MeshRenderer>().enabled = true;
        setMeshRecursive(this.gameObject, true);
    }


    private void setMeshRecursive(GameObject obj, bool enable)
    {
        if (null == obj)
            return;
        if (obj.GetComponent<MeshRenderer>() != null)
            obj.GetComponent<MeshRenderer>().enabled = enable;
        if (obj.GetComponent<SkinnedMeshRenderer>() != null)
            obj.GetComponent<SkinnedMeshRenderer>().enabled = enable;
        if (obj.GetComponent<Light>() != null)
            obj.GetComponent<Light>().enabled = enable;

        foreach (Transform child in obj.transform)
        {
           
            if (null == child)
                continue;
            //child.gameobject contains the current child you can do whatever you want like add it to an array
            setMeshRecursive(child.gameObject, enable);

        }
    }


    private void TimerController_secondElapsed(int runTime)
    {
        if (runTime >= startTime)
        {
            onStart();
            started = true;
        }
        if (runTime >= endTime && endTime != -1)
        {
            onStop();
            stopped = true;
        }

    }

    private void onStop()
    {
        running = false;
        hideObject();
    }

    private void onStart()
    {
        running = true;
        showObject();
    }
}
