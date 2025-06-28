#include <StandardCplusplus.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <string>
#include <vector>

using namespace std;

LiquidCrystal_I2C lcd(0x27, 20, 4);

bool last = 0;
bool b1_v = 0;
string l1 = "";
string l2 = "";

class col {
public:
  int is_in = false;
  int pos = 0;
  vector<col> cols;
  string name;
  int function;

  void mcol(string n, int f) {
    name = n;
    function = f;
  }

  void Print() {
    if (cols.size() > 0) {
      l1 = cols[pos].name;
    }
    if (cols.size() > 1) {
      l2 = cols[(pos + 1) % (cols.size())].name;
    }
  }
  void scroll(bool up) {
    pos = (cols.size() + pos + (up * 2 - 1) * -1) % cols.size();
  }
  void add(string n, int f = 0) {
    col temp;
    temp.mcol(n, f);
    cols.push_back(temp);
  }
};

col front;

int main() {

  front.mcol("front", 0);
  setup();
  front.Print();
  front.scroll(1);
  front.Print();


  return 0;
}

// void cout(string s1, string s2 = ""){
//   char t;
//   lcd.setCursor(0, 0);
//   for(int i = 0; i < s1.size(); i++){
//     t =s1[i];
//     lcd.print(t);
//   }
//   lcd.setCursor(0, 1);
//   for(int i = 0; i < s2.size(); i++){
//     t =s2[i];
//     lcd.print(t);
//   }
// }


void setup() {
  lcd.init();
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  pinMode(2, INPUT_PULLUP);

  front.add("NFC");
  front.add("IR");
  front.add("RF");
}



void loop() {
  delay(100);

  b1_v = digitalRead(2);


  if (b1_v == 1 and last == 0) {
    front.scroll(1);
    lcd.clear();
    // cout(l1,l2);
  }
  last = b1_v;
}