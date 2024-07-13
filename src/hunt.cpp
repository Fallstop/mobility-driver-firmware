#include "hunt.h"

const int PIN_hall_effect = 5; 

void huntForMag() {
    Serial.println("Hunting for magnet");

    runMotor();

    unsigned long millis_start = millis();

    // Get off the inital mag
    while (readHallEffect()) {
        delay(100);
        if (millis() - millis_start > 1000) {
            Serial.println("Error: Stuck on inital mag");
            Serial.println("Is the Hall Sensor wire plugged in?");
            return;
        }
    }

    millis_start = millis();

    int error_count = 0;

    // Hunt for the next mag
    while (!readHallEffect()) {
        delay(100);
        if (millis() - millis_start > 5000) {
            error_count++;

            Serial.print("Hunting error detected! Attempt ");
            Serial.println(error_count);

            
            if (error_count > 3) {
                Serial.println("Giving up...");
                return;
            }

            unjamRoutine();
            millis_start = millis();
        }
    }
}

bool readHallEffect() {
    Serial.print(">hallEffect:");
    bool value = !digitalRead(PIN_hall_effect);
    Serial.println(value);
    return value;
}
