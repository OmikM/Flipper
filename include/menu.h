#pragma once
#include <Arduino.h>
#include <vector>
#include <String>
#include <functional>

class col {
public:
    int is_in = false;
    int pos = 0;
    std::vector<col> cols;
    String name;
    void (*func)() = nullptr;

    int value; // used in IR

    String l1, l2;

    
    void initMenu();

    void Print_out();
    void scroll(bool up);
    void add(String n, void (*f)() = nullptr, int v = 0);
    col *cur();
    void back();
    void next();
};
extern col fr;