#ifndef TYPE_H
#define TYPE_H
#include <string>

class Type {
public:
    int is_lets;
    bool is_big;
    int row;
    int col;
    char lets[2][16];
    char nums[2][16];
    char big[2][16];
    void n_to_l();
    std::string typed ="";
    char disp[2][16];
    void cp(char a[2][16]);
    std::string type();
};

#endif