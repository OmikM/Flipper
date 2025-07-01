#include <StandardCplusplus.h>
#include <Arduino.h>
#include <vector>
#include <functional>
#include <String>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <unistd.h>
using namespace std;
//

const int b_pins[4] = {2,3,4,5}; //u,d,l,r
unsigned long debounceDelay = 50;
unsigned long lastDebounceTime = 0;
const int ledPin = 8;

bool lastStates[4] = {0};
bool curStates[4] = {0};

char push = '0';
LiquidCrystal_I2C lcd(0x27,20,4);

int min(int a,int b){
  if(a>b)return b;
  return a;
}

void Print(String l1, String l2 = ""){
	lcd.clear();
  	lcd.print(l1);
	lcd.setCursor(0,1);
  	lcd.print(l2);


}


class col {
	public:
		int is_in = false;
    	int pos = 0;
		vector<col> cols;
		String name;
		void (*func)();

    	String l1, l2;

		void mcol(String n, void (*f)()){
			name = n;
			func =  f;
		}

    	void Print_out(){
			if(cols.size()>0){
	      l1 = cols[pos].name;
			}
			if(cols.size()>1){
        l2 = cols[(pos+1)%(cols.size())].name;
			}
			Print(l1,l2);
    	}	

		  void scroll(bool up){
  			pos = (cols.size()+pos +(up*2-1)*-1)%cols.size();
		  }
		  void add(String n, void (*f)() = NULL){
			  col temp;
			  temp.mcol(n,f);
			  cols.push_back(temp);
		  }

		col *cur(){
			//if par retrurns parent
	  		if(is_in){
				if(cols.size()>0){
  					return cols[pos].cur();
				  }
				func();
			}
  			return this;
		  }

		void back(){
			Serial.println(String(name));
			if(cols.size()==0 or !cols[pos].is_in){
				is_in = 0;
			}else{
				cols[pos].back();
			}
		}

		void next(){
			if(cols[pos].cols.size())
				is_in = true;
			if(cols[pos].func){
				cols[pos].func();
			}
		}
};

col fr;



void add_ir(){
	digitalWrite(ledPin, HIGH);
	for(int i =0; i < 8; i++){
		Print("Scanning" + '.'*(i%4));
		delay(400);
		digitalWrite(ledPin, LOW);
	}

	int IR = 10943;
	Print("Found IR", String(IR));
	delay(3000);
	fr.back();


}

void setup(){
  	Serial.begin(115200);
	pinMode(ledPin, OUTPUT);

  	fr.mcol("fr", 0);

	for(int i = 0; i < 4; i++){
		pinMode(b_pins[i], INPUT);
	}
	

	lcd.init();
	lcd.backlight();


	fr.add("NFC");
	fr.add("IR");
	fr.cols[1].add("Add_IR", add_ir);
	fr.cols[1].cols[0].add("Scanning ...");
	fr.add("RF");
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