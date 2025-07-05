#include <Arduino.h>
#include "type.h"
#include "display.h"
#include "hardware.h"
using namespace std;


Type tp;

void Type::cp(char a[2][16]){
  // for(int i = 0; i < 2; i++){
  //   for(int j = 0; j < 16; j++){
  //     disp[i][j] = a[i][j];
  //   }
  // }
  a = 0;
}

void Type::typeInit(){
    String typed ="";
    // bool is_lets = 1;
    // bool is_big = 0;
    // int row = 0;
    // int col = 8;
    // char lets[2][16] = {{'a', 'c', 'e', 'g', 'i', 'k', '~', ' ', '~','m', 'o', 'q', 's', 'u', 'w', 'y'},
    // {'b', 'd', 'f', 'h', 'j', 'l', '~', '~', '~','n', 'p', 'r', 't', 'v', 'x', 'z'}};
    // char nums[2][16] = {{' ','1', '3', '5', '7', '9', '~', '~', '~', '@', '#', '$', '%', '^', '|', '_'},
    //                   {' ','2', '4', '6', '8', '!', '~', '~', '~', '?', '*', '(', ')', '+', '=', '-'}};
    // char big[2][16] = {{'A', 'C', 'E', 'G', 'I', 'K', '~', '~', '~', 'M', 'O', 'Q', 'S', 'U', 'W', 'Y'},
    //                 {'B', 'D', 'F', 'H', 'J', 'L', '~', '~', '~', 'N', 'P', 'R', 'T', 'V', 'X', 'Z'}};
    // cp(lets);

}

String Type::type(){
    return "HIHIHO";
//     while (true){
//         Print(disp[0], disp[1]);

//         bool pressed;
// 	    pressed = false;
// 	    int pressed_ind = -1;
//   	    delay(200);
	
	
// 	    unsigned long time = millis();

// 	    for(int i = 0; i < 4; i++){
//     		curStates[i] = digitalRead(b_pins[i]);
//     	}

//     	for (int i = 0; i < 4; i++) {
//     	    if (curStates[i] and !lastStates[i]) {
//           		if (time - lastDebounceTime > debounceDelay) {
//         		    pressed = true;
//         		    pressed_ind = i;
//         		    lastDebounceTime = time;
//         		    break;  
//       	    }
//     	    }
//   	    }

//         if (pressed) {
//             Serial.print("Button ");
//             Serial.print(pressed_ind);
//             Serial.println(" pressed!");
//         }

//         for (int i = 0; i < 4; i++) {
//             lastStates[i] = curStates[i];
//         }


//         if(pressed_ind==0 or pressed_ind==1){
//               if(row==1 and pressed_ind==0){
//                 row--;
//             }else if(row==0 and pressed_ind==1){
//                 row++;
//             }else{
//                 //function buttons
//                 if(col==8 and row==0){
//                     typed.remove(typed.length()-1,1);
//                 }
//                 else if(col==7 and row==1){
//                 if(is_lets)cp(nums);
//                 else cp(lets);
//                 is_lets = !is_lets;
//                 }
//                 else if(col==6 and row==1){
//                 if(is_big)cp(lets);
//                 else cp(big);
//                 is_big = !is_big;
//                 }
//             else if(col==8 and row==1)return typed;
//             else typed +=disp[row][col];
//         }
//         }
//         if(pressed_ind==2){
//             if(col==0)col= 15;
//             else col-=1;
//         }
//         if(pressed_ind==3){
//             if(col==15) col=0;
//         else col++;
//     }
//   }  
}