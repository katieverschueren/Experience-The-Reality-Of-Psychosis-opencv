#include <SoftwareSerial.h>
#include <MP3Player_KT403A.h>
#include <ESP8266WiFi.h>
#include <SPI.h>


#ifndef STASSID
#define STASSID "Apollo"
#define STAPSK  "Gemini1964"
#endif
#define TFT_DC    5
#define TFT_RST   0
//#define TFT_CS    10 // only for displays with CS pin
#define TFT_MOSI  13   // for hardware SPI data pin (all of available pins)
#define TFT_SCLK  14 

SoftwareSerial mp3(2, 0);
WiFiServer server(80);

const char* ssid = STASSID;
const char* password = STAPSK;

int lineIndex = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  setupMP3();
  setupServer();
}



void setupMP3()
{
   mp3.begin(9600); 
   delay(100);
   SelectPlayerDevice(0x02);       // Select SD card as the player device.
   SetVolume(0x19);           // Set the volume, the range is 0x00 to 0x1E.
   Serial.println("Audio setup");
}

void printOnScreen(String text)
{
  Serial.println(text);
}

void setupServer()
{
  Serial.print(F("Connecting to "));
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(F("."));
  }
  Serial.println();
  Serial.println(F("WiFi connected"));

  // Start the server
  server.begin();
  Serial.println(F("Server started"));

  // Print the IP address
  Serial.println(WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  printOnScreen(F("new client"));

  client.setTimeout(1000); // default is 1000
  String req = client.readStringUntil('\r');
  printOnScreen(F("request: "));
  printOnScreen(req);

  if (req.indexOf(F("/player/start")) != -1) {
    printOnScreen("starting music player");
    SpecifyMusicPlay(1);
    delay(1000);
  }else if (req.indexOf(F("/player/play")) != -1) {
    PlayResume();
    delay(1000);
  }else if (req.indexOf(F("/player/pause")) != -1) {
    PlayPause();
    delay(1000);
  }
  
  while (client.available()) {
    // byte by byte is not very efficient
    client.read();
  }
  client.print(F("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>Experience the reality of Psychosis!</html>"));
  Serial.println(F("Disconnecting from client"));
  
}
