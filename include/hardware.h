#pragma once

void toggle_cs(bool is_SD);
int buttons();


const int ledPin = 4;
const int b_pins[4] = {36, 39, 34, 35};  // up, down, left, right
//const int on_off_switch_p = 32;
const unsigned long debounceDelay = 50;
const int radio_rec_p = 5;
const int radio_emi_p = 12;
const int ir_rec_p = 14;
const int ir_emi_p = 2;

const int rfid_rst = 13;

const int rfid_cs = 12;

const int SD_cs_p = 26;

const int SPI_SCK =  18;
const int SPI_MISO = 19;
const int SPI_MOSI = 23;


extern unsigned long lastDebounceTime;
extern bool lastStates[4];
extern bool curStates[4];
extern char push;
extern bool presed;


extern bool on_off;
const gpio_num_t on_off_switch_p = GPIO_NUM_32;
