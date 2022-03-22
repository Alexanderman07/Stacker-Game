/* Your Name & E-mail: Alexander Manjarrez amanj003@ucr.edu
 * * Lab Section: Section 22
 * * Assignment: Final Project Stacker Game
 * * Exercise Description: For this final project,I developed a stacker game that has a difficulty setting using a joystick, uses an 8x8 LED matrix, and 
 * * uses a piezo buzzer to indicate to the player that they have lost the game. Players can also reset the game if they wish to continue playing after they 
 * * have either won or lost the game.
 * *
 * * I acknowledge all content contained herein, excluding
 * * template or example code, is my own original work.
 * *
 * * Demo Link: https://www.youtube.com/watch?v=tK0Kse1C_dc 
 * */
#include <LedControl.h>

int DIN = 12;
int CS =  11;
int CLK = 10;
LedControl lc = LedControl(DIN, CLK, CS, 0);

const int buzzer = 9;
const int b0 = 4;
const int b1 = 5;
const int b2 = 6;
const int x_pin = A2;
const int y_pin = A3;
const int SW_pin = 7;
int switchval = 1;
char goOn = 1;
unsigned char timer = 0;
unsigned char timelimit = 0;
bool timerstop = false;
bool commence = false;
bool redoUp = false;

unsigned char flag = 0;
unsigned char flag1 = 0;
unsigned char flag2 = 0;
unsigned char flag3 = 0;
unsigned char flag4 = 0;
unsigned char flag5 = 0;
unsigned char flag6 = 0;
unsigned char flag7 = 0;
unsigned char cnt;
unsigned char soundflag = 0;
unsigned char sound = 0;
unsigned char spaces = 0;

unsigned char level = 0; //move up a row everytime a button is pressed
unsigned char positioncheck = 0;
int i = 7;

//row 1 - 3 blocks
byte row11[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07};
byte row12[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E};
byte Starting[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1C};
byte row13[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38};
byte row14[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70};
byte row15[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0};

//row2 - 3 blocks
byte row21[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00};
byte row22[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x00};
byte Starting2[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x00};
byte row23[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00};
byte row24[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00};
byte row25[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00};

//row3 - 3 blocks (can also be 1 or 2 blocks)
byte row31[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00};
byte row32[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00};
byte Starting3[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00};
byte row33[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00};
byte row34[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00};
byte row35[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00};
byte row36[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00}; //set up for 2 blocks
byte row37[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00}; //set up for 1 block

//row4 - 2 blocks
byte row41[8] = {0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00};
byte row42[8] = {0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00};
byte row43[8] = {0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00};
byte Starting4[8] = {0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00};
byte row44[8] = {0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00};
byte row45[8] = {0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00};
byte row46[8] = {0x00, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00};
byte row47[8] = {0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00}; //set up for 1 block

//row5 - 2 blocks
byte row51[8] = {0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00};
byte row52[8] = {0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00};
byte row53[8] = {0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x00};
byte Starting5[8] = {0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00};
byte row54[8] = {0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00};
byte row55[8] = {0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00};
byte row56[8] = {0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x00};
byte row57[8] = {0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00}; //set up for 1 block

//row6 - 2 blocks
byte row61[8] = {0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00};
byte row62[8] = {0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00};
byte row63[8] = {0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00};
byte Starting6[8] = {0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00};
byte row64[8] = {0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00};
byte row65[8] = {0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00};
byte row66[8] = {0x00, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00};
byte row67[8] = {0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00}; //set up for 1 block

//row 7 - 1 block
byte row71[8] = {0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
byte row72[8] = {0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
byte row73[8] = {0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
byte Starting7[8] = {0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
byte row74[8] = {0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
byte row75[8] = {0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
byte row76[8] = {0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
byte row77[8] = {0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

//row 8 - 1 block
byte row81[8] = {0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
byte row82[8] = {0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
byte row83[8] = {0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
byte Starting8[8] = {0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
byte row84[8] = {0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
byte row85[8] = {0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
byte row86[8] = {0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
byte row87[8] = {0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

unsigned char temp = 0;
byte* row1[] = {row11, row12, Starting, row13, row14, row15};

typedef struct task {
  int state;
  unsigned long period;
  unsigned long elapsedTime;
  int (*TickFct)(int);
} task;

const unsigned short tasksNum = 4;
task tasks[tasksNum];

enum States_Game {Start2, Idle1, Idle2, Idle3, Idle4, Idle5, Idle6, Idle7, Idle8, Idle9, Idle10, Idle11, Idle12, Idle13, Idle14, Hold, Moveup, Winner, Lose, Reset};
int TickFct_Gameplay(int state) {
  switch (state) {
    case Start2:
      if(commence == true){
      state = Idle1;
      cnt = 0;
      timerstop = false;
      timer = 0;
      sound = 0;
      }
      else if(commence == false){
        state = Start2;
      }
      break;

case Idle1: //Starting 0x1C
if (digitalRead(A0) == LOW) {
        if(timerstop == true){
          state = Lose;
        }
      else{
          state = Idle2;
        }
      }
      if (digitalRead(A0) == HIGH) {
        timer = 0;
        state = Hold;
        if (level == 0) {
          flag = 0x1C;
        }
        if (level == 1) {
          flag1 = 0x1C;
        }
        if (level == 2) {
          if (spaces == 0) {
            flag2 = 0x1C;
          }
          if (spaces == 2) {
            flag2 = 0x18;
          }
          if (spaces == 1) {
            flag2 = 0x08;
          }
        }
        if (level == 3) {
          if (spaces == 1) {
            flag3 = 0x08;
          }
          else {
            flag3 = 0x18;
          }
        }
        if (level == 4) {
          if (spaces == 1) {
            flag4 = 0x08;
          }
          else {
            flag4 = 0x18;
          }
        }
        if (level == 5) {
          if (spaces == 1) {
            flag5 = 0x08;
          }
          else {
            flag5 = 0x18;
          }
        }
        if (level == 6) {
          flag6 = 0x08;
        }
        if (level == 7) {
          flag7 = 0x08;
        }
      }
      break;

case Idle2: //0x38
if (digitalRead(A0) == LOW) {
        if(timerstop == true){
          state = Lose;
        }
        else{
          state = Idle3;
        }
      }
      if (digitalRead(A0) == HIGH) {
        timer = 0;
        state = Hold;
        if (level == 0) {
          flag = 0x38;
        }
        if (level == 1) {
          flag1 = 0x38;
        }
        if (level == 2) {
          if (spaces == 0) {
            flag2 = 0x38;
          }
          if (spaces == 2) {
            flag2 = 0x30;
          }
          if (spaces == 1) {
            flag2 = 0x10;
          }
        }
        if (level == 3) {
          if (spaces == 1) {
            flag3 = 0x10;
          }
          else {
            flag3 = 0x30;
          }
        }
        if (level == 4) {
          if (spaces == 1) {
            flag4 = 0x10;
          }
          else {
            flag4 = 0x30;
          }
        }
        if (level == 5) {
          if (spaces == 1) {
            flag5 = 0x10;
          }
          else {
            flag5 = 0x30;
          }
        }
        if (level == 6) {
          flag6 = 0x10;
        }
        if (level == 7) {
          flag7 = 0x10;
        }
      }
      break;

case Idle3: //0x070
if (digitalRead(A0) == LOW) {
        if(timerstop == true){
          state = Lose;
        }
        else{
          state = Idle4;
        }
      }
      if (digitalRead(A0) == HIGH) {
        timer = 0;
        state = Hold;
        if (level == 0) {
          flag = 0x70;
        }
        if (level == 1) {
          flag1 = 0x70;
        }
        if (level == 2) {
          if (spaces == 0) {
            flag2 = 0x70;
          }
          if (spaces == 2) {
            flag2 = 0x60;
          }
          if (spaces == 1) {
            flag2 = 0x20;
          }
        }
        if (level == 3) {
          if (spaces == 1) {
            flag3 = 0x20;
          }
          else {
            flag3 = 0x60;
          }
        }
        if (level == 4) {
          if (spaces == 1) {
            flag4 = 0x20;
          }
          else {
            flag4 = 0x60;
          }
        }
        if (level == 5) {
          if (spaces == 1) {
            flag5 = 0x20;
          }
          else {
            flag5 = 0x60;
          }
        }
        if (level == 6) {
          flag6 = 0x20;
        }
        if (level == 7) {
          flag7 = 0x20;
        }
      }
      break;

case Idle4: //0xE0
if (digitalRead(A0) == LOW) {
        if(timerstop == true){
          state = Lose;
        }
        else{
          state = Idle5;
        }
      }
      if (digitalRead(A0) == HIGH) {
        timer = 0;
        state = Hold;
        if (level == 0) {
          flag = 0xE0;
        }
        if (level == 1) {
          flag1 = 0xE0;
        }
        if (level == 2) {
          if (spaces == 0) {
            flag2 = 0xE0;
          }
          if (spaces == 2) {
            flag2 = 0xC0;
          }
          if (spaces == 1) {
            flag2 = 0x40;
          }
        }
        if (level == 3) {
          if (spaces == 1) {
            flag3 = 0x40;
          }
          else {
            flag3 = 0xC0;
          }
        }
        if (level == 4) {
          if (spaces == 1) {
            flag4 = 0x40;
          }
          else {
            flag4 = 0xC0;
          }
        }
        if (level == 5) {
          if (spaces == 1) {
            flag5 = 0x40;
          }
          else {
            flag5 = 0xC0;
          }
        }
        if (level == 6) {
          flag6 = 0x40;
        }
        if (level == 7) {
          flag7 = 0x40;
        }
      }
      break;

case Idle5: //0x70
if (digitalRead(A0) == LOW) {
        if(timerstop == true){
          state = Lose;
        }
        else{
          state = Idle6;
        }
      }
      if (digitalRead(A0) == HIGH) {
        timer = 0;
        state = Hold;
        if (level == 0) {
          flag = 0x70;
        }
        if (level == 1) {
          flag1 = 0x70;
        }
        if (level == 2) {
          if (spaces == 0) {
            flag2 = 0x70;
          }
          if (spaces == 2) {
            flag2 = 0x60;
          }
          if (spaces == 1) {
            flag2 = 0x80;
          }
        }
        if (level == 3) {
          if (spaces == 1) {
            flag3 = 0x80;
          }
          else {
            flag3 = 0x60;
          }
        }
        if (level == 4) {
          if (spaces == 1) {
            flag4 = 0x80;
          }
          else {
            flag4 = 0x60;
          }
        }
        if (level == 5) {
          if (spaces == 1) {
            flag5 = 0x80;
          }
          else {
            flag5 = 0x60;
          }
        }
        if (level == 6) {
          flag6 = 0x80;
        }
        if (level == 7) {
          flag7 = 0x80;
        }
      }
      break;

case Idle6: //0x38
if (digitalRead(A0) == LOW) {
        if(timerstop == true){
          state = Lose;
        }
        else{
          state = Idle7;
        }
      }
      if (digitalRead(A0) == HIGH) {
        timer = 0;
        state = Hold;
        if (level == 0) {
          flag = 0x38;
        }
        if (level == 1) {
          flag1 = 0x38;
        }
        if (level == 2) {
          if (spaces == 0) {
            flag2 = 0x38;
          }
          if (spaces == 2) {
            flag2 = 0x30;
          }
          if (spaces == 1) {
            flag2 = 0x40;
          }
        }
        if (level == 3) {
          if (spaces == 1) {
            flag3 = 0x40;
          }
          else {
            flag3 = 0x30;
          }
        }
        if (level == 4) {
          if (spaces == 1) {
            flag4 = 0x40;
          }
          else {
            flag4 = 0x30;
          }
        }
        if (level == 5) {
          if (spaces == 1) {
            flag5 = 0x40;
          }
          else {
            flag5 = 0x30;
          }
        }
        if (level == 6) {
          flag6 = 0x40;
        }
        if (level == 7) {
          flag7 = 0x40;
        }
      }
      break;

case Idle7: //Starting 0x01C
if (digitalRead(A0) == LOW) {
        if(timerstop == true){
          state = Lose;
        }
        else{
          state = Idle8;
        }
      }
      if (digitalRead(A0) == HIGH) {
        timer = 0;
        state = Hold;
        if (level == 0) {
          flag = 0x1C;
        }
        if (level == 1) {
          flag1 = 0x1C;
        }
        if (level == 2) {
          if (spaces == 0) {
            flag2 = 0x1C;
          }
          if (spaces == 2) {
            flag2 = 0x18;
          }
          if (spaces == 1) {
            flag2 = 0x20;
          }
        }
        if (level == 3) {
          if (spaces == 1) {
            flag3 = 0x20;
          }
          else {
            flag3 = 0x18;
          }
        }
        if (level == 4) {
          if (spaces == 1) {
            flag4 = 0x20;
          }
          else {
            flag4 = 0x18;
          }
        }
        if (level == 5) {
          if (spaces == 1) {
            flag5 = 0x20;
          }
          else {
            flag5 = 0x18;
          }
        }
        if (level == 6) {
          flag6 = 0x20;
        }
        if (level == 7) {
          flag7 = 0x20;
        }
      }
      break;

case Idle8: //0x0E
if (digitalRead(A0) == LOW) {
        if(timerstop == true){
          state = Lose;
        }
        else{
          state = Idle9;
        }
      }
      if (digitalRead(A0) == HIGH) {
        timer = 0;
        state = Hold;
        if (level == 0) {
          flag = 0x0E;
        }
        if (level == 1) {
          flag1 = 0x0E;
        }
        if (level == 2) {
          if (spaces == 0) {
            flag2 = 0x0E;
          }
          if (spaces == 2) {
            flag2 = 0x0C;
          }
          if (spaces == 1) {
            flag2 = 0x10;
          }
        }
        if (level == 3) {
          if (spaces == 1) {
            flag3 = 0x10;
          }
          else {
            flag3 = 0x0C;
          }
        }
        if (level == 4) {
          if (spaces == 1) {
            flag4 = 0x10;
          }
          else {
            flag4 = 0x0C;
          }
        }
        if (level == 5) {
          if (spaces == 1) {
            flag5 = 0x10;
          }
          else {
            flag5 = 0x0C;
          }
        }
        if (level == 6) {
          flag6 = 0x10;
        }
        if (level == 7) {
          flag7 = 0x10;
        }
      }
      break;

case Idle9: //0x07
if (digitalRead(A0) == LOW) {
        if(timerstop == true){
          state = Lose;
        }
        else{
          state = Idle10;
        }
      }
      if (digitalRead(A0) == HIGH) {
        timer = 0;
        state = Hold;
        if (level == 0) {
          flag = 0x07;
        }
        if (level == 1) {
          flag1 = 0x07;
        }
        if (level == 2) {
          if (spaces == 0) {
            flag2 = 0x07;
          }
          if (spaces == 2) {
            flag2 = 0x06;
          }
          if (spaces == 1) {
            flag2 = 0x08;
          }
        }
        if (level == 3) {
          if (spaces == 1) {
            flag3 = 0x08;
          }
          else {
            flag3 = 0x06;
          }
        }
        if (level == 4) {
          if (spaces == 1) {
            flag4 = 0x08;
          }
          else {
            flag4 = 0x06;
          }
        }
        if (level == 5) {
          if (spaces == 1) {
            flag5 = 0x08;
          }
          else {
            flag5 = 0x06;
          }
        }
        if (level == 6) {
          flag6 = 0x08;
        }
        if (level == 7) {
          flag7 = 0x08;
        }
      }
      break;

case Idle10: //Starting 0x1C
if (digitalRead(A0) == LOW) {
        if(timerstop == true){
          state = Lose;
        }
        if (level == 0 || level == 1 || (level == 2 && spaces == 0)) {
          state = Idle1;
        }
        if ((level == 5 && spaces == 1) || (level == 4 && spaces == 1) || (level == 3 && spaces == 1) || (level == 2 && spaces == 2) || (level == 2 && spaces == 1) || level == 3 || level == 4 || level == 5 || level == 6 || level == 7) {
          state = Idle11;
        }
      }
      if (digitalRead(A0) == HIGH) {
        timer = 0;
        state = Hold;
        if (level == 0) {
          flag = 0x1C;
        }
        if (level == 1) {
          flag1 = 0x1C;
        }
        if (level == 2) {
          if (spaces == 0) {
            flag2 = 0x1C;
          }
          if (spaces == 2) {
            flag2 = 0x03;
          }
          if (spaces == 1) {
            flag2 = 0x04;
          }
        }
        if (level == 3) {
          if (spaces == 1) {
            flag3 = 0x04;
          }
          else {
            flag3 = 0x03;
          }
        }
        if (level == 4) {
          if (spaces == 1) {
            flag4 = 0x04;
          }
          else {
            flag4 = 0x03;
          }
        }
        if (level == 5) {
          if (spaces == 1) {
            flag5 = 0x04;
          }
          else {
            flag5 = 0x03;
          }
        }
        if (level == 6) {
          flag6 = 0x04;
        }
        if (level == 7) {
          flag7 = 0x04;
        }
      }
      break;

    case Idle11:
      if (digitalRead(A0) == LOW) {
        if(timerstop == true){
          state = Lose;
        }
        else{
          state = Idle12;
        }
      }
      if (digitalRead(A0) == HIGH) {
        timer = 0;
        state = Hold;
        if (level == 2) {
          if (spaces == 2) {
            flag2 = 0x06;
          }
          if (spaces == 1) {
            flag2 = 0x02;
          }
        }
        if (level == 3) {
          if (spaces == 1) {
            flag3 = 0x02;
          }
          else {
            flag3 = 0x06;
          }
        }
        if (level == 4) {
          if (spaces == 1) {
            flag4 = 0x02;
          }
          else {
            flag4 = 0x06;
          }
        }
        if (level == 5) {
          if (spaces == 1) {
            flag5 = 0x02;
          }
          else {
            flag5 = 0x06;
          }
        }
        if (level == 6) {
          flag6 = 0x02;
        }
        if (level == 7) {
          flag7 = 0x02;
        }
      }
      break;

    case Idle12:
      if (digitalRead(A0) == LOW) {
        if(timerstop == true){
          state = Lose;
        }
        if ((level == 2 && spaces == 2) || level == 3 || level == 4 || level == 5) {
          state = Idle1;
        }
        if ((level == 5 && spaces == 1) || (level == 4 && spaces == 1) || (level == 3 && spaces == 1) || (level == 2 && spaces == 1) || level == 6 || level == 7) {
          state = Idle13;
        }
      }
      if (digitalRead(A0) == HIGH) {
        timer = 0;
        state = Hold;
        if (level == 2) {
          if (spaces == 1) {
            flag2 = 0x01;
          }
        }
        if (level == 3) {
          if (spaces == 1) {
            flag3 = 0x01;
          }
          else {
            flag3 = 0x0C;
          }
        }
        if (level == 4) {
          if (spaces == 1) {
            flag4 = 0x01;
          }
          else {
            flag4 = 0x0C;
          }
        }
        if (level == 5) {
          if (spaces == 1) {
            flag5 = 0x01;
          }
          else {
            flag5 = 0x0C;
          }
        }
        if (level == 6) {
          flag6 = 0x01;
        }
        if (level == 7) {
          flag7 = 0x01;
        }
      }
      break;

    case Idle13:
      if (digitalRead(A0) == LOW) {
        if(timerstop == true){
          state = Lose;
        }
        else{
          state = Idle14;
        }
      }
      if (digitalRead(A0) == HIGH) {
        timer = 0;
        state = Hold;
        if (level == 2) {
          if (spaces == 1) {
            flag2 = 0x02;
          }
        }
        if (level == 3) {
          if (spaces == 1) {
            flag3 = 0x02;
          }
        }
        if (level == 4) {
          if (spaces == 1) {
            flag4 = 0x02;
          }
        }
        if (level == 5) {
          if (spaces == 1) {
            flag5 = 0x02;
          }
        }
        if (level == 6) {
          flag6 = 0x02;
        }
        if (level == 7) {
          flag7 = 0x02;
        }
      }
      break;

    case Idle14:
      if (digitalRead(A0) == LOW) {
        if(timerstop == true){
          state = Lose;
        }
        else{
          state = Idle1;
        }
      }
      if (digitalRead(A0) == HIGH) {
        timer = 0;
        state = Hold;
        if (level == 2) {
          if (spaces == 1) {
            flag2 = 0x04;
          }
        }
        if (level == 3) {
          if (spaces == 1) {
            flag3 = 0x04;
          }
        }
        if (level == 4) {
          if (spaces == 1) {
            flag4 = 0x04;
          }
        }
        if (level == 5) {
          if (spaces == 1) {
            flag5 = 0x04;
          }
        }
        if (level == 6) {
          flag6 = 0x04;
        }
        if (level == 7) {
          flag7 = 0x04;
        }
      }
      break;

case Hold:
    if(digitalRead(A0) == HIGH){
      timer = 0;
      state = Hold;
    }
    else if(digitalRead(A0) == LOW){
      timer = 0;
      state = Moveup;
    }
    break;
    
    case Moveup:
      level++;
      positioncheck = flag;

      if (level == 1) {
        row21[i] = flag;
        row22[i] = flag;
        Starting2[i] = flag;
        row23[i] = flag;
        row24[i] = flag;
        row25[i] = flag;

        state = Idle1;
      }

      if (level == 2) {
        row31[i - 2] = 0x07;
        row32[i - 2] = 0x0E;
        Starting3[i - 2] = 0x1C;
        row33[i - 2] = 0x38;
        row34[i - 2] = 0x70;
        row35[i - 2] = 0xE0;
        row36[i - 2] = 0xC0;
        row37[i - 2] = 0x80;

        row31[i - 1] = flag1 & flag;
        row32[i - 1] = flag1 & flag;
        Starting3[i - 1] = flag1 & flag;
        row33[i - 1] = flag1 & flag;
        row34[i - 1] = flag1 & flag;
        row35[i - 1] = flag1 & flag;

        row31[i] = flag;
        row32[i] = flag;
        Starting3[i] = flag;
        row33[i] = flag;
        row34[i] = flag;
        row35[i] = flag;

        if (((flag1 & flag) == 0x03) || ((flag1 & flag) == 0x06) || ((flag1 & flag) == 0x0C) || ((flag1 & flag) == 0x18) || ((flag1 & flag) == 0x30) || ((flag1 & flag) == 0x60) || ((flag1 & flag) == 0xC0)) {
          row31[i - 2] = 0x03;
          row32[i - 2] = 0x06;
          Starting3[i - 2] = 0x0C;
          row33[i - 2] = 0x18;
          row34[i - 2] = 0x30;
          row35[i - 2] = 0x60;
          row36[i - 2] = 0xC0;

          row36[i - 1] = flag1 & flag;

          row36[i] = flag;

          spaces = 2;
        }

        if (((flag1 & flag) == 0x01) || ((flag1 & flag) == 0x02) || ((flag1 & flag) == 0x04) || ((flag1 & flag) == 0x08) || ((flag1 & flag) == 0x10) || ((flag1 & flag) == 0x20) || ((flag1 & flag) == 0x40) || ((flag1 & flag) == 0x80)) {
          row31[i - 2] = 0x01;
          row32[i - 2] = 0x02;
          Starting3[i - 2] = 0x04;
          row33[i - 2] = 0x08;
          row34[i - 2] = 0x10;
          row35[i - 2] = 0x20;
          row36[i - 2] = 0x40;
          row37[i - 2] = 0x80;

          row36[i - 1] = flag1 & flag;
          row37[i - 1] = flag1 & flag;

          row36[i] = flag;
          row37[i] = flag;

          spaces = 1;
        }

/*if(((flag1 & flag) ==0x07)||((flag1 & flag) == 0x0E)||((flag1 & flag) == 0x1C)||((flag1 & flag) == 0x38)||((flag1 & flag) == 0x70)||((flag1 & flag) == 0xE0)) {
 *           state = Idle1;
 *                     }*/

if ((flag1 & flag) == 0x00) {
          state = Lose;
        }
        if ((flag1 & flag) != 0x00) {
          state = Idle1;
        }
      }

      if (level == 3) {
        row41[i - 3] = 0x03;
        row42[i - 3] = 0x06;
        row43[i - 3] = 0x0C;
        Starting4[i - 3] = 0x18;
        row44[i - 3] = 0x30;
        row45[i - 3] = 0x60;
        row46[i - 3] = 0xC0;
        row47[i - 3] = 0x80;

        row41[i - 2] = flag2 & flag1 & flag;
        row42[i - 2] = flag2 & flag1 & flag;
        row43[i - 2] = flag2 & flag1 & flag;
        Starting4[i - 2] = flag2 & flag1 & flag;
        row44[i - 2] = flag2 & flag1 & flag;
        row45[i - 2] = flag2 & flag1 & flag;
        row46[i - 2] = flag2 & flag1 & flag;

        row41[i - 1] = flag1 & flag;
        row42[i - 1] = flag1 & flag;
        row43[i - 1] = flag1 & flag;
        Starting4[i - 1] = flag1 & flag;
        row44[i - 1] = flag1 & flag;
        row45[i - 1] = flag1 & flag;
        row46[i - 1] = flag1 & flag;

        row41[i] = flag;
        row42[i] = flag;
        row43[i] = flag;
        Starting4[i] = flag;
        row44[i] = flag;
        row45[i] = flag;
        row46[i] = flag;

        if (((flag2 & flag1 & flag) == 0x01) || ((flag2 & flag1 & flag) == 0x02) || ((flag2 & flag1 & flag) == 0x04) || ((flag2 & flag1 & flag) == 0x08) || ((flag2 & flag1 & flag) == 0x10) || ((flag2 & flag1 & flag) == 0x20) || ((flag2 & flag1 & flag) == 0x40) || ((flag2 & flag1 & flag) == 0x80)) {
          row41[i - 3] = 0x01;
          row42[i - 3] = 0x02;
          row43[i - 3] = 0x04;
          Starting4[i - 3] = 0x08;
          row44[i - 3] = 0x10;
          row45[i - 3] = 0x20;
          row46[i - 3] = 0x40;
          row47[i - 3] = 0x80;

          row46[i - 2] = flag2 & flag1 & flag;
          row47[i - 2] = flag2 & flag1 & flag;

          row46[i - 1] = flag1 & flag;
          row47[i - 1] = flag1 & flag;

          row46[i] = flag;
          row47[i] = flag;

          spaces = 1;
        }

        if ((flag2 & flag1 & flag) == 0x00) {
          state = Lose;
        }
        if ((flag2 & flag1 & flag) != 0x00) {
          state = Idle1;
        }
      }

      if (level == 4) {
        row51[i - 4] = 0x03;
        row52[i - 4] = 0x06;
        row53[i - 4] = 0x0C;
        Starting5[i - 4] = 0x18;
        row54[i - 4] = 0x30;
        row55[i - 4] = 0x60;
        row56[i - 4] = 0xC0;
        row57[i - 4] = 0x80;

        row51[i - 3] = flag3 & flag2 & flag1 & flag;
        row52[i - 3] = flag3 & flag2 & flag1 & flag;
        row53[i - 3] = flag3 & flag2 & flag1 & flag;
        Starting5[i - 3] = flag3 & flag2 & flag1 & flag;
        row54[i - 3] = flag3 & flag2 & flag1 & flag;
        row55[i - 3] = flag3 & flag2 & flag1 & flag;
        row56[i - 3] = flag3 & flag2 & flag1 & flag;

        row51[i - 2] = flag2 & flag1 & flag;
        row52[i - 2] = flag2 & flag1 & flag;
        row53[i - 2] = flag2 & flag1 & flag;
        Starting5[i - 2] = flag2 & flag1 & flag;
        row54[i - 2] = flag2 & flag1 & flag;
        row55[i - 2] = flag2 & flag1 & flag;
        row56[i - 2] = flag2 & flag1 & flag;

        row51[i - 1] = flag1 & flag;
        row52[i - 1] = flag1 & flag;
        row53[i - 1] = flag1 & flag;
        Starting5[i - 1] = flag1 & flag;
        row54[i - 1] = flag1 & flag;
        row55[i - 1] = flag1 & flag;
        row56[i - 1] = flag1 & flag;

        row51[i] = flag;
        row52[i] = flag;
        row53[i] = flag;
        Starting5[i] = flag;
        row54[i] = flag;
        row55[i] = flag;
        row56[i] = flag;

        if (((flag3 & flag2 & flag1 & flag) == 0x01) || ((flag3 & flag2 & flag1 & flag) == 0x02) || ((flag3 & flag2 & flag1 & flag) == 0x04) || ((flag3 & flag2 & flag1 & flag) == 0x08) || ((flag3 & flag2 & flag1 & flag) == 0x10) || ((flag3 & flag2 & flag1 & flag) == 0x20) || ((flag3 & flag2 & flag1 & flag) == 0x40) || ((flag3 & flag2 & flag1 & flag) == 0x80)) {
          row51[i - 4] = 0x01;
          row52[i - 4] = 0x02;
          row53[i - 4] = 0x04;
          Starting5[i - 4] = 0x08;
          row54[i - 4] = 0x10;
          row55[i - 4] = 0x20;
          row56[i - 4] = 0x40;
          row57[i - 4] = 0x80;

          row56[i - 3] = flag3 & flag2 & flag1 & flag;
          row57[i - 3] = flag3 & flag2 & flag1 & flag;

          row56[i - 2] = flag2 & flag1 & flag;
          row57[i - 2] = flag2 & flag1 & flag;

          row56[i - 1] = flag1 & flag;
          row57[i - 1] = flag1 & flag;

          row56[i] = flag;
          row57[i] = flag;

          spaces = 1;
        }

        if ((flag3 & flag2 & flag1 & flag) == 0x00) {
          state = Lose;
        }
        if ((flag3 & flag2 & flag1 & flag) != 0x00) {
          state = Idle1;
        }
      }

      if (level == 5) {
        row61[i - 5] = 0x03;
        row62[i - 5] = 0x06;
        row63[i - 5] = 0x0C;
        Starting6[i - 5] = 0x18;
        row64[i - 5] = 0x30;
        row65[i - 5] = 0x60;
        row66[i - 5] = 0xC0;
        row67[i - 5] = 0x80;

        row61[i - 4] = flag4 & flag3 & flag2 & flag1 & flag;
        row62[i - 4] = flag4 & flag3 & flag2 & flag1 & flag;
        row63[i - 4] = flag4 & flag3 & flag2 & flag1 & flag;
        Starting6[i - 4] = flag4 & flag3 & flag2 & flag1 & flag;
        row64[i - 4] = flag4 & flag3 & flag2 & flag1 & flag;
        row65[i - 4] = flag4 & flag3 & flag2 & flag1 & flag;
        row66[i - 4] = flag4 & flag3 & flag2 & flag1 & flag;

        row61[i - 3] = flag3 & flag2 & flag1 & flag;
        row62[i - 3] = flag3 & flag2 & flag1 & flag;
        row63[i - 3] = flag3 & flag2 & flag1 & flag;
        Starting6[i - 3] = flag3 & flag2 & flag1 & flag;
        row64[i - 3] = flag3 & flag2 & flag1 & flag;
        row65[i - 3] = flag3 & flag2 & flag1 & flag;
        row66[i - 3] = flag3 & flag2 & flag1 & flag;

        row61[i - 2] = flag2 & flag1 & flag;
        row62[i - 2] = flag2 & flag1 & flag;
        row63[i - 2] = flag2 & flag1 & flag;
        Starting6[i - 2] = flag2 & flag1 & flag;
        row64[i - 2] = flag2 & flag1 & flag;
        row65[i - 2] = flag2 & flag1 & flag;
        row66[i - 2] = flag2 & flag1 & flag;

        row61[i - 1] = flag1 & flag;
        row62[i - 1] = flag1 & flag;
        row63[i - 1] = flag1 & flag;
        Starting6[i - 1] = flag1 & flag;
        row64[i - 1] = flag1 & flag;
        row65[i - 1] = flag1 & flag;
        row66[i - 1] = flag1 & flag;

        row61[i] = flag;
        row62[i] = flag;
        row63[i] = flag;
        Starting6[i] = flag;
        row64[i] = flag;
        row65[i] = flag;
        row66[i] = flag;

        if (((flag4 & flag3 & flag2 & flag1 & flag) == 0x01) || ((flag4 & flag3 & flag2 & flag1 & flag) == 0x02) || ((flag4 & flag3 & flag2 & flag1 & flag) == 0x04) || ((flag4 & flag3 & flag2 & flag1 & flag) == 0x08) || ((flag4 & flag3 & flag2 & flag1 & flag) == 0x10) || ((flag4 & flag3 & flag2 & flag1 & flag) == 0x20) || ((flag4 & flag3 & flag2 & flag1 & flag) == 0x40) || ((flag4 & flag3 & flag2 & flag1 & flag) == 0x80)) {
          row61[i - 5] = 0x01;
          row62[i - 5] = 0x02;
          row63[i - 5] = 0x04;
          Starting6[i - 5] = 0x08;
          row64[i - 5] = 0x10;
          row65[i - 5] = 0x20;
          row66[i - 5] = 0x40;
          row67[i - 5] = 0x80;

          row66[i - 4] = flag4 & flag3 & flag2 & flag1 & flag;
          row67[i - 4] = flag4 & flag3 & flag2 & flag1 & flag;

          row66[i - 3] = flag3 & flag2 & flag1 & flag;
          row67[i - 3] = flag3 & flag2 & flag1 & flag;

          row66[i - 2] = flag2 & flag1 & flag;
          row67[i - 2] = flag2 & flag1 & flag;

          row66[i - 1] = flag1 & flag;
          row67[i - 1] = flag1 & flag;

          row66[i] = flag;
          row67[i] = flag;

          spaces = 1;
        }

        if ((flag4 & flag3 & flag2 & flag1 & flag) == 0x00) {
          state = Lose;
        }
        if ((flag4 & flag3 & flag2 & flag1 & flag) != 0x00) {
          state = Idle1;
        }
      }

      if (level == 6) {
        row71[i - 5] = flag5 & flag4 & flag3 & flag2 & flag1 & flag;
        row72[i - 5] = flag5 & flag4 & flag3 & flag2 & flag1 & flag;
        row73[i - 5] = flag5 & flag4 & flag3 & flag2 & flag1 & flag;
        Starting7[i - 5] = flag5 & flag4 & flag3 & flag2 & flag1 & flag;
        row74[i - 5] = flag5 & flag4 & flag3 & flag2 & flag1 & flag;
        row75[i - 5] = flag5 & flag4 & flag3 & flag2 & flag1 & flag;
        row76[i - 5] = flag5 & flag4 & flag3 & flag2 & flag1 & flag;
        row77[i - 5] = flag5 & flag4 & flag3 & flag2 & flag1 & flag;

        row71[i - 4] = flag4 & flag3 & flag2 & flag1 & flag;
        row72[i - 4] = flag4 & flag3 & flag2 & flag1 & flag;
        row73[i - 4] = flag4 & flag3 & flag2 & flag1 & flag;
        Starting7[i - 4] = flag4 & flag3 & flag2 & flag1 & flag;
        row74[i - 4] = flag4 & flag3 & flag2 & flag1 & flag;
        row75[i - 4] = flag4 & flag3 & flag2 & flag1 & flag;
        row76[i - 4] = flag4 & flag3 & flag2 & flag1 & flag;
        row77[i - 4] = flag4 & flag3 & flag2 & flag1 & flag;

        row71[i - 3] = flag3 & flag2 & flag1 & flag;
        row72[i - 3] = flag3 & flag2 & flag1 & flag;
        row73[i - 3] = flag3 & flag2 & flag1 & flag;
        Starting7[i - 3] = flag3 & flag2 & flag1 & flag;
        row74[i - 3] = flag3 & flag2 & flag1 & flag;
        row75[i - 3] = flag3 & flag2 & flag1 & flag;
        row76[i - 3] = flag3 & flag2 & flag1 & flag;
        row77[i - 3] = flag3 & flag2 & flag1 & flag;

        row71[i - 2] = flag2 & flag1 & flag;
        row72[i - 2] = flag2 & flag1 & flag;
        row73[i - 2] = flag2 & flag1 & flag;
        Starting7[i - 2] = flag2 & flag1 & flag;
        row74[i - 2] = flag2 & flag1 & flag;
        row75[i - 2] = flag2 & flag1 & flag;
        row76[i - 2] = flag2 & flag1 & flag;
        row77[i - 2] = flag2 & flag1 & flag;

        row71[i - 1] = flag1 & flag;
        row72[i - 1] = flag1 & flag;
        row73[i - 1] = flag1 & flag;
        Starting7[i - 1] = flag1 & flag;
        row74[i - 1] = flag1 & flag;
        row75[i - 1] = flag1 & flag;
        row76[i - 1] = flag1 & flag;
        row77[i - 1] = flag1 & flag;

        row71[i] = flag;
        row72[i] = flag;
        row73[i] = flag;
        Starting7[i] = flag;
        row74[i] = flag;
        row75[i] = flag;
        row76[i] = flag;
        row77[i] = flag;

        if ((flag5 & flag4 & flag3 & flag2 & flag1 & flag) == 0x00) {
          state = Lose;
        }
        if ((flag5 & flag4 & flag3 & flag2 & flag1 & flag) != 0x00) {
          state = Idle1;
        }
      }

      if (level == 7) {
        row81[i - 6] = flag6 & flag5 & flag4 & flag3 & flag2 & flag1 & flag;
        row82[i - 6] = flag6 & flag5 & flag4 & flag3 & flag2 & flag1 & flag;
        row83[i - 6] = flag6 & flag5 & flag4 & flag3 & flag2 & flag1 & flag;
        Starting8[i - 6] = flag6 & flag5 & flag4 & flag3 & flag2 & flag1 & flag;
        row84[i - 6] = flag6 & flag5 & flag4 & flag3 & flag2 & flag1 & flag;
        row85[i - 6] = flag6 & flag5 & flag4 & flag3 & flag2 & flag1 & flag;
        row86[i - 6] = flag6 & flag5 & flag4 & flag3 & flag2 & flag1 & flag;
        row87[i - 6] = flag6 & flag5 & flag4 & flag3 & flag2 & flag1 & flag;

        row81[i - 5] = flag5 & flag4 & flag3 & flag2 & flag1 & flag;
        row82[i - 5] = flag5 & flag4 & flag3 & flag2 & flag1 & flag;
        row83[i - 5] = flag5 & flag4 & flag3 & flag2 & flag1 & flag;
        Starting8[i - 5] = flag5 & flag4 & flag3 & flag2 & flag1 & flag;
        row84[i - 5] = flag5 & flag4 & flag3 & flag2 & flag1 & flag;
        row85[i - 5] = flag5 & flag4 & flag3 & flag2 & flag1 & flag;
        row86[i - 5] = flag5 & flag4 & flag3 & flag2 & flag1 & flag;
        row87[i - 5] = flag5 & flag4 & flag3 & flag2 & flag1 & flag;

        row81[i - 4] = flag4 & flag3 & flag2 & flag1 & flag;
        row82[i - 4] = flag4 & flag3 & flag2 & flag1 & flag;
        row83[i - 4] = flag4 & flag3 & flag2 & flag1 & flag;
        Starting8[i - 4] = flag4 & flag3 & flag2 & flag1 & flag;
        row84[i - 4] = flag4 & flag3 & flag2 & flag1 & flag;
        row85[i - 4] = flag4 & flag3 & flag2 & flag1 & flag;
        row86[i - 4] = flag4 & flag3 & flag2 & flag1 & flag;
        row87[i - 4] = flag4 & flag3 & flag2 & flag1 & flag;

        row81[i - 3] = flag3 & flag2 & flag1 & flag;
        row82[i - 3] = flag3 & flag2 & flag1 & flag;
        row83[i - 3] = flag3 & flag2 & flag1 & flag;
        Starting8[i - 3] = flag3 & flag & flag1 & flag2;
        row84[i - 3] = flag3 & flag2 & flag1 & flag;
        row85[i - 3] = flag3 & flag2 & flag1 & flag;
        row86[i - 3] = flag3 & flag2 & flag1 & flag;
        row87[i - 3] = flag3 & flag2 & flag1 & flag;

        row81[i - 2] = flag2 & flag1 & flag;
        row82[i - 2] = flag2 & flag1 & flag;
        row83[i - 2] = flag2 & flag1 & flag;
        Starting8[i - 2] = flag2 & flag1 & flag;
        row84[i - 2] = flag2 & flag1 & flag;
        row85[i - 2] = flag2 & flag1 & flag;
        row86[i - 2] = flag2 & flag1 & flag;
        row87[i - 2] = flag2 & flag1 & flag;

        row81[i - 1] = flag1 & flag;
        row82[i - 1] = flag1 & flag;
        row83[i - 1] = flag1 & flag;
        Starting8[i - 1] = flag1 & flag;
        row84[i - 1] = flag1 & flag;
        row85[i - 1] = flag1 & flag;
        row86[i - 1] = flag1 & flag;
        row87[i - 1] = flag1 & flag;

        row81[i] = flag;
        row82[i] = flag;
        row83[i] = flag;
        Starting8[i] = flag;
        row84[i] = flag;
        row85[i] = flag;
        row86[i] = flag;
        row87[i] = flag;

        if ((flag6 & flag5 & flag4 & flag3 & flag2 & flag1 & flag) == 0x00) {
          state = Lose;
        }
        if ((flag6 & flag5 & flag4 & flag3 & flag2 & flag1 & flag) != 0x00) {
          state = Idle1;
        }
      }

      if (level == 8) {
        if ((flag7 & flag6 & flag5 & flag4 & flag3 & flag2 & flag1 & flag) == 0x00) {
          state = Lose;
        }
        if ((flag7 & flag6 & flag5 & flag4 & flag3 & flag2 & flag1 & flag) != 0x00) {
          state = Winner;
        }
      }

      break;

case Winner:

      if (cnt <= 15) {
        if ((cnt % 3) == 0) {
          if (flag6 == row81[0]) {
            printByte(row81);
          }
          if (flag6 == row82[0]) {
            printByte(row82);
          }
          if (flag6 == row83[0]) {
            printByte(row83);
          }
          if (flag6 == Starting8[0]) {
            printByte(Starting8);
          }
          if (flag6 == row84[0]) {
            printByte(row84);
          }
          if (flag6 == row85[0]) {
            printByte(row85);
          }
          if (flag6 == row86[0]) {
            printByte(row86);
          }
          if (flag6 == row87[0]) {
            printByte(row87);
          }
        }
        else {
          lc.clearDisplay(0);
        }
      }
      if (cnt > 15) {
        cnt = 16;
        if (digitalRead(A1) == HIGH) {
          state = Reset;
        }
      }
      break;

    case Lose:
      if (cnt <= 3) {
        sound = 1;
      }
      if (cnt > 3) {
        cnt = 4;
        sound = 0;
      }
      if (digitalRead(A1) == HIGH) {
        sound = 0;
        state = Reset;
      }
      break;

    case Reset:
      flag = 0;
      flag1 = 0;
      flag2 = 0;
      flag3 = 0;
      flag4 = 0;
      flag5 = 0;
      flag6 = 0;
      flag7 = 0;
      soundflag = 0;
      sound = 0;
      spaces = 0;
      level = 0;
      state = Start2;
      redoUp = true;
      commence = false;
      timer = 0;
      timelimit = 0;
      timerstop = false;
      lc.clearDisplay(0);
      break;

    default:
      break;
  }
switch (state) {
    case Start2:
      break;

    case Idle1:
      lc.clearDisplay(0);
      if (level == 0) {
        printByte(Starting);
      }
      if (level == 1) {
        printByte(Starting2);
      }
      if (level == 2) {
        if (spaces == 0) {
          printByte(Starting3);
        }
        if (spaces == 2 || spaces == 1) {
          printByte(row33);
        }
      }
      if (level == 3) {
        printByte(Starting4);
      }
      if (level == 4) {
        printByte(Starting5);
      }
      if (level == 5) {
        printByte(Starting6);
      }
      if (level == 6) {
        printByte(Starting7);
      }
      if (level == 7) {
        printByte(Starting8);
      }
      break;

    case Idle2:
      lc.clearDisplay(0);
      if (level == 0) {
        printByte(row13);
      }
      if (level == 1) {
        printByte(row23);
      }
      if (level == 2) {
        if (spaces == 0) {
          printByte(row33);
        }
        if (spaces == 2 || spaces == 1) {
          printByte(row34);
        }
      }
      if (level == 3) {
        printByte(row44);
      }
      if (level == 4) {
        printByte(row54);
      }
      if (level == 5) {
        printByte(row64);
      }
      if (level == 6) {
        printByte(row74);
      }
      if (level == 7) {
        printByte(row84);
      }
      break;

case Idle3:
      lc.clearDisplay(0);
      if (level == 0) {
        printByte(row14);
      }
      if (level == 1) {
        printByte(row24);
      }
      if (level == 2) {
        if (spaces == 0) {
          printByte(row34);
        }
        if (spaces == 2 || spaces == 1) {
          printByte(row35);
        }
      }
      if (level == 3) {
        printByte(row45);
      }
      if (level == 4) {
        printByte(row55);
      }
      if (level == 5) {
        printByte(row65);
      }
      if (level == 6) {
        printByte(row75);
      }
      if (level == 7) {
        printByte(row85);
      }
      break;

case Idle4:
      lc.clearDisplay(0);
      if (level == 0) {
        printByte(row15);
      }
      if (level == 1) {
        printByte(row25);
      }
      if (level == 2) {
        if (spaces == 0) {
          printByte(row35);
        }
        if (spaces == 2 || spaces == 1) {
          printByte(row36);
        }
      }
      if (level == 3) {
        printByte(row46);
      }
      if (level == 4) {
        printByte(row56);
      }
      if (level == 5) {
        printByte(row66);
      }
      if (level == 6) {
        printByte(row76);
      }
      if (level == 7) {
        printByte(row86);
      }
      break;

case Idle5:
      lc.clearDisplay(0);
      if (level == 0) {
        printByte(row14);
      }
      if (level == 1) {
        printByte(row24);
      }
      if (level == 2) {
        if (spaces == 0) {
          printByte(row34);
        }
        if (spaces == 2) {
          printByte(row35);
        }
        if (spaces == 1) {
          printByte(row37);
        }
      }
      if (level == 3) {
        if (spaces == 1) {
          printByte(row47);
        }
        else {
          printByte(row45);
        }
      }
      if (level == 4) {
        if (spaces == 1) {
          printByte(row57);
        }
        else {
          printByte(row55);
        }
      }
      if (level == 5) {
        if (spaces == 1) {
          printByte(row67);
        }
        else {
          printByte(row65);
        }
      }
      if (level == 6) {
        printByte(row77);
      }
      if (level == 7) {
        printByte(row87);
      }
      break;

case Idle6:
      lc.clearDisplay(0);
      if (level == 0) {
        printByte(row13);
      }
      if (level == 1) {
        printByte(row23);
      }
      if (level == 2) {
        if (spaces == 0) {
          printByte(row33);
        }
        if (spaces == 2) {
          printByte(row34);
        }
        if (spaces == 1) {
          printByte(row36);
        }
      }
      if (level == 3) {
        if (spaces == 1) {
          printByte(row46);
        }
        else {
          printByte(row44);
        }
      }
      if (level == 4) {
        if (spaces == 1) {
          printByte(row56);
        }
        else {
          printByte(row54);
        }
      }
      if (level == 5) {
        if (spaces == 1) {
          printByte(row66);
        }
        else {
          printByte(row64);
        }
      }
      if (level == 6) {
        printByte(row76);
      }
      if (level == 7) {
        printByte(row86);
      }
      break;

case Idle7:
      lc.clearDisplay(0);
      if (level == 0) {
        printByte(Starting);
      }
      if (level == 1) {
        printByte(Starting2);
      }
      if (level == 2) {
        if (spaces == 0) {
          printByte(Starting3);
        }
        if (spaces == 2) {
          printByte(row33);
        }
        if (spaces == 1) {
          printByte(row35);
        }
      }
      if (level == 3) {
        if (spaces == 1) {
          printByte(row45);
        }
        else {
          printByte(Starting4);
        }
      }
      if (level == 4) {
        if (spaces == 1) {
          printByte(row55);
        }
        else {
          printByte(Starting5);
        }
      }
      if (level == 5) {
        if (spaces == 1) {
          printByte(row65);
        }
        else {
          printByte(Starting6);
        }
      }
      if (level == 6) {
        printByte(row75);
      }
      if (level == 7) {
        printByte(row85);
      }
      break;

case Idle8:
      lc.clearDisplay(0);
      if (level == 0) {
        printByte(row12);
      }
      if (level == 1) {
        printByte(row22);
      }
      if (level == 2) {
        if (spaces == 0) {
          printByte(row32);
        }
        if (spaces == 2) {
          printByte(Starting3);
        }
        if (spaces == 1) {
          printByte(row34);
        }
      }
      if (level == 3) {
        if (spaces == 1) {
          printByte(row44);
        }
        else {
          printByte(row43);
        }
      }
      if (level == 4) {
        if (spaces == 1) {
          printByte(row54);
        }
        else {
          printByte(row53);
        }
      }
      if (level == 5) {
        if (spaces == 1) {
          printByte(row64);
        }
        else {
          printByte(row63);
        }
      }
      if (level == 6) {
        printByte(row74);
      }
      if (level == 7) {
        printByte(row84);
      }
      break;

case Idle9:
      lc.clearDisplay(0);
      if (level == 0) {
        printByte(row11);
      }
      if (level == 1) {
        printByte(row21);
      }
      if (level == 2) {
        if (spaces == 0) {
          printByte(row31);
        }
        if (spaces == 2) {
          printByte(row32);
        }
        if (spaces == 1) {
          printByte(row33);
        }
      }
      if (level == 3) {
        if (spaces == 1) {
          printByte(Starting4);
        }
        else {
          printByte(row42);
        }
      }
      if (level == 4) {
        if (spaces == 1) {
          printByte(Starting5);
        }
        else {
          printByte(row52);
        }
      }
      if (level == 5) {
        if (spaces == 1) {
          printByte(Starting6);
        }
        else {
          printByte(row62);
        }
      }
      if (level == 6) {
        printByte(Starting7);
      }
      if (level == 7) {
        printByte(Starting8);
      }
      break;

case Idle10:
      lc.clearDisplay(0);
      if (level == 0) {
        printByte(row12);
      }
      if (level == 1) {
        printByte(row22);
      }
      if (level == 2) {
        if (spaces == 0) {
          printByte(row32);
        }
        if (spaces == 2) {
          printByte(row31);
        }
        if (spaces == 1) {
          printByte(Starting3);
        }
      }
      if (level == 3) {
        if (spaces == 1) {
          printByte(row43);
        }
        else {
          printByte(row41);
        }
      }
      if (level == 4) {
        if (spaces == 1) {
          printByte(row53);
        }
        else {
          printByte(row51);
        }
      }
      if (level == 5) {
        if (spaces == 1) {
          printByte(row63);
        }
        else {
          printByte(row61);
        }
      }
      if (level == 6) {
        printByte(row73);
      }
      if (level == 7) {
        printByte(row83);
      }
      break;

case Idle11:
      lc.clearDisplay(0);
      if (level == 2) {
        if (spaces == 2 || spaces == 1) {
          printByte(row32);
        }
      }
      if (level == 3) {
        printByte(row42);
      }
      if (level == 4) {
        printByte(row52);
      }
      if (level == 5) {
        printByte(row62);
      }
      if (level == 6) {
        printByte(row72);
      }
      if (level == 7) {
        printByte(row82);
      }
      break;

case Idle12:
      lc.clearDisplay(0);
      if (level == 2) {
        if (spaces == 2) {
          printByte(Starting3);
        }
        if (spaces == 1) {
          printByte(row31);
        }
      }
      if (level == 3) {
        if (spaces == 1) {
          printByte(row41);
        }
        else {
          printByte(row43);
        }
      }
      if (level == 4) {
        if (spaces == 1) {
          printByte(row51);
        }
        else {
          printByte(row53);
        }
      }
      if (level == 5) {
        if (spaces == 1) {
          printByte(row61);
        }
        else {
          printByte(row63);
        }
      }
      if (level == 6) {
        printByte(row71);
      }
      if (level == 7) {
        printByte(row81);
      }
      break;

case Idle13:
      lc.clearDisplay(0);
      if (level == 2) {
        if (spaces == 1) {
          printByte(row32);
        }
      }
      if (level == 3) {
        if (spaces == 1) {
          printByte(row42);
        }
      }
      if (level == 4) {
        if (spaces == 1) {
          printByte(row52);
        }
      }
      if (level == 5) {
        if (spaces == 1) {
          printByte(row62);
        }
      }
      if (level == 6) {
        printByte(row72);
      }
      if (level == 7) {
        printByte(row82);
      }
      break;

case Idle14:
      lc.clearDisplay(0);
      if (level == 2) {
        if (spaces == 1) {
          printByte(Starting3);
        }
      }
      if (level == 3) {
        if (spaces == 1) {
          printByte(row43);
        }
      }
      if (level == 4) {
        if (spaces == 1) {
          printByte(row53);
        }
      }
      if (level == 5) {
        if (spaces == 1) {
          printByte(row63);
        }
      }
      if (level == 6) {
        printByte(row73);
      }
      if (level == 7) {
        printByte(row83);
      }
      break;

case Winner:
      cnt++;
      break;

    case Lose:
      cnt++;
      break;

    case Reset:
      break;

    case Moveup:
      break;

    case Hold:
      break; 
    
    default:
      break;

  }

return state;
}

enum States_sound {Start, Loss_sound};
int TickFct_Sound(int state) {
  switch (state) {
    case Start:
      state = Loss_sound;
      break;

    case Loss_sound:
      if (sound == 1) {
        tone(buzzer, 200);
      }
      if (sound == 0) {
        noTone(buzzer);
      }
      break;

    default:
      break;
  }

  switch (state) {
    case Start:
      break;

    case Loss_sound:
      break;

    default:
      break;
  }
  return state;
}

enum States_Joystick {Start3, MODES, SET_MODE};
int TickFct_Joystick(int state) {
  int val = analogRead(x_pin);
  switchval = digitalRead(SW_pin);

  
  switch (state) {
    case Start3:
      state = MODES;
      redoUp = false;
      break;

    case MODES:
      if (val <= 339) {
        goOn = 1;
        if(!switchval){
          state = SET_MODE;
        }
        else {
          state = MODES;
        }
      }
      else if (val > 339 && val <= 678) {
        goOn = 2;
        if(!switchval){
          state = SET_MODE;
        }
        else{
          state = MODES;
        }
      }
      else if (val > 678 && val <= 1023) {
        goOn = 3;
        if(!switchval){
          state = SET_MODE;
        }
        else{
          state = MODES;
        }
      }
      break;

    case SET_MODE:
    if(redoUp == false){
      state = SET_MODE;
    }
    else if(redoUp == true){
      state = Start3;
    }
      break;

    default:
      break;
  }
  switch (state) {
    case Start3:
      break;

    case MODES:
      if (goOn == 1) {
        digitalWrite(b0, HIGH);
        digitalWrite(b1, LOW);
        digitalWrite(b2, LOW);
      }
      else if (goOn == 2) {
        digitalWrite(b0, LOW);
        digitalWrite(b1, HIGH);
        digitalWrite(b2, LOW);
      }
      else if (goOn == 3) {
        digitalWrite(b0, LOW);
        digitalWrite(b1, LOW);
        digitalWrite(b2, HIGH);
      }
      
      break;

    case SET_MODE:
    
      if (goOn == 1) {
        digitalWrite(b0, HIGH);
        digitalWrite(b1, LOW);
        digitalWrite(b2, LOW);
        timelimit = 34;
        commence = true;
      }
      else if (goOn == 2) {
        digitalWrite(b0, LOW);
        digitalWrite(b1, HIGH);
        digitalWrite(b2, LOW);
        timelimit = 20;
        commence = true;
      }
      else if (goOn == 3) {
        digitalWrite(b0, LOW);
        digitalWrite(b1, LOW);
        digitalWrite(b2, HIGH);
        timelimit = 13;
        commence = true;
      }
      break;

    default:
      break;
  }
  return state;
}

enum States {Start4, clockCount};
int TickFct_GameTimer(int state) {
  switch(state){
    case Start4:
    timer = 0;
    timelimit = 0;
    timerstop = false;
    if(commence == true){
      state = clockCount;
    }
    else if(commence == false){
      state = Start4;
    }
    break;

    case clockCount: 
    if(timer > timelimit){
      timerstop = true;
    }
    else{
      timer++;
    }
    state = clockCount;
    break;

    default:
    break;
  }
  switch(state){
    case Start4:
    break;

    case clockCount:
    break;

    default:
    break;
  }
  return state;
}

void setup() {
lc.shutdown(0, false);      //The MAX72XX is in power-saving mode on startup
lc.setIntensity(0, 15);      // Set the brightness to maximum value
lc.clearDisplay(0);          // and clear the display

pinMode(buzzer, OUTPUT);
  pinMode(b0, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(b2, OUTPUT);
  digitalWrite(b0, LOW);
  digitalWrite(b1, LOW);
  digitalWrite(b2, LOW);
  pinMode(SW_pin, INPUT);
  pinMode(x_pin, INPUT);
  pinMode(y_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  Serial.begin(9600);

  unsigned char i = 0;
  tasks[i].state = Start2;
  tasks[i].period = 200;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &TickFct_Gameplay;
  i++;
  tasks[i].state = Start;
  tasks[i].period = 300;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &TickFct_Sound;
  i++;
  tasks[i].state = Start3;
  tasks[i].period = 200;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &TickFct_Joystick;
  i++;
  tasks[i].state = Start4;
  tasks[i].period = 300;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &TickFct_GameTimer;
  i++;
}

void printByte(byte character []) {

  int i = 0;
  for (i = 0; i < 8; i++)
  {
    lc.setRow(0, i, character[i]);
  }

}

void loop() {
  unsigned char i;
  for (i = 0; i < tasksNum; ++i) {
    if ( (millis() - tasks[i].elapsedTime) >= tasks[i].period) {
      tasks[i].state = tasks[i].TickFct(tasks[i].state);
      tasks[i].elapsedTime = millis(); // Last time this task was ran
    }
  }
  delay(100);
}
