#include <ESP8266WebServer.h>
bool state = false;
ESP8266WebServer server(80);

void handle_root(){
  String form = "<form action=\"/switch\" method=\"POST\">";
  form = form + "<input type=\"submit\" value=\"Switch\">";
  form = form + "</form>";
  
  server.send(200, "text/html",form);
  server.send(303);
}

void handleSensor(){
  server.sendHeader("Location", "/");
  state = !state;
  server.send(303);
}
void handleNotFound(){
  server.send(404, "text/plain", "404:Not Found");
}


void server_init(){
  server.on("/", HTTP_GET, handle_root);
  server.on("/switch", HTTP_POST, handleSensor);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("Server started at port 80");
}
