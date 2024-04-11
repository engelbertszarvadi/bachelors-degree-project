#include <RH_ASK.h>
#include <SPI.h>
#include <SoftwareSerial.h>

#define RX 2
#define TX 3

RH_ASK rfModule;
SoftwareSerial mySerial(RX, TX);

int voltage;

void setup() {
  pinMode(RX, INPUT);
  pinMode(TX, OUTPUT);

  Serial.begin(9600);
  mySerial.begin(9600);

  if (!rfModule.init()) Serial.println("RF initialization failed!");
}

void loop() {
  uint8_t data[1];
  uint8_t dataLength = sizeof(data);

  if (rfModule.recv(data, &dataLength)) {
    voltage = data[0];
    
    mySerial.write(voltage);
  }

  delay(250);
}
