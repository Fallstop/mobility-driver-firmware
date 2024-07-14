#pragma once
#include <Arduino.h>

void setupMotor();

void setDirection(bool direction);

void runMotor();

void setSpeed(int speed_to_set);

void stopMotor();

void unjamRoutine(int8_t unjam_loops = 5);