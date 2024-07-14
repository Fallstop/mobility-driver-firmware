#include <Arduino.h>

#include <motor.h>
#include <hunt.h>

// #define simple_mode 1

// Has to be 2/3 for interrupt
const int PIN_Interrupt_Button = 2;

int number_to_dispense = 1;

unsigned long millis_last_button = 0;

constexpr int button_debounce_time = 300; //300ms
#ifdef simple_mode
constexpr int simple_reverse_time = 400; //400ms
constexpr int simple_forward_time = simple_reverse_time * 2; //500ms
#endif


void buttonPressed() {
  if (millis() - millis_last_button < button_debounce_time) {
    return;
  }
  number_to_dispense += 1;
  millis_last_button = millis();
  // printf("ButtonPressed");
}

void setup() {
  Serial.begin(9600);
  Serial.println("Starting up");

  setupMotor();
  pinMode(PIN_Interrupt_Button, INPUT_PULLUP); // Active low
  attachInterrupt(digitalPinToInterrupt(PIN_Interrupt_Button), buttonPressed, FALLING);
}

void loop() {

  #ifdef simple_mode
  while (true)
  {
    if (number_to_dispense > 0)
    {
      setDirection(motor_direction_backward);;
      runMotor();
      delay(simple_reverse_time);
      setDirection(motor_direction_forward);
      delay(simple_forward_time);
      stopMotor();
    }
  }
  #endif 

  while (number_to_dispense > 0) {
    Serial.println("Dispensing, qued up :" + String(number_to_dispense));
    huntForMag();
    number_to_dispense -= 1;
  }
}