/*
 * Arduino Sketch for 2/16/20 v3 PCB 
 * 
 * All design v2 code by Craig Gardner, LeafCutterLabs
 * https://github.com/LeafCutterLabs/miniMACRO5
 * 
 * code updated for v3 by Louis McElveen
 */
 

#include "HID-Project.h"
#include <SimpleRotary.h>

const int buttonPin1 = 21;
const int buttonPin2 = 10;
const int buttonPin3 = 16;
const int buttonPin4 = 6;
const int buttonPin5 = 8;

int buttonState1 = 0;
int buttonState2 = 0;
int buttonState3 = 0;
int buttonState4 = 0;
int buttonState5 = 0;

int prevButtonState1 = HIGH;
int prevButtonState2 = HIGH;
int prevButtonState3 = HIGH;
int prevButtonState4 = HIGH;
int prevButtonState5 = HIGH;

int CW  = 1;    // 0 = not turning, 1 = CW, 2 = CCW
int CCW = 2;

SimpleRotary rotaryA(20,1,21); // Pin A, Pin B, Button Pin
SimpleRotary rotaryB(0,19,10); // Pin A, Pin B, Button Pin
SimpleRotary rotaryC(2,1,18); // Pin A, Pin B, Button Pin
SimpleRotary rotaryD(3,4,6); // Pin A, Pin B, Button Pin
SimpleRotary rotaryE(7,5,8); // Pin A, Pin B, Button Pin

void setup() {
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
  pinMode(buttonPin4, INPUT_PULLUP);
  pinMode(buttonPin5, INPUT_PULLUP);

  digitalWrite(buttonPin1, HIGH);
  digitalWrite(buttonPin2, HIGH);
  digitalWrite(buttonPin3, HIGH);
  digitalWrite(buttonPin4, HIGH);
  digitalWrite(buttonPin4, HIGH);
  
  Keyboard.begin();
}

void loop() {

  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  buttonState3 = digitalRead(buttonPin3);
  buttonState4 = digitalRead(buttonPin4);
  buttonState5 = digitalRead(buttonPin5);

// this is the button if you have a switch or an encoder
  if ((buttonState1 != prevButtonState1) && (buttonState1 == HIGH)) {   // If a button switches to high
    Consumer.write(MEDIA_VOL_MUTE);   // Mute
    delay(100); // debounce
  }
    prevButtonState1 = buttonState1; // reset button to low

  if ((buttonState2 != prevButtonState2) && (buttonState2 == HIGH)) {
    NKROKeyboard.add(KEY_LEFT_CTRL);  // undo
    NKROKeyboard.add('z');
    NKROKeyboard.send();
    NKROKeyboard.releaseAll();
    delay(100);
  }
    prevButtonState2 = buttonState2;
    
  if ((buttonState3 != prevButtonState3) && (buttonState3 == HIGH)) {
    NKROKeyboard.add(KEY_LEFT_CTRL);  // redo
    NKROKeyboard.add('y');
    NKROKeyboard.send();
    NKROKeyboard.releaseAll();
    delay(100);
  }
    prevButtonState3 = buttonState3;
  
  if ((buttonState4 != prevButtonState4) && (buttonState4 == HIGH)) {
    NKROKeyboard.add(KEY_LEFT_CTRL);  // copy
    NKROKeyboard.add('c');
    NKROKeyboard.send();
    NKROKeyboard.releaseAll();
    delay(100);
  }
    prevButtonState4 = buttonState4;
  
  if ((buttonState5 != prevButtonState5) && (buttonState5 == HIGH)) {
    NKROKeyboard.add(KEY_LEFT_CTRL);  // paste
    NKROKeyboard.add('v');
    NKROKeyboard.send();
    NKROKeyboard.releaseAll();
    delay(100);
  }
    prevButtonState5 = buttonState5;

    // for all modifiers go to: https://www.arduino.cc/en/Reference/KeyboardModifiers
    
  
  byte rotA, rotB, rotC, rotD, rotE;

  rotA = rotaryA.rotate();
  rotB = rotaryA.rotate(); 
  rotC = rotaryB.rotate();
  rotD = rotaryC.rotate();
  rotE = rotaryD.rotate();

// volume up/down
  if ( rotA == CW ) {
    Consumer.write(MEDIA_VOL_UP);
  }
  if ( rotA == CCW ) {
    Consumer.write(MEDIA_VOL_DOWN);
  }
    
//  zooming in/out   
  if ( rotB == CW ) {
    NKROKeyboard.add(KEY_LEFT_CTRL);
    NKROKeyboard.send();
    Mouse.move(0, 0, 30);    
    NKROKeyboard.releaseAll();
  }
  if ( rotB == CCW ) {
    NKROKeyboard.add(KEY_LEFT_CTRL);
    NKROKeyboard.send();
    Mouse.move(0, 0, -30);    
    NKROKeyboard.releaseAll(); 
  }
 
 // scrolling up/down 
  if ( rotC == CW ) {
    Mouse.move(0, 0, 5);   
  }
  if ( rotC == CCW ) {
    Mouse.move(0, 0, -5);   
  }
  
// previous/next window
  if ( rotD == CW ) {
    NKROKeyboard.add(KEY_LEFT_ALT);
    NKROKeyboard.add(KEY_TAB);
    NKROKeyboard.send();
    NKROKeyboard.releaseAll();
    delay(300);
  }
  if ( rotD == CCW ) {
    NKROKeyboard.add(KEY_LEFT_ALT);
    NKROKeyboard.add(KEY_LEFT_SHIFT);
    NKROKeyboard.add(KEY_TAB);
    NKROKeyboard.send();
    NKROKeyboard.releaseAll();
    delay(300);
  }

// previous/next tab
  if ( rotE == CW ) {
    NKROKeyboard.add(KEY_LEFT_CTRL);
    NKROKeyboard.add(KEY_TAB);
    NKROKeyboard.send();
    NKROKeyboard.releaseAll();
    delay(100);
  }
  if ( rotE == CCW ) {
    NKROKeyboard.add(KEY_LEFT_CTRL);
    NKROKeyboard.add(KEY_LEFT_SHIFT);
    NKROKeyboard.add(KEY_TAB);
    NKROKeyboard.send();
    NKROKeyboard.releaseAll();
    delay(100);
  }

}
