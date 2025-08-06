
using namespace std;
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <IRrecv.h>
#include <Arduino.h>
#include <SD.h>
#include "menu.h"
#include "hardware.h"
#include "display.h"
#include "IR.h"
#include "type.h"
#include "micro_sd.h"

IRrecv receiver(ir_rec_p);
decode_results res;


extern col fr;


extern Type tp;


void add_ir(){
	char text[13] = "Scanning    ";
	receiver.enableIRIn();
	int IR;
	for(int i = 0; i < 64; i++){
		
		if(receiver.decode(&res)){
	        IR = res.value, HEX;
        	receiver.resume();
			break;
    	}
		if(i%16==0)
		{
			char text[13] = "Scanning    ";
			Print(text);
		}else if(i%4==0){
			text[7+((i%16)/4)] = '.';
			Serial.println(text);
			Print(text);
		}	
		delay(100);
	}

	Print("Found IR", String(IR));
	writeFile(SD, "/hello.txt", "Hello ");
	delay(3000);
	readFile(SD, "/hello.txt");

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

	for(int i = 0; i < 6; i++){
  		irsend.sendNEC(fr.cur()->value, 32);
		delay(50);
	}
}