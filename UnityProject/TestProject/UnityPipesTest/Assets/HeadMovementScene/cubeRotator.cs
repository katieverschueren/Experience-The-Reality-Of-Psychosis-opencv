using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class cubeRotator : MonoBehaviour {

	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
        transform.Rotate(Vector3.forward, 1);
        transform.Rotate(Vector3.up, 3);
	}
}
