#include "ThingSpeak.h"
#include "WiFi.h"

char ssid[] = "JioFiber-dq6nd";  
char pass[] = "anshularchanaanjali";

#define echo 12 // attach pin D12 Arduino to pin Echo of HC-SR04
#define trigger 13 //attach pin D13 Arduino to pin Trig of HC-SR04

long duration; // variable for the duration of sound wave travel
int distanceCM; // variable for the distance measurement
int constDis;
int noObject = -1;

WiFiClient client;

unsigned long myChannelField = 1645355; 
//const int ChannelField1 = 1; 
const int ChannelField2 = 2; 
const char * myWriteAPIKey = "O9RXRMUYHAI25G1R";

void setup() {
  Serial.begin(115200);
  pinMode(trigger, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echo, INPUT); // Sets the echoPin as an INPUT
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);
}

void loop() 
{
  //-----------------WiFi Setup-------------------//
  if(WiFi.status()!= WL_CONNECTED)
  {
    Serial.print("Attempting to Connect to SSID: ");
    Serial.println("Jio");
  }
  while(WiFi.status()!= WL_CONNECTED)
  {
    WiFi.begin(ssid,pass);
    Serial.print(".");
    delay(5000);
  }
  Serial.println("\nConnected.");
  //--------------------------------------------//
  
  w
  Serial.print("Number of objects: ");
  Serial.println(noObject);

  //-------------Sending Data to ThingSpeak Cloud---------------//
  ThingSpeak.writeField(myChannelField, ChannelField2, noObject, myWriteAPIKey);
  delay(1000);
}
