#include "menu.h"
#include "display.h"
#include <Arduino.h>
using namespace std;

#include "IR.h"
#include "radio.h"

col fr;

void col::initMenu(){
    fr.add("NFC");
	fr.add("IR");
	fr.cols[1].add("Add_IR", add_ir);
	fr.cols[1].cols[0].add("Scanning ...");
	fr.add("RF");
    fr.cols[2].add("Custom");
    fr.cols[2].cols[0].add("Add_RF", add_radio);
    fr.cols[2].add("Dict");

}

void col::Print_out() {
    if (cols.size() > 0) {
        l1 = cols[pos].name;
    }
    if (cols.size() > 1) {
        l2 = cols[(pos + 1) % cols.size()].name;
    }
    Print(l1, l2);
}

void col::scroll(bool up) {
    pos = (cols.size() + pos + (up ? -1 : 1)) % cols.size();
}

void col::add(String n, void (*f)(), int v) {
    col temp;
    temp.name = n;
    temp.func = f;
    temp.value = v;
    cols.push_back(temp);
}

col *col::cur() {
    if (is_in) {
        if (cols.size() > 0) {
            return cols[pos].cur();
        }
        if (func) func();
    }
    return this;
}

void col::back() {
    Serial.println(String(name));
    if (cols.size() == 0 || !cols[pos].is_in) {
        is_in = 0;
    } else {
        cols[pos].back();
    }
}

void col::next() {
    if (cols[pos].cols.size())
        is_in = true;
    if (cols[pos].func) {
        cols[pos].func();
    }
}