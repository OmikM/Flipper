#include <SPI.h>
#include <FS.h>
#include <SD.h>
#include <Arduino.h>
#include <vector>
#include "hardware.h"
#include "micro_sd.h"

using namespace std;


void writeFile(fs::FS &fs, const char * path, const char * message){

  Serial.printf("Writing file: %s\n", path);

  File file = fs.open(path, FILE_WRITE);
  if(!file){
    Serial.println("Failed to open file for writing");
    return;
  }
  if(file.print(message)){
    Serial.println("File written");
  } else {
    Serial.println("Write failed");
  }
  file.close();
}


vector<String> readFile(fs::FS &fs, const char * path){
  vector<String> res;
  String word = ""; 


  File file = fs.open(path);
  if(!file){
    return res;
  }

  
  while(file.available()){
    char c = file.read();
    if(c=='\n'){
      res.push_back(word);
      word = "";
    }else{
      word += c;
    }
  }
  res.push_back(word);
  file.close();
  return res;
}


vector<String> listDir(fs::FS &fs, const char * dirname, uint8_t levels = 0){
  vector<String> res;
  

  File root = fs.open(dirname);
  if(!root){
    Serial.println("Failed to open directory");
    return res;
  }
  if(!root.isDirectory()){
    Serial.println("Not a directory");
    return res;
  }

  File file = root.openNextFile();
  while(file){
    if(file.isDirectory()){
      String name = file.name();
      Serial.println(name.substring(name.length() - 4));
      if(name.substring(name.length() - 4)==String("temp")){
        Serial.print("___" + String(file.name()));
        removeDir(SD, (dirname+String("/temp")).c_str());
      }

      res.push_back(name);
      if(levels){
        listDir(fs, file.name(), levels -1);
      }
    } else {
      res.push_back(file.name());
    }
    file = root.openNextFile();
  }
  return res;
}


void removeDir(fs::FS &fs, const char * path){
  Serial.println(path);
  File root = fs.open(path);

  Serial.printf("Removing Dir: %s\n", path);
  File file = root.openNextFile();
    while (file) {
        String filePath = String(path) + '/' + String(file.name());
        if (file.isDirectory()) {
          removeDir(fs, filePath.c_str());
        } else {
            // Delete file
            if (!fs.remove(filePath)) {
                Serial.println(filePath);
                Serial.printf("Failed to remove file: %s\n", filePath.c_str());
            }
        }
        file = root.openNextFile();
    }

    // Finally, remove the empty folder
    if (!fs.rmdir(path)) {
        Serial.printf("Failed to remove directory: %s\n", path);
    }
}



void createDir(fs::FS &fs, const char * path){
  Serial.printf("Creating Dir: %s\n", path);
  if(fs.mkdir(path)){
    Serial.println("Dir created");
  } else {
    Serial.println("mkdir failed");
  }
}

bool is_dir(fs::FS &fs, const char * dirname){
  File file = fs.open(dirname);
  return file.isDirectory();
}



void appendFile(fs::FS &fs, const char * path, const char * message){
  Serial.printf("Appending to file: %s\n", path);

  File file = fs.open(path, FILE_APPEND);
  if(!file){
    Serial.println("Failed to open file for appending");
    return;
  }
  if(file.print(message)){
      Serial.println("Message appended");
  } else {
    Serial.println("Append failed");
  }
  file.close();
}

void renameFile(fs::FS &fs, const char * path1, const char * path2){
  Serial.printf("Renaming file %s to %s\n", path1, path2);
  if (fs.rename(path1, path2)) {
    Serial.println("File renamed");
  } else {
    Serial.println("Rename failed");
  }
}

void deleteFile(fs::FS &fs, const char * path){
  Serial.printf("Deleting file: %s\n", path);
  if(fs.remove(path)){
    Serial.println("File deleted");
  } else {
    Serial.println("Delete failed");
  }
}

void testFileIO(fs::FS &fs, const char * path){
  File file = fs.open(path);
  static uint8_t buf[512];
  size_t len = 0;
  uint32_t start = millis();
  uint32_t end = start;
  if(file){
    len = file.size();
    size_t flen = len;
    start = millis();
    while(len){
      size_t toRead = len;
      if(toRead > 512){
        toRead = 512;
      }
      file.read(buf, toRead);
      len -= toRead;
    }
    end = millis() - start;
    Serial.printf("%u bytes read for %u ms\n", flen, end);
    file.close();
  } else {
    Serial.println("Failed to open file for reading");
  }


  file = fs.open(path, FILE_WRITE);
  if(!file){
    Serial.println("Failed to open file for writing");
    return;
  }

  size_t i;
  start = millis();
  for(i=0; i<2048; i++){
    file.write(buf, 512);
  }
  end = millis() - start;
  Serial.printf("%u bytes written for %u ms\n", 2048 * 512, end);
  file.close();
}

  // uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  // Serial.printf("SD Card Size: %lluMB\n", cardSize);

  // listDir(SD, "/", 0);
  // createDir(SD, "/mydir");
  // listDir(SD, "/", 0);
  // removeDir(SD, "/mydir");
  // listDir(SD, "/", 2);
  // writeFile(SD, "/hello.txt", "Hello ");
  // appendFile(SD, "/hello.txt", "World!\n");
  // readFile(SD, "/hello.txt");
  // deleteFile(SD, "/foo.txt");
  // renameFile(SD, "/hello.txt", "/foo.txt");
  // readFile(SD, "/foo.txt");
  // testFileIO(SD, "/test.txt");
  // Serial.printf("Total space: %lluMB\n", SD.totalBytes() / (1024 * 1024));
  // Serial.printf("Used space: %lluMB\n", SD.usedBytes() / (1024 * 1024));

