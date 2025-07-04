#include <iostream>
#include <string>
using namespace std;
#include "type.h"
 

void Type::cp(char a[2][16]){
  for(int i = 0; i < 2; i++){
    for(int j = 0; j < 16; j++){
      disp[i][j] = a[i][j];
    }
  }
}

string Type::type(){
  string typed ="";
  bool is_lets = 1;
  bool is_big = 0;
  int row = 0;
  int col = 8;
  char lets[2][16] = {{'a', 'c', 'e', 'g', 'i', 'k', '~', ' ', '~','m', 'o', 'q', 's', 'u', 'w', 'y'},
  {'b', 'd', 'f', 'h', 'j', 'l', '~', '~', '~','n', 'p', 'r', 't', 'v', 'x', 'z'}};
  char nums[2][16] = {{' ','1', '3', '5', '7', '9', '~', '~', '~', '@', '#', '$', '%', '^', '|', '_'},
                      {' ','2', '4', '6', '8', '!', '~', '~', '~', '?', '*', '(', ')', '+', '=', '-'}};
  char big[2][16] = {{'A', 'C', 'E', 'G', 'I', 'K', '~', '~', '~', 'M', 'O', 'Q', 'S', 'U', 'W', 'Y'},
                    {'B', 'D', 'F', 'H', 'J', 'L', '~', '~', '~', 'N', 'P', 'R', 'T', 'V', 'X', 'Z'}};
  
  cp(lets);


  bool high = true;
  while (true){
    for(int j = 0; j <2; j++){
      for(int i = 0; i < 16; i++){
        if(j == row and i==col){
          cout << "@ ";
        }else{
          cout << disp[j][i] << " ";
        }
      }
      cout << '\n';
    }

    char temp;
    cin >> temp;
    if(temp=='w' or temp=='s'){
      if(row==1 and temp=='w'){
        row--;
      }else if(row==0 and temp=='s'){
        row++;
      }else{
        //function buttons
        if(col==8 and row==0)typed.pop_back();
        else if(col==7 and row==1){
          if(is_lets)cp(nums);
          else cp(lets);
          is_lets = !is_lets;
        }
        else if(col==6 and row==1){
          if(is_big)cp(lets);
          else cp(big);
          is_big = !is_big;
          }
        else if(col==8 and row==1)return typed;
        else typed +=disp[row][col];
      }
    }
    if(temp=='a'){
      if(col==0)col= 15;
      else col-=1;
    }
    if(temp=='d'){
      if(col==15) col=0;
      else col++;
    }
  }  
}