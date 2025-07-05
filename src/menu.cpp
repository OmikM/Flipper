#include "menu.h"
#include "display.h"
#include <Arduino.h>
#include "IR.h"

col fr;

void col::initMenu(){
    fr.add("NFC");
	fr.add("IR");
	fr.cols[1].add("Add_IR", add_ir);
	fr.cols[1].cols[0].add("Scanning ...");
	fr.add("RF");
}

void col::mcol(String n, void (*f)()) {
    name = n;
    func = f;
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

void col::add(String n, void (*f)()) {
    col temp;
    temp.mcol(n, f);
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