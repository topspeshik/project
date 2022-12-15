#include <ESP8266WiFi.h>

String ip = "IP unset";
String password = "88148814";
String ssid_pref = "espProject";

String id(){
  uint8_t mac[WL_MAC_ADDR_LENGTH];
  WiFi.softAPmacAddress(mac);
  String macID = String(mac[WL_MAC_ADDR_LENGTH - 2], HEX)+ String(mac[WL_MAC_ADDR_LENGTH] - 1, HEX);

  macID.toUpperCase();
  return macID;
}

bool StartAPMode(){
  IPAddress apIP(192,164,4,2);
  WiFi.disconnect();
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255,255,255,0));
  WiFi.softAP(ssid_pref + id(), password);
  Serial.println("WiFi AP is up with" + ssid_pref + id());

  return true;
}

void WiFi_init(bool ap_mode){
  if(ap_mode){
    StartAPMode();
  }
}
