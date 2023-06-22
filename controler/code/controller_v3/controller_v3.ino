#include <Gamepad.h>
Gamepad gp;

#include "ADS1X15.h"
ADS1115 ADS0(0x48);
ADS1115 ADS1(0x49);

#include "Mouse.h"
int range = 20;               // output range of X or Y movement
int responseDelay = 5;        // response delay of the mouse, in ms
int threshold = range / 4;    // resting threshold
int center = range / 2;       // resting position value

#include "Keyboard.h"

void setup() {
  Keyboard.begin();
  Serial.begin(115200);
  ADS0.begin();
  ADS1.begin();
  
  //pinMode(0, INPUT_PULLUP);
  //pinMode(1, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  
  pinMode(10, INPUT_PULLUP);
  pinMode(14, INPUT_PULLUP);
  pinMode(15, INPUT_PULLUP);
  pinMode(16, INPUT_PULLUP);

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
}

void loop() {
  // keybord();
  controller();
  }
void controller(){
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
  //int x = !digitalRead(0);
  //int z = !digitalRead(1);
  int Start = !digitalRead(4);
  int Select = !digitalRead(5);
  int LB = !digitalRead(6);
  int LT = !digitalRead(7);
  int RB = !digitalRead(8);
  int RT = !digitalRead(9);
  int i = !digitalRead(16);
  int j = !digitalRead(10);
  gp.setButtonState(8, Start);
  gp.setButtonState(9, Select);
  gp.setButtonState(12, LB);
  gp.setButtonState(13, LT);
  gp.setButtonState(14, RB);
  gp.setButtonState(15, RT);
  gp.setButtonState(16, i);
  gp.setButtonState(17, j);
  //gp.setButtonState(16, x);
  //gp.setButtonState(17, z);

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
  }
void keybord(){
  int xReading = map(analogRead(A0), 0, 1023, range, 0) - center;
  int yReading = map(analogRead(A1), 0, 1023, 0, range) - center;
  if (abs(xReading) < threshold) {
    xReading = 0;
  }
  if (abs(yReading) < threshold) {
    yReading = 0;
  }
  
  Mouse.move(xReading, yReading, 0);
  if (!digitalRead(15) == HIGH) {
    if (!Mouse.isPressed(MOUSE_RIGHT)) {
      Mouse.press(MOUSE_RIGHT);
    }
  }
  else {
    if (Mouse.isPressed(MOUSE_RIGHT)) {
      Mouse.release(MOUSE_RIGHT);
    }
  }
  
  if (!digitalRead(14) == HIGH) {
    if (!Mouse.isPressed(MOUSE_LEFT)) {
      Mouse.press(MOUSE_LEFT);
    }
  }
  else {
    if (Mouse.isPressed(MOUSE_LEFT)) {
      Mouse.release(MOUSE_LEFT);
    }
  }

  ADS0.setGain(0);
  ADS1.setGain(0);
  // ABXY
  int16_t A = ADS0.readADC(0);  
  if(A < 0){A = Keyboard.write('A');}
  int16_t B = ADS0.readADC(1);  
  if(B < 0){B = Keyboard.write('B');}
  int16_t X = ADS0.readADC(2);  
  if(X < 0){X = Keyboard.write('X');}
  int16_t Y = ADS0.readADC(3);
  if(Y < 0){Y = Keyboard.write('Y');}
  // pad
  int16_t up = ADS1.readADC(0);  
  if(up < 0){up = Keyboard.write('u');}
  int16_t down = ADS1.readADC(1);  
  if(down < 0){down = Keyboard.write('d');}
  int16_t left = ADS1.readADC(2);  
  if(left < 0){left = Keyboard.write('l');}
  int16_t right = ADS1.readADC(3);
  if(right < 0){right = Keyboard.write('r');}

  // start select
  if (!digitalRead(4) == HIGH) {
    Keyboard.write('S');
  }
  if (!digitalRead(5) == HIGH) {
    Keyboard.write('s');
  }
  
  delay(responseDelay);
}
