#include <Arduino.h>
#include "hardware.h"
#include <SD.h>
unsigned long lastDebounceTime = 0;
bool lastStates[4] = {0};
bool curStates[4] = {0};
char push = '0';

// digitalWrite(SD_cs_p, !(is_SD));      
// digitalWrite(rfid_cs, is_SD);

// 1 toggle to SD 0 to RFID
void toggle_cs(bool is_SD){
    if (is_SD) {
        digitalWrite(SD_cs_p, LOW);
        digitalWrite(rfid_cs, HIGH);
    } else {
        digitalWrite(SD_cs_p, HIGH);
        digitalWrite(rfid_cs, LOW);
    }
}