#pragma once
#include <Arduino.h>
using namespace std;



class Type {
public:
    int is_lets;
    bool is_big;
    int r;
    int c;

    const char nums[2][17] = {{' ','1', '3', '5', '7', '9', '~', '~', '~', '@', '#', '$', '%', '^', '|', '_'},
                      {' ','2', '4', '6', '8', '!', '~', '~', '~', '?', '*', '(', ')', '+', '=', '-'}};

    const char lets[2][17] = {{'a', 'c', 'e', 'g', 'i', 'k', '~', ' ', '~','m', 'o', 'q', 's', 'u', 'w', 'y'},
    {'b', 'd', 'f', 'h', 'j', 'l', '~', '~', '~','n', 'p', 'r', 't', 'v', 'x', 'z'}};;


    char big[2][17];
    String typed ="";
    char disp[2][17];
    void cp(const char a[2][17]);
    String type();
    void typeInit();
};
extern Type tp;

