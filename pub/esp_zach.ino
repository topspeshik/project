#include <SoftwareSerial.h>

SoftwareSerial mySer(4, 5);

void setup() {
  Serial.begin(9600);
  mySer.begin(9600);

  while (!Serial) {}
  while (!mySer) {}
}

void loop() {
  if (mySer.available() > 0) {
    Serial.write(mySer.read());
  }
}
