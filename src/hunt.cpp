#include "hunt.h"

const int PIN_hall_effect = 5; 
constexpr int hall_effect_polling_time = 1; //1ms. poll faster to not miss the magnet

void huntForMag() {
    Serial.println("Hunting for magnet");

    runMotor();

    unsigned long millis_start = millis();

    // Get off the inital mag
    while (readHallEffect()) {
        delay(hall_effect_polling_time); 
        if (millis() - millis_start > 500) {
            Serial.println("Error: Stuck on inital mag");
            Serial.println("Is the Hall Sensor wire plugged in?");
            unjamRoutine();
            stopMotor();
            return;
        }
    }

    millis_start = millis();

    int error_count = 0;

    // Hunt for the next mag 
    while (!readHallEffect()) {
        delay(hall_effect_polling_time); 
        if (millis() - millis_start > 500) {
            error_count++;

            Serial.print("Hunting error detected! Attempt ");
            Serial.println(error_count);

            if (error_count >= 3) {
                Serial.println("Giving up...");
                stopMotor();
                return;
            }

            unjamRoutine();
            millis_start = millis();
        }
    }
    stopMotor();
}

/// @brief 
/// @return True = magnet detected; False = no magnet detected 
bool readHallEffect() {
    Serial.print(">hallEffect:");
    bool value = !digitalRead(PIN_hall_effect);
    Serial.println(value);
    return value;
}
