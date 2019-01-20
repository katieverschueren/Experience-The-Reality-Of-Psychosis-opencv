using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Video;

public enum Direction
{
    LEFT,
    RIGHT
};

public class flickeringController : MonoBehaviour
{

    public Direction direction;

    private VideoPlayer player;
	// Use this for initialization
	void Start ()
	{
	    player = GetComponent<VideoPlayer>();

        if(direction == Direction.RIGHT)
            HeadRotationHandler.lookingRight += HeadRotationHandler_looking;
        else
            HeadRotationHandler.lookingLeft += HeadRotationHandler_looking;
    }

    private void HeadRotationHandler_looking(bool isLooking)
    {
        if (isLooking)
            player.targetCameraAlpha = 0;
        else
            player.targetCameraAlpha = 1;

    }




    // Update is called once per frame
    void Update () {
		
	}
}
