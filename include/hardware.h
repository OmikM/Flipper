#pragma once

const int ledPin = 4;
const int b_pins[4] = {33, 25, 26, 27};  // up, down, left, right
//const int on_off_switch_p = 32;
const unsigned long debounceDelay = 50;
const int radio_rec_p = 5;
const int radio_emi_p = 12;
const int ir_rec_p = 14;
const int ir_emi_p = 2;

const int rfid_rst = 13;
const int rfid_sda = 12;



extern unsigned long lastDebounceTime;
extern bool lastStates[4];
extern bool curStates[4];
extern char push;

