#include <Arduino.h>
#include <RF24.h>
#include <nRF24L01.h>
#include <SPI.h>

#define CE 27
#define CSN 5

#define JOYSTICK 33

RF24 radio(CE, CSN);

const byte addres[5] = {0xc5, 0xf3, 0x7, 0xfa, 0xaa};

boolean buttonState = 0;

void setup() {
  pinMode(JOYSTICK, INPUT);
  Serial.begin(115200);

  radio.begin();
  radio.setPALevel(RF24_PA_LOW);
  radio.openWritingPipe(addres);
  radio.stopListening();
}

void loop() {
  int angleRead = analogRead(JOYSTICK);
  int servoAngle = map(angleRead, 0, 4095, 0, 180);
  Serial.println(servoAngle);
  radio.write(&servoAngle, sizeof(servoAngle));
}
