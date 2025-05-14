#include <Arduino.h>
#include <RF24.h>
#include <nRF24L01.h>
#include <SPI.h>

#define CE 27
#define CSN 5
#define BUTTON 32

RF24 radio(CE, CSN);

const byte addres[5] = {0xc5, 0xf3, 0x7, 0xfa, 0xaa};

boolean buttonState = 0;

void setup() {
  pinMode(BUTTON, INPUT);
  pinMode(2, OUTPUT);
  Serial.begin(115200);

  while(!radio.begin()){
    digitalWrite(2, HIGH);
    delay(5000);
  }
    digitalWrite(2, LOW);

  radio.setPALevel(RF24_PA_HIGH);
  radio.openWritingPipe(addres);
  radio.stopListening();


  Serial.println(radio.getStatusFlags());
}

void loop() {
  buttonState = digitalRead(BUTTON);
  Serial.println(buttonState);
  radio.write(&buttonState, sizeof(buttonState));
  delay(1000);
}
