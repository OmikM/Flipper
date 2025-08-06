#pragma once
#include <MFRC522.h>



void init_RFID();
void read_RFID();

void start();
bool try_key(MFRC522::MIFARE_Key *key);