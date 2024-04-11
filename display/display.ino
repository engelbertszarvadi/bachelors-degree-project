#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <SPI.h>
#include <SoftwareSerial.h>

#define screenWidth 128
#define screenHeight 64
#define screenAddress 0x3C
#define oledReset -1

#define RX 2
#define TX 3

Adafruit_SSD1306 display(screenWidth, screenHeight, &Wire, oledReset);
SoftwareSerial mySerial(RX, TX);

String inputText = "WELCOME";
String prevInputText = "";

int textSize = 2;

void setup() {
  pinMode(RX, INPUT);
  pinMode(TX, OUTPUT);

  Serial.begin(9600);
  mySerial.begin(9600);

  display.begin(SSD1306_SWITCHCAPVCC, screenAddress);
  display.display();
  delay(500);
  display.clearDisplay();
}

void displayCenter(String text) {
  int16_t x1;
  int16_t y1;
  uint16_t width = screenWidth / 2;
  uint16_t height = screenHeight / 2;

  display.getTextBounds(text, 0, 0, &x1, &y1, &width, &height);

  display.setCursor((screenWidth - width) / 2, (screenHeight - height) / 2);
  display.println(text);
  display.display();
}

void loop() {
  display.setTextSize(textSize);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);

  if (mySerial.available() > 0) {
    int inputVoltage = mySerial.read();
    inputVoltage = map(inputVoltage, 0, 255, 0, 1023);
    inputText = (inputVoltage * 5.0) / 1024.0;
  }

  if (inputText != prevInputText) {
    display.clearDisplay();
    prevInputText = inputText;
  }

  displayCenter(inputText);
}