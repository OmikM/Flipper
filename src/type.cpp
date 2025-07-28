#include <Arduino.h>
#include "type.h"
#include "display.h"
#include "hardware.h"
using namespace std;


Type tp;
//extern Type tp;


void Type::cp(const char a[2][17]){
  for(short i = 0; i < 2; i++){
    for(short j = 0; j < 17; j++){
        disp[i][j] = a[i][j];
    }
  }
}

void Type::typeInit(){
    cp(lets);
}


String Type::type(){
    String typed ="";
    short r = 0;
    short c = 8;
    int i =0;
    bool is_lets = 1;
    while (true){
        i++;
        if(i%2){
            disp[r][c] = '_';
        }else{
            if(!is_lets)cp(big);
            else if(is_big)cp(big);
            else cp(lets);
        }
        Print(String(disp[0]), String(disp[1]));

        bool pressed;
	    pressed = false;
	    short pressed_ind = -1;
  	    delay(200);

        char ch;
	
	
	    unsigned long time = millis();

	    for(short i = 0; i < 4; i++){
    		curStates[i] = digitalRead(b_pins[i]);
    	}

    	for (short i = 0; i < 4; i++) {
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
        }

        for (short i = 0; i < 4; i++) {
            lastStates[i] = curStates[i];
        }


        if(pressed_ind==0 or pressed_ind==1){
              if(r==1 and pressed_ind==0){
                r--;
                ch = disp[r][c];
            }else if(r==0 and pressed_ind==1){
                r++;
                ch = disp[r][c];
            }else{
                //function buttons
                if(c==8 and r==0){
                    typed.remove(typed.length()-1,1);
                }

                else if(c==7 and r==1){
                    is_lets = !is_lets;
                }

                else if(c==6 and r==1){
                    if(is_big)is_big=false;
                    else is_big=true;
                    is_lets = true;
                }

                else if(c==8 and r==1)return typed;

                else{
                    typed += ch;
                }
        }
        }
        if(pressed_ind==2){
            if(c==0)c= 15;
            else c-=1;
            ch = disp[r][c];
        }
        if(pressed_ind==3){
            if(c==15) c=0;
            else c++;
            ch = disp[r][c];
        }
  }  
}