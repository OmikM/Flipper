
using namespace std;
#include <Arduino.h>
#include "menu.h"
#include "hardware.h"
#include "display.h"
#include "radio.h"
#include "type.h"
#include <RCSwitch.h>

extern col fr;
extern Type tp;

RCSwitch rf_rec = RCSwitch();
RCSwitch rf_emi = RCSwitch();



void radio_init(){
    
    rf_emi.enableTransmit(radio_emi_p);
}

void add_radio(){
    rf_rec.enableReceive(radio_rec_p);
	char text[13] = "Scanning";
    Print(text);
    int value = 0;
    if (rf_rec.available()) {
        Serial.println("trying");
        value = rf_rec.getReceivedValue();

        if (value == 0) {
            Serial.println("Unknown encoding");
        } else {
            Serial.print("Received ");
            Serial.print(value);
            Serial.print(" / Bit length: ");
            Serial.println(rf_rec.getReceivedBitlength());
        }

        rf_rec.resetAvailable();
    }
	Print("Found Radio", String(value));
	delay(3000);

	String name = tp.type();
	if(name.length()<=0 and name.length()>=16){
		return;
	}
	Serial.print(fr.cur()->name);
	fr.cur()->add(name,send_radio, value);
}

void send_radio(){
    fr.cur()->next();
    rf_emi.send(fr.cur()->value, 24);
    Serial.println("Sent: " + fr.cur()->name + fr.cur()->value);


    fr.cur()->back();

	delay(100);
}