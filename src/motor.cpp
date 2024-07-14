#include "motor.h"

const int PIN_enA = 9;
const int PIN_in1 = 6;
const int PIN_in2 = 7;

const int base_speed = 200;
constexpr int reverse_speed = base_speed * 1.2;
constexpr int initial_reverse_time = 500; // 500ms
constexpr int reverse_time = 500; // 500ms
constexpr bool motor_direction_forward = true;
constexpr bool motor_direction_backward = false;
constexpr int unjaming_loop_time = 300; // 300ms

bool current_direction = true;
bool current_running = false;


void setupMotor() {
    pinMode(PIN_enA, OUTPUT);
    pinMode(PIN_in1, OUTPUT);
    pinMode(PIN_in2, OUTPUT);

    //set the motor directions with 
    // in1 enable, in2 disable
    // in1 disable, in2 enable

    // Set initial rotation direction
    setDirection(current_direction);
    stopMotor();
}

void setDirection(bool direction) {
    current_direction = direction;

    digitalWrite(PIN_in1, direction);
    digitalWrite(PIN_in2, !direction);
}

void runMotor() {
    current_running = true;
    analogWrite(PIN_enA, base_speed);
}

void stopMotor() {
    current_running = false;
    analogWrite(PIN_enA, 0);
}

void setSpeed(int speed_to_set) {
    analogWrite(PIN_enA, speed_to_set);
}


void unjamRoutine(int8_t unjam_loops = 5) {
    bool inital_direction = current_direction;

    Serial.println("Unjamming routine");
    // Run in reverse for a short period of time 
    stopMotor();
    delay(initial_reverse_time); // delay to let you know shit is happening
    setDirection(motor_direction_backward); //  
    setSpeed(base_speed);
    // analogWrite(PIN_enA, (base_speed));
    runMotor();
    delay(initial_reverse_time);
    stopMotor();

    analogWrite(PIN_enA, base_speed);

    for (int i = 0; i < unjam_loops; i++) {
        setDirection(i % 2 == 0 ? motor_direction_backward : motor_direction_forward);
        delay(unjaming_loop_time);
    }

    setDirection(motor_direction_backward);
    delay(initial_reverse_time);
    // Return to original direction
    setDirection(motor_direction_forward);
}
