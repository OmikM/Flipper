#include <Arduino.h>
#include "type.h"
#include "display.h"
#include "hardware.h"
using namespace std;


Type tp;
//extern Type tp;



char char_to_hex(char lt1) {
    if(lt1 <= '9'){
        return lt1 - '0';
    }
    if (lt1 >= 'a' and lt1 <= 'z') {
        lt1 -= 32;
    }
    return lt1 - 'A' + 10;
}

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
    char ch;
    short pressed_ind = -1;

    while (true){
        i++;
        
        if(i%2){
            disp[r][c] = '_';
        }else{
            if(!is_lets)cp(nums);
            else if(is_big)cp(big);
            else cp(lets);
        }
        Print(String(disp[0]), String(disp[1]));

        

        pressed_ind = buttons();

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

                // byte
                else if(c==6 and r==0 and typed.length()>=2){
                    char temp = 16*char_to_hex(typed[typed.length()-2]) + char_to_hex(typed[typed.length()-1]);
                    typed = typed.substring(0, typed.length() - 2);
                    typed += temp;
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