#pragma once
#include <FS.h>
#include <vector>
#include <Arduino.h>
using namespace std;

void writeFile(fs::FS &fs, const char * path, const char * message);
vector<String> readFile(fs::FS &fs, const char * path);
vector<String> listDir(fs::FS &fs, const char * dirname, uint8_t levels);
bool is_dir(fs::FS &fs, const char * dirname);