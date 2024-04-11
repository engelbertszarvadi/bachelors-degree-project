#include <RH_ASK.h>
#include <SPI.h>

const int analogInputPin = A0;

RH_ASK rfModule;

void setup() {
  Serial.begin(9600);
  if (!rfModule.init()) Serial.println("RF initialization failed!");
}

void loop() {

  int voltage = analogRead(analogInputPin) / 4;

  byte data[] = { static_cast<byte>(voltage) };

  rfModule.send(data, sizeof(data));
  rfModule.waitPacketSent();

  delay(250);
}
