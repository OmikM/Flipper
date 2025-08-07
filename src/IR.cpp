
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


//extern col fr;


extern Type tp;


void add_ir(){
	char text[13] = "Scanning    ";
	receiver.enableIRIn();
	int IR;
	String prot;
	for(int i = 0; i < 64; i++){
		
		if(receiver.decode(&res)){
			String prot = String(res.decode_type);
	        IR = res.value, HEX;
        	receiver.resume();
			break;
    	}
		if(i%16==0)
		{
			char texct[13] = "Scanning    ";
			Print(text);
		}else if(i%4==0){
			text[7+((i%16)/4)] = '.';
			Serial.println(text);
			Print(text);
		}	
		delay(50);
	}

	Print("Found IR", String(IR));

	

	String name = tp.type();
	if(name.length()<=0 and name.length()>=16){
		return;
	}

	String content = String("4\n")+ IR + '\n' + prot;
	Serial.println("\n"+prot);
	writeFile(SD, (M.path + '/' + name + ".txt").c_str() , content.c_str());
}

void send_IR(){
	Serial.print("Sending");

	IRsend irsend(ir_emi_p);

	irsend.begin();

	String prot = readFile(SD, (M.path + "/" + M.dir[M.pos] + ".txt").c_str())[2];
	int val = readFile(SD, (M.path + "/" + M.dir[M.pos] + ".txt").c_str())[1].toInt();

	for(int i = 0; i < 6; i++){
		if(prot=="NEC") irsend.sendNEC(val, 32);
		delay(50);
	}
}