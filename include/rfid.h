#pragma once
#include <MFRC522.h>
#include <Arduino.h>
#include <vector>
#include <hardware.h>
using namespace std;


class NFC {
private:
    byte buffer[18];
    byte block;
    byte waarde[64][16];
    MFRC522::StatusCode status;
    char choice;
    void setup_sectors();
    
    MFRC522::MIFARE_Key key;
public:
    MFRC522 mfrc522;
    const int NR_KNOWN_KEYS = 8;
    static const byte knownKeys[8][MFRC522::MF_KEY_SIZE];

    NFC(byte csPin, byte rstPin) : mfrc522(csPin, rstPin) {}

    void init_RFID();
    void read_RFID();

    void start();
    bool try_key(MFRC522::MIFARE_Key *key);
};
extern NFC N;