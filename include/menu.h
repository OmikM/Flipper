#pragma once
#include <Arduino.h>
#include <vector>
#include <String>
#include <functional>
using namespace std;

class col {
public:
    String path = "/M";
    vector<String> dir;
    int is_in = false;
    int pos = 0;
    std::vector<col> cols;
    String name;
    void (*func)() = nullptr;

    bool del_file = 0;

    int value; // used in IR


    
    void initMenu();

    void scroll(bool up);
    void add(String n, void (*f)() = nullptr, int v = 0);
    void Print_out();

    void back();
    void next();
};
extern col M;