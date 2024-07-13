#include "motor.h"

const int PIN_enA = 9;
const int PIN_in1 = 6;
const int PIN_in2 = 7;

const int base_speed = 200;

bool current_direction = true;
bool current_running = false;

void setupMotor() {
    pinMode(PIN_enA, OUTPUT);
    pinMode(PIN_in1, OUTPUT);
    pinMode(PIN_in2, OUTPUT);
    // Set initial rotation direction
    setDirection(current_direction);
    stopMotor();
}

void setDirection(bool direction) {
    current_direction = direction;

    digitalWrite(PIN_in1, LOW);
    digitalWrite(PIN_in2, HIGH);
}

void runMotor() {
    current_running = true;
    analogWrite(PIN_enA, base_speed);
}

void stopMotor() {
    current_running = false;
    analogWrite(PIN_enA, 0);
}

void unjamRoutine(int8_t unjam_loops = 5) {
    bool inital_direction = current_direction;

    // Run in reverse for a short period of time
    stopMotor();
    
    setDirection(!current_direction);
    analogWrite(PIN_enA, (base_speed*1.2));
    delay(500);
    stopMotor();

    for (int i = 0; i < unjam_loops; i++) {
        setDirection(!current_direction);
        analogWrite(PIN_enA, base_speed);
        delay(20);
        stopMotor();
        delay(200);
    }

    // Return to original direction
    setDirection(inital_direction);
}
