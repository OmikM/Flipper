
using namespace std;
#include <Arduino.h>
#include "menu.h"
#include "hardware.h"
#include "display.h"
#include "IR.h"
//#include "type.h"

extern col fr;
//extern Type tp;


void add_ir(){
	digitalWrite(ledPin, HIGH);
	for(int i =0; i < 8; i++){
		Print("Scanning" + '.'*(i%4));
		delay(400);
		digitalWrite(ledPin, LOW);
	}

	//String name = tp.type();

	int IR = 10943;
	Print("Found IR", String(IR));
	delay(3000);
	fr.back();
}