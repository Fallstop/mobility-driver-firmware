#include "hunt.h"

const int PIN_hall_effect = 5; 

void huntForMag() {
    runMotor();

    // Get off the inital mag
    while (readHallEffect()) {
        delay(100);
    }

    unsigned long millis_start = millis();

    int error_count = 0;

    // Hunt for the next mag
    while (!readHallEffect()) {
        delay(100);
        if (millis() - millis_start > 5000) {
            error_count++;
            if (error_count > 3) {
                return;
            }

            unjamRoutine();
            millis_start = millis();
        }
    }
}

bool readHallEffect() {
    return !digitalRead(PIN_hall_effect);
}
