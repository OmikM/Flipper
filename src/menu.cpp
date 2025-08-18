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
#include "IR_send.h"



col M;


void funct_wrapper(int f_id){
    if(f_id==1) add_ir();
    if(f_id==2) N.read_RFID();
    if(f_id==3) add_radio(); 
    if(f_id==4) send_IR();
    if(f_id==5) send_radio();
    if(f_id==6){
        M.del_file = !M.del_file;
        Serial.println(M.del_file);
    }
    if(f_id==7) N.write_rfid();

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


    for(pos = 0; pos < 1000; pos++){
        if(dir[pos]== temp) break;
    }
}

void col::next() {
    String f = path + '/' + dir[pos];
    int func_id;
    if (is_dir(SD,f.c_str())){
        pos = 0;
        path = f;
    }else{
        func_id = readFile(SD, f.c_str())[0].toInt();

        if (del_file and func_id!=6){
            deleteFile(SD, f.c_str());
            del_file = false;
            dir = listDir(SD, path.c_str(), 0);
            return;
        }

        funct_wrapper(func_id);
    }
    dir = listDir(SD, path.c_str(), 0);
}