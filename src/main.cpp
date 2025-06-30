#include <StandardCplusplus.h>
#include <Arduino.h>
#include <vector>
#include <functional>
#include <String>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
//sleep
#include <unistd.h>
using namespace std;

const int b_u = 2;
const int b_d = 3;
const int b_l = 4;
const int b_r = 5;
char push = '0';
LiquidCrystal_I2C lcd(0x27,20,4);

int min(int a,int b){
  if(a>b)return b;
  return a;
}

void Print(String l1, String l2 = ""){
	lcd.setCursor(0,0);
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
  			if(is_in){
				  if(cols.size()>0)
  					return cols[pos].cur();
				  func();
			  }
			  else{
  				return this;
			  }
		  }

		void next(){
			if(cols[pos].cols.size())
				is_in = true;
			if(cols[pos].func){
				cols[pos].func();
			}
		}
		
		void back(){
			is_in = false;
		}

};

col fr;

void add_ir(){
	Print("Scanning");
	int IR = 10943;

}

void setup(){
  Serial.begin(115200);
  delay(100);

  fr.mcol("fr", 0);

	pinMode(b_u, INPUT);
	pinMode(b_d, INPUT);
	pinMode(b_l, INPUT);
	pinMode(b_r, INPUT);

	lcd.init();
	lcd.backlight();


	fr.add("NFC");
	fr.add("IR");
	fr.cols[1].add("Add_IR", add_ir);
	fr.cols[1].cols[0].add("Scanning ...");
	fr.add("RF");
}

void up(){
	//fr.cur()->scroll(1);
	Serial.println('u');
}
void down(){
	//fr.cur()->scroll(0);
  Serial.println('d');
}
void left(){
	//fr.cur()->back();
  Serial.println('l');
}
void right(){
  Serial.println('r');
	//fr.cur()->next();
}


void loop() {
  delay(1000);
	Serial.println(". ");
  fr.cur()->Print_out();
	
	if(push == '0'){
    if (digitalRead(b_u) == HIGH)push = 'u';
    else if (digitalRead(b_d) == HIGH)push = 'd';
    else if (digitalRead(b_l) == HIGH)push = 'l';
    else if (digitalRead(b_r) == HIGH)push = 'r';

  }else{
    char temp = '0';
		if(push=='w' and digitalRead(b_u)==LOW)up();
		else if(push=='s' and digitalRead(b_d)==LOW)down();
		else if(push=='a' and digitalRead(b_l)==LOW)left();
		else if(push=='d' and digitalRead(b_r)==LOW)right();
		else{
    	temp = push;
		}
      push = temp;
    }
}