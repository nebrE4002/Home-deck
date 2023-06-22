#include <Gamepad.h>
Gamepad gp;

#include "ADS1X15.h"
ADS1115 ADS0(0x48);
ADS1115 ADS1(0x49);


void setup() {
  Serial.begin(115200);
  ADS0.begin();
  ADS1.begin();
  
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);

  pinMode(14, INPUT_PULLUP);
  pinMode(15, INPUT_PULLUP);

  
  pinMode(16, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
}

void loop() {
  ADS0.setGain(0);
  ADS1.setGain(0);

  // ABXY
  int16_t A = ADS0.readADC(0);  
  if(A < 0){A = true;}else{A = false;}
  int16_t B = ADS0.readADC(1);  
  if(B < 0){B = true;}else{B = false;}
  int16_t X = ADS0.readADC(2);  
  if(X < 0){X = true;}else{X = false;}
  int16_t Y = ADS0.readADC(3);
  if(Y < 0){Y = true;}else{Y = false;}
  //Serial.print("\tAnalog0: "); Serial.println(A);
  gp.setButtonState(0, A);
  gp.setButtonState(1, B);
  gp.setButtonState(2, X);
  gp.setButtonState(3, Y);

  // pad
  int16_t up = ADS1.readADC(0);  
  if(up < 0){up = true;}else{up = false;}
  int16_t down = ADS1.readADC(1);  
  if(down < 0){down = true;}else{down = false;}
  int16_t left = ADS1.readADC(2);  
  if(left < 0){left = true;}else{left = false;}
  int16_t right = ADS1.readADC(3);
  if(right < 0){right = true;}else{right = false;}
  gp.setButtonState(4, up);
  gp.setButtonState(5, down);
  gp.setButtonState(6, left);
  gp.setButtonState(7, right);

  // start select
  int Start = !digitalRead(4);
  int Select = !digitalRead(5);
  gp.setButtonState(8, Start);
  gp.setButtonState(9, Select);

  // joysticks
  int lx;
  int ly;
  lx = analogRead(A0);
  ly = analogRead(A1);
  //we need to convert a 0-1000 to -127 - 127
  lx = floor((lx - 500) * 0.254);
  ly = floor((ly - 500) * 0.254);
  if(lx > 127) lx = 127;
  if(ly > 127) ly = 127;
  gp.setLeftXaxis(lx);
  gp.setLeftYaxis(ly);
  gp.setButtonState(10, !digitalRead(15));
  
  int rx, ry;
  rx = analogRead(A2);
  ry = analogRead(A3);
  //we need to convert a 0-1000 to -127 - 127
  rx = floor((rx - 500) * 0.254);
  ry = floor((ry - 500) * 0.254);
  if(rx > 127) rx = 127;
  if(ry > 127) ry = 127;
  gp.setRightXaxis(rx);
  gp.setRightYaxis(ry);
  gp.setButtonState(11, !digitalRead(14));

  // scholderbutton 
  int LB = !digitalRead(6);
  int LT = !digitalRead(7);
  int RB = !digitalRead(8);
  int RT = !digitalRead(9);
  gp.setButtonState(12, LB);
  gp.setButtonState(13, LT);
  gp.setButtonState(14, RB);
  gp.setButtonState(15, RT);
  
  // scholderbutton 
  int i = !digitalRead(16);
  int j = !digitalRead(10);
  gp.setButtonState(16, i);
  gp.setButtonState(17, j);

}
