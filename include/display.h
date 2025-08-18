#pragma once
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

extern LiquidCrystal_I2C lcd;

void initDisplay();
void Print(String l1, String l2 = "", bool row = false);

void error(String msg);