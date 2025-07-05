#pragma once
#include <Arduino.h>
using namespace std;



class Type {
public:
    int is_lets;
    bool is_big;
    int row;
    int col;
    char lets[2][16];
    char nums[2][16];
    char big[2][16];
    String typed ="";
    char disp[2][16];
    void cp(char a[2][16]);
    String type();
    void typeInit();
};
extern Type tp;

