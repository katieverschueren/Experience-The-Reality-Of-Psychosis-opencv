using UnityEngine;
using System.IO;
using System.Threading;
using System.IO.Pipes;
using System.ComponentModel;

public class PipeClient : MonoBehaviour {

    public delegate void PipeResponse(string response);
    public static event PipeResponse onResponse;

    private string pipeName
     {
         get
         {
             return "KatiePipe";
         }
     }
     private NamedPipeClientStream stream;
     private StreamWriter sw;
     private StreamReader sr;
 
     /// <summary>
     /// Thread for inter process communication
     /// </summary>
     private Thread interProc;
 
     /// <summary>
     /// When set tells thread to continue its work.
     /// </summary>
     private AutoResetEvent msgEvent;
 
     /// <summary>
     /// Must-have for get{} in messageTo
     /// </summary>
     private string tmpMessageTo;


    private float deltaTime = 0;
     /// <summary>
     /// Message that will be sent to another process. Sets msgEvent automatically.
     /// </summary>
     private string messageTo
     {
         get
         {
             return tmpMessageTo; //Required so it doesn't cause infinite loop.
         }
         set
         {
             tmpMessageTo = value;
             msgEvent.Set(); //Setting event will cause second thread to continue its work.
         }
     }
     private string messageFrom;
 
     /// <summary>
     /// Should 2nd thread be still running?
     /// </summary>
     private volatile bool run = true;
 
     void Start()
     {
         msgEvent = new AutoResetEvent(false); //False means that it will not trigger the event when it's created.

        Debug.Log("Press spacebar to initialize: ");
     }
 
     void Update()
     {
         //Sending messages to the pipe
         if (Input.GetKeyDown(KeyCode.Space))
         {
            Initialise();
         }
        deltaTime += Time.deltaTime;
     }
 
     /* --- SECOND THREAD ---*/
     /// <summary>
     /// Initialises writers/readers and the pipe
     /// </summary>
     void Initialise()
     {
         //Starting the pipe
         Debug.LogFormat("[IPC] Creating new ClientStream. Pipe name: {0}", pipeName);
         stream = new NamedPipeClientStream(".", pipeName, PipeDirection.InOut);
 
         //Connecting to the pipe
         Debug.Log("[IPC] Connecting...");
         try
         {
             stream.Connect(120);
         }
         catch (Win32Exception)
         {
             Debug.LogError("[IPC] Server not running");
             run = false;
             return;
         }
         Debug.Log("[IPC] Connected");
 
         //Initialising Readers/Writers
         Debug.Log("[IPC] Starting StreamReader");
         sr = new StreamReader(stream);
 
         Debug.Log("[IPC] Starting StreamWriter");
         sw = new StreamWriter(stream);
 
         //AutoFlush
         Debug.Log("[IPC] AutoFlush = true");
         sw.AutoFlush = true;

        interProc = new Thread(Listen);
        interProc.Start();

    }
    void Listen()
     {
         while (run) //Main loop of the thread
         {
             messageFrom = "";

 
             messageFrom = sr.ReadLine(); //Reading
             if (messageFrom.Length > 0)
             {
                onResponse(messageFrom);
                Debug.Log(1/ deltaTime);
                deltaTime = 0;
             }
            Thread.Sleep(1);
         }
         Debug.Log("Finished");
     }
 
     /* --- UNITY'S THREAD --- */
     //The following should stop the thread on Editor and Standalone quit and also when the game object is destroyed.
     public void OnApplicationQuit()
     {
         run = false;
         if (interProc != null)
         {
             if (interProc.ThreadState != ThreadState.Aborted)
                 interProc.Abort();
         }
     }
 
     public void OnDestroy()
     {
         run = false;
         if (interProc != null)
         {
             if (interProc.ThreadState != ThreadState.Aborted)
                 interProc.Abort();
         }
     }
 }