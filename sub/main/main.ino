#include "WIFI.h"
#include "server.h"
#include <SoftwareSerial.h>

#define TRIG_PIN 14
#define ECHO_PIN 12
#define LED_PIN 2
#define BRIGHT_PIN A0


SoftwareSerial mySerial(0, 4);

int maxBright = 0;
long duration;
int distance;
String ledState;

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT); 
  pinMode(LED_PIN, OUTPUT);
  
  while(!Serial) {}
  while(!mySerial) {}
  
  WiFi_init(true);
  server_init();

}

void loop() {
  server.handleClient();

  if (state){

    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);

    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    duration = pulseIn(ECHO_PIN, HIGH);

    distance = duration * 0.034 / 2; // Speed 

    mySerial.println("S" + String(distance));
  }
  else
  {
    int bright = analogRead(BRIGHT_PIN);
    mySerial.println("B" + String(bright));
  }
//
  while (Serial.available())
  {
    ledState = Serial.read();
  }

  if (ledState == "0") {
    digitalWrite(LED_PIN, LOW);
  }
  
  else if (ledState == "1") 
  {  
    digitalWrite(LED_PIN, HIGH);
  }
  
    
}
  
