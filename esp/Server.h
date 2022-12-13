#include <ESP8266WebServer.h>

ESP8266WebServer server(80);

bool isBright = false;

void handleRoot() {
  String form = "<form action=\"/\" method=\"POST\">";
  form = form + "<input type=\"submit\" value=\"Switch\">";
  form = form + "<h1>";
  if (isBright) {
    form = form + "bright";
  } else {
    form = form + "sonic";
  }
  form = form + "</h1>";
  form = form + "</form>";
  server.send(200, "text/html", form);
}

void handleSwitch() {
  isBright = !isBright;
  server.sendHeader("Location", "/");
  server.send(303);
}

void handleNotFound() {
  server.send(404, "text/plan", "404;Not found");
}

void server_init() {
  server.on("/", HTTP_GET, handleRoot);
  server.on("/", HTTP_POST, handleSwitch);
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("Server started at port 80");
}
