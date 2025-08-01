
using namespace std;
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <Arduino.h>
#include "menu.h"
#include "hardware.h"
#include "display.h"
#include "IR.h"
#include "type.h"

extern col fr;


extern Type tp;


void add_ir(){
	for(int j = 0; j < 2; j++){
	char text[13] = "Scanning";
		for(int i =0; i < 4; i++){
			text [8+i] = '.';
			Print(text);
			digitalWrite(ledPin, HIGH);
			delay(50);
			digitalWrite(ledPin, LOW);
			delay(50);
		}
	}

	int IR = 0x20DF10EF;
	Print("Found IR", String(IR));
	delay(3000);

	String name = tp.type();
	if(name.length()<=0 and name.length()>=16){
		return;
	}
	fr.back();
	Serial.print(fr.cur()->name);
	fr.cur()->add(name,send_IR, IR);
}

void send_IR(){
	Serial.print("Sending");
	Serial.print(fr.cur()->name);
	Serial.print(fr.cur()->value);


	IRsend irsend(ir_emi_p);

	irsend.begin();


  	irsend.sendNEC(0x20DF10EF, 32);

	delay(100);
}