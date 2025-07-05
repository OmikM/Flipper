#include <StandardCplusplus.h>
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
//#include "type.h"




void setup(){
  	Serial.begin(115200);
	pinMode(ledPin, OUTPUT);

  	fr.mcol("fr", 0);

	for(int i = 0; i < 4; i++){
		pinMode(b_pins[i], INPUT);
	}
	
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
void loop() {
	pressed = false;
	int pressed_ind = -1;
  	delay(200);
	
  	fr.cur()->Print_out();
	
	unsigned long time = millis();

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
    Serial.print("Button ");
    Serial.print(pressed_ind);
    Serial.println(" pressed!");
    if(pressed_ind==0)up();
    if(pressed_ind==1)down();
    if(pressed_ind==2)left();
    if(pressed_ind==3)right();

  }

  for (int i = 0; i < 4; i++) {
    lastStates[i] = curStates[i];
  }
}