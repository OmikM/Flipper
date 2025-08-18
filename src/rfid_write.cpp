using namespace std;
#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include <MFRC522.h>

#include "menu.h"
#include "hardware.h"
#include "display.h"
#include "rfid.h"
#include "type.h"
#include "micro_sd.h"

void NFC::error(String msg){
    Print("Failed",msg);
    delay(1000);
    Serial.print(msg);
    Serial.println();
    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();  
    toggle_cs(1);
}

bool NFC::write(MFRC522::MIFARE_Key *key, String name, byte dataBlock[16], int blockAddr){


    Serial.print(F("Writing data into block ")); Serial.print(blockAddr);   

    status = (MFRC522::StatusCode) mfrc522.MIFARE_Write(blockAddr, dataBlock, 16);
    if (status != MFRC522::STATUS_OK) {
        return false;
    }

    String f_o = M.path + '/' + M.dir[M.pos];
    String f_n = M.path + '/' + M.dir[M.pos].substring(0,4) + name.substring(0,16) + ".txt";
    renameFile(SD, f_o.c_str(), f_n.c_str());
    return true;

}

void NFC::write_rfid(){
    toggle_cs(0);

    String name = tp.type();
	if(name.length()<=0){return;}
	if(name.length()>=16){
		name = name.substring(0, 16);
    }else{
        int temp = 16 - name.length();
        for(int i = 0; i < temp; i++){
            name += '_';
            Serial.println(name + String(i));
        }
    }

    int blockAddr = M.dir[M.pos].substring(0,3).toInt();

    //not writable
    if(blockAddr<=4 or blockAddr%4==0 or blockAddr%4==3){
        Print("Invalid block", String(blockAddr));
        delay(1000);
        Serial.print("invalid block");
        return;
    }

    byte dataBlock[16];
    for(int i = 0; i < 16; i++){
        if(name[i]=='_') dataBlock[i]=0;
        else dataBlock[i] = byte(name[i]);
    }


    Serial.print("Writing ...");
    while (true){
        if (!mfrc522.PICC_IsNewCardPresent()) {
            continue;
        }
        Serial.print("Detected");
        
        if (mfrc522.PICC_ReadCardSerial()) {

            break;
        }
        delay(50);
    }

    bool ok = false;

    MFRC522::MIFARE_Key key;
    for (byte k = 0; k < NR_KNOWN_KEYS; k++) {
        for (byte i = 0; i < MFRC522::MF_KEY_SIZE; i++) {
            key.keyByte[i] = knownKeys[k][i];
        }

        status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, blockAddr, &key, &(mfrc522.uid));
        if (status == MFRC522::STATUS_OK){
            ok = write(&key, name, dataBlock, blockAddr);
            if(ok)break;
        }

        status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_B, blockAddr, &key, &(mfrc522.uid));
        if (status == MFRC522::STATUS_OK){
            ok = write(&key, name, dataBlock, blockAddr);
            if(ok)break;
        }


    }

    if(!ok)return error("Authentication failed");



    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();  
    toggle_cs(1);
}