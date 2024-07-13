#include <Arduino.h>

#include <motor.h>
#include <hunt.h>

// Has to be 2/3 for interrupt
const int PIN_button = 2;

int number_to_dispense = 1;

unsigned long millis_last_button = 0;


void buttonPressed() {
  if (millis() - millis_last_button < 300) {
    return;
  }
  number_to_dispense += 1;
  millis_last_button = millis();
}

void setup() {
  setupMotor();
  attachInterrupt(PIN_button, buttonPressed, RISING);
}

void loop() {
  while (number_to_dispense > 0) {
    
    huntForMag();
    number_to_dispense -= 1;
  }
}