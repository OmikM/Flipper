#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "display.h"
#include "menu.h"
using namespace std;

// &
byte enter[8] = {
B00000,
B00001,
B00101,
B01001,
B11111,
B01000,
B00100,
B00000
};

// `
byte space[8] = {
B00000,
B00000,
B00000,
B00000,
B00000,
B00000,
B10001,
B11111
};
// /
byte big[8] = {
B00000,
B00100,
B01010,
B10001,
B01010,
B01010,
B01110,
B00000
};
//@
byte small[8] = {
B00000,
B01110,
B01010,
B01010,
B10001,
B01010,
B00100,
B00000
};
// {
byte del[8] = {
  B00000,
  B10001,
  B01010,
  B00100,
  B01010,
  B10001,
  B00000,
  B00000
};

byte hx[8]{
  B00000,
  B00000,
  B10111,
  B10100,
  B10111,
  B10101,
  B10101,
  B10111
};


LiquidCrystal_I2C lcd(0x27, 20, 4);

void initDisplay() {
    lcd.init();
    lcd.backlight();
    lcd.createChar(0, enter);
    lcd.createChar(1, space);
    lcd.createChar(2, big);
    lcd.createChar(3, small);
    lcd.createChar(4, del);
    lcd.createChar(5, hx);
}

String nopref(String s){
    if(isDigit(s[0])){
        return s.substring(4);
    }
    return s;
}

void Print(String l1, String l2, bool row) {
    
    if(row){
        l1 = l2;
    }else{
        lcd.clear();
    }

    l1 = nopref(l1);

    lcd.setCursor(0, row);
    for (int i = 0; i < l1.length(); i++) {
        if (l1[i] == '&') {lcd.write(byte(0));
        }else if (l1[i] == '`') {lcd.write(byte(1));
        }else if (l1[i] == '/') {lcd.write(byte(2)); 
        }else if (l1[i] == '@') {lcd.write(byte(3));
        }else if (l1[i] == '{') {lcd.write(byte(4));
        }else if (l1[i] == '~') {lcd.write(byte(5));
        }else {lcd.print(l1[i]);}
    }

    if(row == 0){
        Print(l1,l2,1);
    }
    
}