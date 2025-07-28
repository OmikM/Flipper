#include <Arduino.h>
#include <vector>
#include <functional>
#include <String>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <unistd.h>
using namespace std;
#include "hardware.h"
#include "display.h"
#include "menu.h"
#include "IR.h"
#include "type.h"
#include "radio.h"


#define on_off_switch_p  GPIO_NUM_32

void setup(){
  	Serial.begin(115200);
	pinMode(ledPin, OUTPUT);

  	fr.name = "fr";

	for(int i = 0; i < 4; i++){
		pinMode(b_pins[i], INPUT);
	}

	pinMode(on_off_switch_p, INPUT);
	esp_err_t result = esp_sleep_enable_ext0_wakeup(on_off_switch_p, 1);
	
	radio_init();
	tp.typeInit();
	initDisplay();
	fr.initMenu();
}

void up(){
	fr.cur()->scroll(1);
	Serial.println('u');
}
void down(){
	fr.cur()->scroll(0);
  	Serial.println('d');
}
void left(){
	fr.back();
	Serial.println('l');
}
void right(){
  	Serial.println('r');
	fr.cur()->next();
}

bool pressed;
bool on_off = 1; //1 = ON

void loop() {
	pressed = false;
	int pressed_ind = -1;
  	delay(200);
	
  	fr.cur()->Print_out();
	
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

  if (pressed) {
    if(pressed_ind==0)up();
    if(pressed_ind==1)down();
    if(pressed_ind==2)left();
    if(pressed_ind==3)right();

  }

  for (int i = 0; i < 4; i++) {
    lastStates[i] = curStates[i];
  }
}