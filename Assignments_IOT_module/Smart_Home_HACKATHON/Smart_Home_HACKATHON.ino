#include <analogWrite.h>
//#define CAYENNE_PRINT Serial
#include <CayenneMQTTESP32.h>
#include "DHT.h"

// WiFi network info.
char ssid[] = "JioFiber-dq6nd";
char wifiPassword[] = "anshularchanaanjali";

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "ae529690-8a69-11ec-8da3-474359af83d7";
char password[] = "561b8fafb9abd5134ab13a442c2d73a4ecf0cac5";
char clientID[] = "349c55b0-8a6a-11ec-9f5b-45181495093e";
int LDR = 33;
int PIR = 14;
int DHTPIN = 2;
int echo = 12, trigger = 13;

int ALARM = 15;
int LED_RED = 25;
int LED_BLUE = 26;
int LED_YELLOW = 27;

int val, val1, val2;
int sw1 = 0, sw2 = 0, sw3 = 0; 
int pirStatus = 0, uvStatus = 0, ledStatus = 1, dhtStatus = 0;
int count = 0, duration, constDist, distanceCm;
int temp, humi;

DHT dht(DHTPIN, DHT11);

void setup() {
  Serial.begin(115200);
  dht.begin();
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(ALARM, OUTPUT);
  pinMode(PIR, INPUT);
  pinMode(LDR, INPUT);  
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  analogWrite(LED_RED, 0);
  analogWrite(LED_BLUE, 0);
  analogWrite(LED_YELLOW, 0);
  digitalWrite(ALARM, LOW);
  Cayenne.begin(username, password, clientID, ssid, wifiPassword);
}

void loop() {
  Cayenne.loop();
  if((ledStatus == 1) && (sw1 == 0 || sw2 == 0 || sw3 == 0))
  {
    val1 = analogRead(LDR);
    Serial.print("LDR Sensor Value: ");    
    Serial.println(val1);
    if(val1 < 300 )
    {
      if(sw1 == 0)
        analogWrite(LED_RED, 0);
      if(sw2 == 0)  
        analogWrite(LED_BLUE, 0);
      if(sw3 == 0)  
        analogWrite(LED_YELLOW, 0);
      val2 = 4;
    }
    else if(val1 >= 300 && val1 <= 1500)
    {
      if(sw1 == 0)
        analogWrite(LED_RED, 2);
      if(sw2 == 0)
        analogWrite(LED_BLUE, 2);
      if(sw3 == 0)  
        analogWrite(LED_YELLOW, 2);
      val2 = 3;    
    }
    else if(val1 > 1500 && val1 <= 2700)
    {
      if(sw1 == 0)
        analogWrite(LED_RED, 30);
      if(sw2 == 0)  
        analogWrite(LED_BLUE, 30);
      if(sw3 == 0)  
        analogWrite(LED_YELLOW, 30);
      val2 = 2;
    }
    else if(val1 > 2700 && val1 <= 3700)
    {
      if(sw1 == 0)
        analogWrite(LED_RED, 115);
      if(sw2 == 0)  
        analogWrite(LED_BLUE, 115);
      if(sw3 == 0)  
        analogWrite(LED_YELLOW, 115);
      val2 = 1;
    }
    else 
    {
      if(sw1 == 0)
        analogWrite(LED_RED, 255);
      if(sw2 == 0)  
        analogWrite(LED_BLUE, 255);
      if(sw3 == 0)  
        analogWrite(LED_YELLOW, 255);
      val2 = 0;
    }
  Serial.print("Brightness Level: ");
  Serial.println(val2);      
  } 
  else
  {
    analogWrite(LED_RED, 0);
    analogWrite(LED_BLUE, 0);
    analogWrite(LED_YELLOW, 0);    
  }
  Cayenne.virtualWrite(0, val1);  
  Cayenne.virtualWrite(1, val2);
  Cayenne.virtualWrite(2, val2);
  Cayenne.virtualWrite(3, val2);     
  // For PIR Sensor
  if(pirStatus == 1)
  {
    Serial.println("PIR Sensor is switched ON.");
    int val = digitalRead(PIR); 
    if (val == HIGH) 
    { 
      digitalWrite(ALARM, HIGH); 
      Serial.println("Motion detected!(PIR)");
      Cayenne.virtualWrite(8, 1);
      delay(8000);
    }
    else
      digitalWrite(ALARM, LOW);
  }
  // For UV Sensor  
  if (uvStatus == 1)
  {
    Serial.println("UV Sensor is switched ON.");
    digitalWrite(trigger, LOW);
    delayMicroseconds(2);
    digitalWrite(trigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigger, LOW);
  
    duration = pulseIn(echo, HIGH);
    distanceCm = (duration * 0.034)/2;
    Serial.print("Distance in cm: ");
    Serial.println(distanceCm);
    if (count == 0)
    {
      constDist = distanceCm;    
      count++;
    }
    if (distanceCm <= (constDist-1))
    {
      digitalWrite(ALARM, HIGH); 
      Serial.println("Motion detected!(UV)");
      Cayenne.virtualWrite(10, 1);
      delay(8000);
    }
    else
      digitalWrite(ALARM, LOW);
  }
  // For Temperature and Humidity Sensor
  if(dhtStatus == 1)
  {   
    humi = dht.readHumidity();
    temp = dht.readTemperature();
    Serial.print("Temperature: ");
    Serial.println(temp);
    Serial.print("Humidity: ");
    Serial.println(humi);
    Cayenne.virtualWrite(14, temp);
    Cayenne.virtualWrite(15, humi);          
  }  
}

CAYENNE_IN(5)
{
	int value = getValue.asInt(); // -50 to 255
  if(value >= 0)
    sw1 = 1;
  else
    sw1 = 0;
	analogWrite(LED_RED, value);
}

CAYENNE_IN(6)
{
	int value = getValue.asInt(); // -50 to 255
  if(value >= 0)
    sw2 = 1;
  else
    sw2 = 0;
	analogWrite(LED_BLUE, value);
}

CAYENNE_IN(7)
{
	int value = getValue.asInt(); // -50 to 255
  if(value >= 0)
    sw3 = 1;
  else
    sw3 = 0;
	analogWrite(LED_YELLOW, value);
}

CAYENNE_IN(9)
{
	pirStatus = getValue.asInt();
  if (pirStatus == 0)
  {  
    Cayenne.virtualWrite(8, 0);
    Serial.println("PIR Sensor is switched OFF.");
  }        
}

CAYENNE_IN(11)
{
	uvStatus = getValue.asInt();
  if (uvStatus == 0)
  {
    count = 0;
    Cayenne.virtualWrite(10, 0);
    Serial.println("UV Sensor is switched OFF.");
  }    
}

CAYENNE_IN(12)
{
	ledStatus = getValue.asInt(); 
}

CAYENNE_IN(13)
{
	dhtStatus = getValue.asInt(); 
  if(dhtStatus == 1)
    Serial.println("DHT11 Sensor is switched ON.");
  else
    Serial.println("DHT11 Sensor is switched OFF.");
}
