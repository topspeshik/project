#include <SoftwareSerial.h>

SoftwareSerial NewSerial(9, 10);

void setup() {
  Serial.begin(9600);
  NewSerial.begin(9600);
}

void loop() {
  while (NewSerial.available()) {
    char msg = NewSerial.read();
    Serial.print(msg);
  }
}