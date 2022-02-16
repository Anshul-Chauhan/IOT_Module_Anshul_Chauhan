#include "ThingSpeak.h"
#include "WiFi.h"

char ssid[] = "JioFiber-dq6nd";  
char pass[] = "anshularchanaanjali";

int ledPin = 2; // choose the pin for the LED
int pirPin = 15; // choose the input pin (for PIR sensor)
int pirState = LOW; // we start, assuming no motion detected
int val = 0; // variable for reading the pin status
int count = 0;
int ledStatus = LOW;

WiFiClient client;

unsigned long myChannelField = 1646198; 
const int ChannelField1 = 1; 
const int ChannelField2 = 2; 
const char * myWriteAPIKey = "XKSN5RYJHH0KN97T";

void setup() {
 pinMode(ledPin, OUTPUT); // declare LED as output
 pinMode(pirPin, INPUT); // declare sensor as input

 Serial.begin(115200);
 WiFi.mode(WIFI_STA);
 ThingSpeak.begin(client);
}

void loop(){
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

 ledStatus = LOW;
 val = digitalRead(pirPin); // read input value
 if (val == HIGH) { // check if the input is HIGH
 digitalWrite(ledPin, HIGH); // turn LED ON
 count++;
 ledStatus = HIGH;
 if (pirState == LOW) {
 // we have just turned on
 Serial.println("Motion detected!");
 Serial.print("LED Status: ");
 Serial.println(ledStatus);
 // We only want to print on the output change, not state
 pirState = HIGH;
 }
 } else {
 digitalWrite(ledPin, LOW); // turn LED OFF
 if (pirState == HIGH){
 // we have just turned of
 Serial.println("Motion ended!");
 // We only want to print on the output change, not state
 pirState = LOW;
 }
 }
 //-------------Sending Data to ThingSpeak Cloud---------------//
 ThingSpeak.writeField(myChannelField, ChannelField1, count, myWriteAPIKey);
 ThingSpeak.writeField(myChannelField, ChannelField2, ledStatus, myWriteAPIKey);
 delay(1000); 
}