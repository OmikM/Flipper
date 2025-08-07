#include <Arduino.h>
#include <SD.h>
#include <vector>
using namespace std;
#include "menu.h"
#include "display.h"
#include "IR.h"
#include "radio.h"
#include "rfid.h"
#include "micro_sd.h"


col M;

void funct_wrapper(int f_id){
    if(f_id==1) add_ir();
    if(f_id==2) read_RFID(); 
    if(f_id==3) add_radio(); 
    if(f_id==4) send_IR();
    if(f_id==5) send_radio();

}


void col::Print_out() {
    String l1, l2;
    dir = listDir(SD, path.c_str(), 0);
    if (dir.size() > 0) {
        l1 = dir[pos];
    }
    if (dir.size() > 1) {
        l2 = dir[(pos + 1) % dir.size()];
    }
    Print(l1, l2);
}

void col::scroll(bool up) {
    pos = (dir.size() + pos + (up ? -1 : 1)) % dir.size();
}

void col::add(String n, void (*f)(), int v) {
    col temp;
    temp.name = n;
    temp.func = f;
    temp.value = v;
    cols.push_back(temp);
}


void col::back() {
    Serial.println(path);
    if(path == "/M") return;
    int i;
    for(i = path.length()-1; i > 0; i--){
        if(path[i]=='/'){
            break;
        }
    }

    String temp = path.substring(i+1, path.length());    
    path = path.substring(0, i);
    dir = listDir(SD, path.c_str(), 0);
    Serial.println(path);
    Serial.println(temp);

    for(pos = 0; pos < 1000; pos++){
        if(dir[pos]== temp) break;
    }
}

void col::next() {
    String f = path + '/' + dir[pos] ;
    if (is_dir(SD,f.c_str())){
        pos = 0;
        path = f;
        dir = listDir(SD, path.c_str(), 0);
        
    }else{
        int func_id = readFile(SD, f.c_str())[0].toInt();
        funct_wrapper(func_id);
    }
    Serial.println(path);
}