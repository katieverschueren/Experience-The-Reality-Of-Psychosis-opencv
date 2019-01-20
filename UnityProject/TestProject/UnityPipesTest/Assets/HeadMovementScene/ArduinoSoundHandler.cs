using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ArduinoSoundHandler : MonoBehaviour {

	// Use this for initialization
    public string ip = "192.168.178.20/";
    public string port = "80/";

    void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		
	}


    public void startSound()
    {
        string url = ip + port + "player/start";
        WWW myWww = new WWW(url);
    }
}
