/*
 * 
 * 
 * 
 * 
 * 
 */
#include <Wire.h>

#define EEPROM_ADDRESS 0x50

const int runButtonPin = 2;
const int readyLedPin = 4;
const int inProgLedPin =  5;

int runButtonState = 0;
int eepromAddress = 0;
byte value;

void setup() {
  pinMode(runButtonPin, INPUT);
  pinMode(readyLedPin, OUTPUT);
  pinMode(inProgLedPin, OUTPUT);
  // initialize IO.
  
  Serial.begin(9600);
  while (!Serial) {
    ;
  }
  // wait for serial port to connect before proceeding.

  Wire.begin();
  Wire.setClock(400000);
  // start I2C connection. 

  digitalWrite(readyLedPin, HIGH);
  digitalWrite(inProgLedPin, LOW);
  // display status using leds.
}

void loop() {
  runButtonState = digitalRead(runButtonPin);
  if (runButtonState == HIGH) {
    readFullEeprom();
  }
}

void readFullEeprom() {
  digitalWrite(inProgLedPin, HIGH);
  for (long index = 0; index < 0x7D00; index++){
    byte value = readEepromAddress(index);
    Serial.print(value, BIN);
  }
  digitalWrite(inProgLedPin, LOW);
}

byte readEepromAddress(long memoryAddress) {
  Wire.beginTransmission(EEPROM_ADDRESS);
  Wire.write((int)(memoryAddress >> 8));
  Wire.write((int)(memoryAddress & 0xFF));
  Wire.endTransmission();

  Wire.requestFrom(EEPROM_ADDRESS, 1);
  byte data = 0xFF;
  if (Wire.available()) data = Wire.read();
  return data;
}
