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


// Known keys, see: https://code.google.com/p/mfcuk/wiki/MifareClassicDefaultKeys

NFC N(rfid_cs, rfid_rst);

const byte NFC::knownKeys[8][MFRC522::MF_KEY_SIZE] = {
    {0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
    {0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5},
    {0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xb5},
    {0x4d, 0x3a, 0x99, 0xc3, 0x51, 0xdd},
    {0x1a, 0x98, 0x2c, 0x7e, 0x45, 0x9a},
    {0xd3, 0xf7, 0xd3, 0xf7, 0xd3, 0xf7},
    {0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
};


void NFC::init_RFID(){
    toggle_cs(0);
    mfrc522.PCD_Init();


    Serial.print("initialized");

    for (byte i = 0; i < 6; i++) {
        key.keyByte[i] = 0xFF;
    }

}

void NFC::read_RFID(){

    toggle_cs(0);


    Serial.print("Reading ...");
    while (true){
        if(buttons()==2){
			return;
		}
        if (!mfrc522.PICC_IsNewCardPresent()) {
            continue;
        }
        Serial.print("Detected");
        
        if (mfrc522.PICC_ReadCardSerial()) {

            break;
        }
        delay(50);
    }

    Serial.print("Card UID: ");
    for (byte i = 0; i < mfrc522.uid.size; i++) {
        Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
        Serial.print(mfrc522.uid.uidByte[i], HEX);
    }

    Serial.print(F("PICC type: "));
    MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
    Serial.println(mfrc522.PICC_GetTypeName(piccType));
    
    // Try the known default keys
    MFRC522::MIFARE_Key key;
    for (byte k = 0; k < NR_KNOWN_KEYS; k++) {
        // Copy the known key into the MIFARE_Key structure
        for (byte i = 0; i < MFRC522::MF_KEY_SIZE; i++) {
            key.keyByte[i] = knownKeys[k][i];
        }
        // Try the key
        if (try_key(&key)) {
            // Found and reported on the key and block,
            // no need to try other keys for this PICC
            break;
        }
    }

    M.dir = listDir(SD, M.path.c_str(), 0);


    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();
    toggle_cs(1);
}
    

 
void dump_byte_array(byte *buffer, byte bufferSize) {
    for (byte i = 0; i < bufferSize; i++) {
        Serial.print(buffer[i] < 0x10 ? " 0" : " ");
        Serial.print(buffer[i], HEX);
    }
}


void NFC::setup_sectors() {
    M.path = (M.path + "/temp");
    createDir(SD, M.path.c_str());
    M.pos = 0;
    String block_path;
    String num;
    String sec_path;
    String sec_r_path;
    
    for(int sect_r = 0; sect_r < 4; sect_r++){
        sec_r_path = M.path + "/Sectors_" + String((sect_r*4)) + "-" + String((sect_r*4+3));
        createDir(SD, sec_r_path.c_str());

        for(int sect = sect_r*4; sect<(sect_r*4)+4; sect++){
            sec_path = sec_r_path + "/Sector_" + String(sect);
            //Serial.println(sec_path);
            createDir(SD, sec_path.c_str());

            for(int i = 0; i < 4; i++){
                num = "0";
                if((sect*4)+i>=10)num += String((sect*4)+i);
                else num += '0'+String((sect*4)+i);

                block_path = sec_path + "/" + num + '_';

                for(int j = 0; j < 16; j++){
                    if(waarde[(sect*4)+i][j]==0){block_path += '_';}
                    else if(waarde[(sect*4)+i][j]>=33 and waarde[(sect*4)+i][j]<=126){
                        block_path += char(waarde[(sect*4)+i][j]);
                    }else{
                        block_path += '#';
                    }
                }
            
                writeFile(SD, (block_path+".txt").c_str() , "7");
            }
        }
    }

    M.dir = listDir(SD, M.path.c_str(), 0);

}


 
bool NFC::try_key(MFRC522::MIFARE_Key *key)
{
    bool result = false;
    
    for(byte block = 0; block < 64; block++){
      
    status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, key, &(mfrc522.uid));
    if (status != MFRC522::STATUS_OK) {

        return false;
    }

    // Read block
    byte byteCount = sizeof(buffer);
    status = mfrc522.MIFARE_Read(block, buffer, &byteCount);
    if (status != MFRC522::STATUS_OK) {
        Serial.print(F("MIFARE_Read() failed: "));
        Serial.println(mfrc522.GetStatusCodeName(status));
    }
    else {
        // Successful read
        // Serial.print(F("Success with key:"));
        // //dump_byte_array((*key).keyByte, MFRC522::MF_KEY_SIZE);
        // Serial.println();
        
        // Dump block data
        Serial.print(F("Block ")); Serial.print(block); Serial.print(F(":"));
        Serial.println();

        
        for (int p = 0; p < 16; p++) //De 16 bits uit de block uitlezen
        {
          waarde [block][p] = buffer[p];
          Serial.print(waarde[block][p]);
          Serial.print(" ");
        }
        }
        result = true;
    }
    setup_sectors();
    
   
    mfrc522.PICC_HaltA();       // Halt PICC
    mfrc522.PCD_StopCrypto1();  // Stop encryption on PCD
    return result;
}
