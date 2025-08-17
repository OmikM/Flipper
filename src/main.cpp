#include <Arduino.h>
#include <vector>
#include <functional>
#include <String>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <unistd.h>
#include <SD.h>
using namespace std;
#include "hardware.h"
#include "display.h"
#include "menu.h"
#include "IR.h"
#include "type.h"
#include "radio.h"
#include "rfid.h"
#include "micro_sd.h"
#include "IR_send.h"





#define on_off_switch_p  GPIO_NUM_32

void setup(){
	pinMode(rfid_cs, OUTPUT);
  	pinMode(SD_cs_p, OUTPUT);
  	digitalWrite(rfid_cs, HIGH);
  	digitalWrite(SD_cs_p, HIGH);
  	Serial.begin(115200);
	pinMode(ledPin, OUTPUT);

	

	for(int i = 0; i < 4; i++){
		pinMode(b_pins[i], INPUT);
	}

	pinMode(on_off_switch_p, INPUT);
	esp_err_t result = esp_sleep_enable_ext0_wakeup(on_off_switch_p, 1);

	SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI);
	for (int i = 0; i < 10; i++) {
	    SPI.transfer(0xFF);
  	}

	
	N.init_RFID();
	radio_init();
	tp.typeInit();
	initDisplay();


	toggle_cs(1);
	SD.begin(SD_cs_p);

	M.dir = listDir(SD, M.path.c_str(), 0);
	
}

void up(){
	M.scroll(1);
	Serial.println('u');
}
void down(){
	M.scroll(0);
  	Serial.println('d');
}
void left(){
	M.back();
	Serial.println('l');
}
void right(){
	M.next();
  	Serial.println('r');
}

bool pressed;
bool on_off = 1; //1 = ON


void loop() {
	pressed = false;
	int pressed_ind = -1;
  	delay(200);
	
  	M.Print_out();
	
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