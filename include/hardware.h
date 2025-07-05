#pragma once

const int ledPin = 8;
const int b_pins[4] = {2, 3, 4, 5};  // up, down, left, right
const unsigned long debounceDelay = 50;

extern unsigned long lastDebounceTime;
extern bool lastStates[4];
extern bool curStates[4];
extern char push;