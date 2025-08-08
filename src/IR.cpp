
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

vector<uint16_t> StrToRawVal(String temp) {
	String num;
  	vector<uint16_t> res;
	for(int i = 0; i < temp.length(); i++){
		if(temp[i]==' '){
			res.push_back(num.toInt());
			num = "";
		}else{
			num += temp[i];
		}
	}
	return res;
}


void add_ir(){
	char text[13] = "Scanning    ";
	receiver.enableIRIn();
	int IR;
	int msg_s;
	String prot;
	for(int i = 0; i < 64; i++){
		
		if(receiver.decode(&res)){
			prot = String(res.decode_type);
			Serial.println(res.decode_type);
			Serial.println(prot);


			if(res.decode_type==0 or (int(res.decode_type)>=9 and int(res.decode_type) <= 11) or int(res.decode_type) > 14){
				prot = "0";
				msg_s = res.rawlen;
				String IR_raw = rawValToStr(res);
			}else{
				msg_s = res.bits;
				IR = res.value, HEX;
			}

			
			Serial.println(res.bits);
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

	Print("Found IR", String(IR));

	

	String name = tp.type();
	if(name.length()<=0 and name.length()>=16){
		return;
	}


	String content = String("4\n")+ IR + '\n' + String(prot) + '\n' + msg_s;
	writeFile(SD, (M.path + '/' + name + ".txt" ).c_str() , content.c_str());
}

void send_IR(){

	IRsend irsend(ir_emi_p);

	irsend.begin();


	int prot = readFile(SD, (M.path + "/" + M.dir[M.pos] ).c_str())[2].toInt();
	int bits = readFile(SD, (M.path + "/" + M.dir[M.pos] ).c_str())[3].toInt();


	vector<uint16_t> val_raw;
	if(prot == 0){
		vector<uint16_t> val_raw = StrToRawVal(readFile(SD, (M.path + "/" + M.dir[M.pos] ).c_str())[1]);
	}

	int val = readFile(SD, (M.path + "/" + M.dir[M.pos] ).c_str())[1].toInt();


	for(int i = 0; i < 6; i++){
		switch (prot) {
			case 0:
			    Serial.println("Raw");
				irsend.sendRaw(val_raw.data(), bits, 38);
				break;
  			case 1: // NEC
    			Serial.println("NEC");
    			irsend.sendNEC(val, bits);
    			break;

	  		case 2: // SONY
    			Serial.println("SONY");
    			irsend.sendSony(val, bits);
    			break;

  			case 3: // RC5
    			Serial.println("RC5");
    			irsend.sendRC5(val, bits);
    			break;

			case 4: // RC6
    			Serial.println("RC6");
    			irsend.sendRC6(val, bits);
    			break;

  			case 5: // DISH
    			Serial.println("DISH");
    			irsend.sendDISH(val, bits);
    			break;

  			case 6: // SHARP
    			Serial.println("SHARP");
    			irsend.sendSharp(val, bits);
    			break;

  			// case 7: // PANASONIC
    		// 	Serial.println("PANASONIC");
    		// 	irsend.sendPanasonic(results.address, val);
    		// 	break;

  			case 8: // JVC
    			Serial.println("JVC");
    			irsend.sendJVC(val, bits, false); // no repeat
    			break;


  			case 12: // LG
    			Serial.println("LG");
    			irsend.sendLG(val, bits);
    			break;

  			case 13: // WHYNTER
    			Serial.println("WHYNTER");
    			irsend.sendWhynter(val, bits);
    			break;

  			case 14: // AIWA_RC_T501
    			Serial.println("AIWA_RC_T501");
    			irsend.sendAiwaRCT501(val);
    			break;

  			default:
    			Serial.println("Protocol not supported");
    			break;
		}
		delay(50);
	}
}