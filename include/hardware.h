#pragma once

const int ledPin = 4;
const int b_pins[4] = {33, 25, 26, 27};  // up, down, left, right
//const int on_off_switch_p = 32;
const unsigned long debounceDelay = 50;
const int radio_rec_p = 18;
const int radio_emi_p = 12;
//const int ir_rec_p = ;
const int ir_emi_p = 19;


extern unsigned long lastDebounceTime;
extern bool lastStates[4];
extern bool curStates[4];
extern char push;

