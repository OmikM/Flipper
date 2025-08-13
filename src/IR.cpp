
using namespace std;
#include <IRremoteESP8266.h>
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


String rawValToStr(decode_results res) {
  String output = "";

  for (uint16_t i = 0; i < res.rawlen; i++) {
    unsigned int duration = res.rawbuf[i];

    output += String(duration);
    
    if (i < res.rawlen - 1) {
      output += " ";
    }
  }

  return output;
}




void add_ir(){
	char text[13] = "Scanning    ";
	receiver.enableIRIn();
	int IR;
	int msg_s;
	int adr = 0;
	String prot = "-1";
	String IR_raw;
	for(int i = 0; i < 96; i++){
		
		if(receiver.decode(&res)){
			prot = String(res.decode_type);
			Serial.println(res.decode_type);
			Serial.println(prot);

			if(res.decode_type==0 or (res.decode_type>=9 and res.decode_type <= 11) or res.decode_type > 14){
				prot = "0";
				msg_s = res.rawlen;
				String IR_raw = rawValToStr(res);
			}else{
				msg_s = res.bits;
				IR = res.value, HEX;
				adr = res.address, HEX;
			}

			
			Serial.println(res.bits);
			Print("Found");
			delay(1000);
        	receiver.resume();
			break;
    	}
		if(i%16==0)
		{
			strcpy(text, "Scanning    ");
		}else if(i%4==0){
			text[7+((i%16)/4)] = '.';
			Serial.println(text);
			Print(text);
		}
		delay(50);
	}
	if(prot == "-1"){
		Print("Not Found");
		delay(1000);
		return;
	}

	Print("Found IR", String(IR));

	

	String name = tp.type();
	if(name.length()<=0){return;}
	if(name.length()>=16){
		name = name.substring(0, 15);
	}


	String content = String("4\n");

	content += String(prot) + '\n';
	if(prot=="0"){
		content += IR_raw + '\n';
	}else{
		content += String(IR) + '\n';
	}
	content += String(msg_s) + '\n';
	content += String(adr);

	Serial.print(content);

	writeFile(SD, (M.path + '/' + name + ".txt").c_str() , content.c_str());
}

