using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TimerTranslationComponent : MonoBehaviour {

    // Use this for initialization
    public int startTime = 0;
    [Header("Set endTime to -1 to never stop")]
    public int endTime = 0;
    public Vector3 target;

    private bool isStarted = false;
    private bool isStopped = false;


    void Start ()
    {
        TimerController.secondElapsed += TimerController_secondElapsed;

    }

    private void TimerController_secondElapsed(int runTime)
    {
        if (runTime >= startTime && !isStarted)
        {
            StartCoroutine(MoveToPosition(this.transform, target, (endTime - startTime)));
            isStarted = true;
        }
        if (runTime >= endTime && endTime != -1 && !isStopped)
        {
          //  onStopAnim();
            isStopped = true;
        }
    }

    public IEnumerator MoveToPosition(Transform transform, Vector3 position, float timeToMove)
    {
        var currentPos = transform.localPosition;
        var t = 0f;
        while (t < 1)
        {
            t += Time.deltaTime / timeToMove;
            transform.localPosition = Vector3.Lerp(currentPos, position, t);
            yield return null;
        }
    }

}
