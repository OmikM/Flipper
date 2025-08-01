using namespace std;
#include <Arduino.h>
#include "menu.h"
#include "hardware.h"
#include "display.h"
#include "rfid.h"
#include "type.h"
#include <SPI.h>
#include <MFRC522.h>


MFRC522 rc522(rfid_sda, rfid_rst);


void init_RFID(){
    Serial.print("initialized");
    SPI.begin();
    rc522.PCD_Init();
}

void read_RFID(){



    Serial.print("Reading ...");
    while (true){
        if (!rc522.PICC_IsNewCardPresent()) {
            continue;
        }



    // Select one of the cards
        if (!rc522.PICC_ReadCardSerial()) {
            continue;
        }

    // Show UID
        Serial.print("Card UID: ");
        for (byte i = 0; i < rc522.uid.size; i++) {
            Serial.print(rc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
            Serial.print(rc522.uid.uidByte[i], HEX);
        }
        Serial.println();

  // Halt PICC
        rc522.PICC_HaltA();
        rc522.PCD_StopCrypto1();
    }

    delay(50);

}

