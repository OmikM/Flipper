#include "display.h"
#include "menu.h"
using namespace std;


LiquidCrystal_I2C lcd(0x27, 20, 4);

void initDisplay() {
    lcd.init();
    lcd.backlight();
}

void Print(String l1, String l2) {
    lcd.clear();
    lcd.print(l1);
    lcd.setCursor(0, 1);
    lcd.print(l2);
}