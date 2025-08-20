#include <Arduino.h>
#include "hardware.h"
#include <SD.h>
unsigned long lastDebounceTime = 0;
bool lastStates[4] = {0};
bool curStates[4] = {0};
char push = '0';
bool on_off = 1; //1 = ON
bool pressed;

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

int buttons(){
	pressed = false;
	int pressed_ind = -1;
  	delay(50);

	unsigned long time = millis();
	on_off = digitalRead(on_off_switch_p);

	if(on_off == LOW){
		Serial.println("off");
		esp_light_sleep_start();
	}

	for(int i = 0; i < 4; i++){
		curStates[i] = digitalRead(b_pins[i]);
	}

	for (int i = 0; i < 4; i++) {
    	if (curStates[i] and !lastStates[i]) {
      		if (time - lastDebounceTime > debounceDelay) {
        		pressed = true;
        		pressed_ind = i;
        		lastDebounceTime = time;
        		break;  
      	}
    	}
  	}

  	for (int i = 0; i < 4; i++) {
    	lastStates[i] = curStates[i];
  	}
	return pressed_ind;
}