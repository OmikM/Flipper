using namespace std;
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <Arduino.h>
#include <SD.h>
#include "menu.h"
#include "hardware.h"
#include "display.h"
#include "IR.h"
#include "IR_send.h"
#include "micro_sd.h"


vector<uint16_t> StrToRawVal(String temp) {
	String num = "";
  	vector<uint16_t> res;
	for(int i = 0; i < temp.length(); i++){
		if(temp[i]==' ' or temp[i]=='\n'){
			res.push_back(num.toInt());
			Serial.print(num + ' ');
			num = "";
		}else{
			num += temp[i];
		}
	}
	Serial.print("Done");
	return res;
}

void send_IR(){

	IRsend irsend(ir_emi_p);

	irsend.begin();


	int prot = readFile(SD, (M.path + "/" + M.dir[M.pos] ).c_str())[1].toInt();
	int bits = readFile(SD, (M.path + "/" + M.dir[M.pos] ).c_str())[3].toInt();



	vector<uint16_t> val_raw;
	int val;


	if(prot == 0){
		val_raw = StrToRawVal(readFile(SD, (M.path + "/" + M.dir[M.pos] ).c_str())[2]);
	}else{
		val = readFile(SD, (M.path + "/" + M.dir[M.pos] ).c_str())[2].toInt();
	}

    int adr = readFile(SD, (M.path + "/" + M.dir[M.pos] ).c_str())[4].toInt();

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

  			case 7: // PANASONIC
    			Serial.println("PANASONIC");
    			irsend.sendPanasonic(adr, val);
    			break;

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