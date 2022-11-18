/*  Code by JacTech

For unexperienced programmers:
you can change the colors, delays and what each button does in the Customiseable section below

For experienced programmers:
Change whatever you want and dont judge my code :D
*/

#include <ClickEncoder.h>
#include <TimerOne.h>
#include <HID-Project.h>
#include <Adafruit_NeoPixel.h>

#define HID_CUSTOM_LAYOUT
#define LAYOUT_GERMAN

#define NUMPIXELS 8
#define PIN 13
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define ENCODER_CLK1 A0
#define ENCODER_DT1 A4
#define ENCODER_SW1 A2

#define ENCODER_CLK2 A3
#define ENCODER_DT2 A1
#define ENCODER_SW2 A5

int Bu1 = 12;
int B2 = 4;
int B3 = 2;
int B4 = 6;
int B5 = 7;
int B6 = 8;
int B7 = 11;
int B8 = 5;

boolean Standby = 0;

int RGBSelect = 0;
int ShiftSelect = 0;

ClickEncoder *encoder2;
int16_t last2, value2;

ClickEncoder *encoder1;
int16_t last1, value1;

void timerIsr() {
  encoder1->service();
  encoder2->service();
}


//----------------------------------------------------------------Customiseable----------------------------------------------------------------

int Shift = 1;                          //The mode, that the keyboard will start with
int FadeDelay = 100;                        //The LED Animation speed when you turn the keyboard on or switch to a nother shift mode
int PressDelay = 250;                       //Delay between actions if the button is pressed down (to smal values may result in double presses)
int LEDDelay = 100;                         //How long the led will blink up if a key is pressed
int InputDelay = 5;                         //The delay between the keys that get sent to the PC
int Shift0[3] = { 0, 155, 30 };             //The color for Mode 0  {R, G, B}
int Shift1[3] = { 155, 30, 0 };             //The color for Mode 1  {R, G, B}
int LEDBlinkColour[3] = { 255, 255, 255 };  //The colour that will flash if a key is pressed {R, G, B}

void Button1() {  //0 = Media Previous       1 = Turn off lights (sleep mode)

  if (Shift == 0) {
    Consumer.write(MEDIA_PREVIOUS);
  }
  if (Shift == 1) {
    if (Standby == 0) {
      for (int i = 0; i < 8; i++) {
        pixels.setPixelColor(i, pixels.Color(0, 0, 0));
        pixels.show();
      }
      Standby = 1;
    } else {
      for (int i = 0; i < 8; i++) {
        pixels.setPixelColor(i, pixels.Color(Shift1[0], Shift1[1], Shift1[2]));
        pixels.show();
      }
      Standby = 0;
    }
  }
  if (Shift == 3) {
    RGBSelect = 0;
    if (ShiftSelect == 0){
      value2 = Shift0[0];
    }
    if (ShiftSelect == 1){
      value2 = Shift1[0];
    }
  }
}
void Button2() {  //0 = Media Pause          1 = Snaps window to the left

  if (Shift == 0) {
    Consumer.write(MEDIA_PLAY_PAUSE);
  }
  if (Shift == 1) {
    Keyboard.press(KEY_LEFT_GUI);
    delay(InputDelay);
    Keyboard.write(KEY_LEFT_ARROW);
    delay(InputDelay);
    Keyboard.releaseAll();
  }
  if (Shift == 3) {
    RGBSelect = 1;
        if (ShiftSelect == 0){
      value2 = Shift0[1];
    }
    if (ShiftSelect == 1){
      value2 = Shift1[1];
    }
  }
}
void Button3() {  //0 = Media Next           1 = Snaps window to the right

  if (Shift == 0) {
    Consumer.write(MEDIA_NEXT);
  }
  if (Shift == 1) {
    Keyboard.press(KEY_LEFT_GUI);
    delay(InputDelay);
    Keyboard.write(KEY_RIGHT_ARROW);
    delay(InputDelay);
    Keyboard.releaseAll();
  }
  if (Shift == 3) {
    RGBSelect = 2;
    if (ShiftSelect == 0){
      value2 = Shift0[3];
    }
    if (ShiftSelect == 1){
      value2 = Shift1[3];
    }
  }
}
void Button4() {  //0 = Media Mute           1 = Password (default is #HELLOWorld123)

  if (Shift == 0) {
    Consumer.write(MEDIA_VOLUME_MUTE);
  }
  if (Shift == 1) {
    Keyboard.write(35);  //#
    delay(InputDelay);
    Keyboard.press(KEY_LEFT_SHIFT);
    delay(InputDelay);
    Keyboard.write('h');
    delay(InputDelay);
    Keyboard.write('e');
    delay(InputDelay);
    Keyboard.write('l');
    delay(InputDelay);
    Keyboard.write('l');
    delay(InputDelay);
    Keyboard.write('o');
    delay(InputDelay);
    Keyboard.write('w');
    delay(InputDelay);
    Keyboard.release(KEY_LEFT_SHIFT);
    Keyboard.write('o');
    delay(InputDelay);
    Keyboard.write('r');
    delay(InputDelay);
    Keyboard.write('l');
    delay(InputDelay);
    Keyboard.write('d');
    delay(InputDelay);
    Keyboard.write('1');
    delay(InputDelay);
    Keyboard.write('2');
    delay(InputDelay);
    Keyboard.write('3');
    delay(InputDelay);
  }
  if (Shift == 3) {
    pixels.setPixelColor(3, pixels.Color(0, 0, 0));
    if (ShiftSelect == 0) {
      Shift0[0] = 0;
      Shift0[1] = 0;
      Shift0[2] = 0;
    }
    if (ShiftSelect == 1) {
      Shift1[0] = 0;
      Shift1[1] = 0;
      Shift1[2] = 0;
    }

  }
}
void Button5() {  //Switches to the last tab that was open no matter if shift is 1 or 0
  
  if (Shift <= 1) { //in Shift mode 1 or 0

  Keyboard.press(KEY_LEFT_ALT);
  delay(InputDelay);
  Keyboard.press(KEY_TAB);
  delay(InputDelay);
  Keyboard.release(KEY_TAB);
  delay(InputDelay);
  Keyboard.release(KEY_LEFT_ALT);
  }
 
  if (Shift == 3) {
    ShiftSelect = 0;
  }
}
void Button6() {  //0 = Go to desktop        1 = Maximise window
  if (Shift == 0) {
    Keyboard.press(KEY_LEFT_GUI);
    delay(InputDelay);
    Keyboard.press('d');
    delay(InputDelay);
    Keyboard.releaseAll();
  }
  if (Shift == 1) {
    Keyboard.press(KEY_LEFT_GUI);
    delay(InputDelay);
    Keyboard.write(KEY_UP_ARROW);
    delay(InputDelay);
    Keyboard.releaseAll();
  }
  if (Shift == 3) {
    ShiftSelect = 1;
  }
}
void Button7() {  //0 = Takes a screenshot   1 = Open clipboard

  if (Shift == 0) {
    Keyboard.press(KEY_LEFT_GUI);
    delay(InputDelay);
    Keyboard.press(KEY_LEFT_SHIFT);
    delay(InputDelay);
    Keyboard.press('s');
    delay(InputDelay);
    Keyboard.releaseAll();
  }
  if (Shift == 1) {
    Keyboard.press(KEY_LEFT_GUI);
    delay(InputDelay);
    Keyboard.press('v');
    delay(InputDelay);
    Keyboard.releaseAll();
  }
}
void Button8() {  //Changes between shift mode 0 and 1

  if (Shift == 0) {
    Shift = 1;
  } 
  else {
      Shift = 0;
  }
}

//--------------------------------------------------------Not Customiseable--------------

void LEDFade() {

  if (Shift == 0) {
    for (int i = 7; i != -1;) {
      pixels.setPixelColor(i, pixels.Color(Shift0[0], Shift0[1], Shift0[2]));
      pixels.show();
      delay(FadeDelay);
      i = i - 1;
    }
  }
  if (Shift == 1) {
    for (int i = 7; i != -1;) {
      pixels.setPixelColor(i, pixels.Color(Shift1[0], Shift1[1], Shift1[2]));
      pixels.show();
      delay(FadeDelay);
      i = i - 1;
    }
  }
}
void LEDBlink() {

  if (Shift == 0) {
    for (int i = 0; i < 8; i++) {
      pixels.setPixelColor(i, pixels.Color(Shift0[0], Shift0[1], Shift0[2]));
      pixels.show();
    }
  }
  if (Shift == 1) {
    for (int i = 0; i < 8; i++) {
      pixels.setPixelColor(i, pixels.Color(Shift1[0], Shift1[1], Shift1[2]));
      pixels.show();
    }
  }
  if (Shift == 3) {
      pixels.setPixelColor(0, pixels.Color(255, 0, 0));
      pixels.setPixelColor(1, pixels.Color(0, 255, 0));
      pixels.setPixelColor(2, pixels.Color(0, 0, 255));
      pixels.setPixelColor(3, pixels.Color(0, 0, 0));
      pixels.setPixelColor(7, pixels.Color(255, 0, 0));
      pixels.setPixelColor(4, pixels.Color(Shift0[0], Shift0[1], Shift0[2]));
      pixels.setPixelColor(5, pixels.Color(Shift1[0], Shift1[1], Shift1[2]));
    if (ShiftSelect == 0) {
      pixels.setPixelColor(6, pixels.Color(Shift0[0], Shift0[1], Shift0[2]));
    }
    if (ShiftSelect == 1) {
      pixels.setPixelColor(6, pixels.Color(Shift1[0], Shift1[1], Shift1[2]));
    }
     pixels.show();
  }
}

void RGBChange() {

}

void setup() {

  encoder1 = new ClickEncoder(ENCODER_DT1, ENCODER_CLK1, ENCODER_SW1, 4);
  encoder2 = new ClickEncoder(ENCODER_DT2, ENCODER_CLK2, ENCODER_SW2, 4);

  Timer1.initialize(1000);
  Timer1.attachInterrupt(timerIsr);
  last1 = -1;
  last2 = -1;

  pinMode(Bu1, INPUT);
  pinMode(B2, INPUT);
  pinMode(B3, INPUT);
  pinMode(B4, INPUT);
  pinMode(B5, INPUT);
  pinMode(B6, INPUT);
  pinMode(B7, INPUT);
  pinMode(B8, INPUT);

  Serial.begin(9600);
  Consumer.begin();
  pixels.begin();
  pixels.clear();

  for (int i = 0; i < 8; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 150));
    pixels.show();
    delay(FadeDelay);
  }
  delay(LEDDelay);

  LEDFade();
}
void loop() {

  value1 += encoder1->getValue();
  if (value1 != last1) {
    if (last1 < value1)
      Consumer.write(MEDIA_VOLUME_UP);
    else
      Consumer.write(MEDIA_VOLUME_DOWN);
    last1 = value1;
    Serial.print("Encoder Value: ");
    Serial.println(value1);
  }
  value2 += encoder2->getValue();
  if (Shift != 3){
  if (value2 != last2) {
    if (last2 < value2)
      Keyboard.write(KEY_RIGHT_ARROW);
    else
      Keyboard.write(KEY_LEFT_ARROW);

    last2 = value2;
    Serial.print("Encoder Value: ");
    Serial.println(value2);
   }
  }
  else {
    
    if (value2 != last2) {
      if (last2 < value2)
      last2 = value2;
    Serial.print("Encoder Value: ");
    Serial.println(value2);
    if (value2 > 255){
      value2 = 255;
    }
    if (value2 < 0){
      value2 = 0;
    }
  

   if (ShiftSelect == 0){
      Shift0[RGBSelect] = value2;  
      LEDBlink();
    }
   }
      if (ShiftSelect == 1){
      Shift1[RGBSelect] = value2; 
      LEDBlink();
    } 
   }
  
  ClickEncoder::Button b = encoder1->getButton();
  if (b != ClickEncoder::Open) {

    switch (b) {
      case ClickEncoder::Clicked:
        Consumer.write(MEDIA_PLAY_PAUSE);
        break;

      case ClickEncoder::DoubleClicked:
        Consumer.write(MEDIA_NEXT);
        break;
    }
  }
  ClickEncoder::Button c = encoder2->getButton();
  if (c != ClickEncoder::Open) {

    switch (c) {
      case ClickEncoder::Clicked:
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.write('v');
        Keyboard.release(KEY_LEFT_CTRL);
        break;

      case ClickEncoder::DoubleClicked:
        Shift = 3;
        break;
       
    }
  }

  if (digitalRead(Bu1) == LOW) {
    pixels.setPixelColor(0, pixels.Color(LEDBlinkColour[0], LEDBlinkColour[1], LEDBlinkColour[2]));
    pixels.show();
    Button1();
    delay(LEDDelay);
    if (Shift != 1) {
      LEDBlink();
    }
  
    delay(PressDelay - LEDDelay);
  }
  if (digitalRead(B2) == LOW) {
    pixels.setPixelColor(1, pixels.Color(LEDBlinkColour[0], LEDBlinkColour[1], LEDBlinkColour[2]));
    pixels.show();
    Button2();
    delay(LEDDelay);
    LEDBlink();
    delay(PressDelay - LEDDelay);
  }
  if (digitalRead(B3) == LOW) {
    pixels.setPixelColor(2, pixels.Color(LEDBlinkColour[0], LEDBlinkColour[1], LEDBlinkColour[2]));
    pixels.show();
    Button3();
    delay(LEDDelay);
    LEDBlink();
    delay(PressDelay - LEDDelay);
  }
  if (digitalRead(B4) == LOW) {

    pixels.setPixelColor(3, pixels.Color(LEDBlinkColour[0], LEDBlinkColour[1], LEDBlinkColour[2]));
    pixels.show();
    Button4();
    delay(LEDDelay);
    LEDBlink();
    delay(PressDelay - LEDDelay);
  }
  if (digitalRead(B5) == LOW) {

    pixels.setPixelColor(4, pixels.Color(LEDBlinkColour[0], LEDBlinkColour[1], LEDBlinkColour[2]));
    pixels.show();
    Button5();
    delay(LEDDelay);
    LEDBlink();
    delay(PressDelay - LEDDelay);
  }
  if (digitalRead(B6) == LOW) {

    pixels.setPixelColor(5, pixels.Color(LEDBlinkColour[0], LEDBlinkColour[1], LEDBlinkColour[2]));
    pixels.show();
    Button6();
    delay(LEDDelay);
    LEDBlink();
    delay(PressDelay - LEDDelay);
  }
  if (digitalRead(B7) == LOW) {

    pixels.setPixelColor(6, pixels.Color(LEDBlinkColour[0], LEDBlinkColour[1], LEDBlinkColour[2]));
    pixels.show();
    Button7();
    delay(LEDDelay);
    LEDBlink();
    delay(PressDelay - LEDDelay);
  }
  if (digitalRead(B8) == LOW) {

    pixels.setPixelColor(7, pixels.Color(LEDBlinkColour[0], LEDBlinkColour[1], LEDBlinkColour[2]));
    pixels.show();
    Button8();
    delay(LEDDelay);
    LEDFade();
    delay(PressDelay - LEDDelay);
  }
}