#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include "Server.h"
#include <ESP8266WebServer.h>

#define BRIGHT_PIN A0
#define ECHO_PIN 5
#define TRIG_PIN 4
#define LED_PIN 2

long duration;
int distance;

String ip ="IP unset";
String ssid_pref="ESP2866_";
String pass ="12345687";

int maxBright = 0;

String ssidCLI ="Test123";
String passwordCLI="ubuntu12";

ESP8266WiFiMulti wifiClient;

String id(){
  uint8_t mac[WL_MAC_ADDR_LENGTH];
  WiFi.softAPmacAddress(mac);
  String macID = String(mac[WL_MAC_ADDR_LENGTH-2],HEX)+String(mac[WL_MAC_ADDR_LENGTH-1],HEX);
  macID.toUpperCase();
  return macID;
}

bool StartAPMode(){
  IPAddress apIP(192, 168, 4, 1);
  WiFi.disconnect();
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255,255,255,0));
  WiFi.softAP(ssid_pref + id(), pass);
  //Serial.println("WiFi AP is up with " +ssid_pref+ id());
  return true;
}

bool StartCLI(){
  wifiClient.addAP(ssidCLI.c_str(), passwordCLI.c_str());
  while(wifiClient.run()!=WL_CONNECTED){
    //?
  }
  //Serial.println(ssidCLI);
  return true;
}

void WiFi_init(bool ap_mode){
  if(ap_mode) {
    StartAPMode();
    ip = WiFi.softAPIP().toString();
  }
  else {
    ip = WiFi.localIP().toString();
  }
}

int getBright() {
  return analogRead(BRIGHT_PIN);
}

int getDistance() {
  // Clears the trigPin condition
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(ECHO_PIN, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed 
  return distance;
}

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT); 
  pinMode(LED_PIN, OUTPUT);
  WiFi_init(true);
  server_init();
}

void loop() {
  server.handleClient();
  
  if (isBright) {
    int bright = getBright();
    if (bright > maxBright) {
      maxBright = bright;
    }
    if (bright > maxBright / 2) {
      Serial.write('1');
    } else {
      Serial.write('0');
    }
  } else {
    int distance = getDistance();
    if (distance > 20) {
      Serial.write('1');
    } else {
      Serial.write('0');
    }
  }

  String msg;
  
  while (Serial.available()) {
    msg = Serial.readString();
  }

 if (msg == "0") {
    digitalWrite(LED_PIN, LOW);
  }
  else if (msg == "1") {
    digitalWrite(LED_PIN, HIGH);
  }
  
  delay(500);
}
