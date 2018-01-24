#include "MSG4LED.h"

// ----------------------------------
// Set & Init LEDs pins
// ----------------------------------
MSG4LED::MSG4LED (byte _blue, byte _red, byte _green, byte _yellow) {

  // Check pins number
  if (_blue >= 0)   { LEDS[0] = _blue; }
  if (_red >= 0)    { LEDS[1] = _red; }
  if (_green >= 0)  { LEDS[2] = _green; }
  if (_yellow >= 0) { LEDS[3] = _yellow; }
  
  // Init LEDs Array
  for (int i = 0; i < 4; i++) { 
    pinMode(LEDS[i], OUTPUT); 
    digitalWrite(LEDS[i], LOW);  
    }
  
  ChangeOrder(LEDS[0], LEDS[1], LEDS[2], LEDS[3]); // Apply change for LEDorder
}
// ==================================

// ----------------------------------
// Check LED pin in LEDS array and count them
// ----------------------------------
byte MSG4LED::CheckLEDs (byte ColorPin) {
  
  byte c = 0;
  
  for (int i = 0; i < 4; i++) {
    if (LEDS[i] == ColorPin) { c++; }
  }
  return c;
}
// ==================================

// ----------------------------------
// Change LEDs order
// ----------------------------------
void MSG4LED::ChangeOrder (byte _pos_1, byte _pos_2, byte _pos_3, byte _pos_4) {

  // Check pins number and apply new LEDorder value  
  if (CheckLEDs(_pos_1) > 0) { LEDorder[0] = _pos_1; } else { LEDorder[0] = LEDS[0]; }  
  if (CheckLEDs(_pos_2) > 0) { LEDorder[1] = _pos_2; } else { LEDorder[1] = LEDS[1]; }  
  if (CheckLEDs(_pos_3) > 0) { LEDorder[2] = _pos_3; } else { LEDorder[2] = LEDS[2]; }  
  if (CheckLEDs(_pos_4) > 0) { LEDorder[3] = _pos_4; } else { LEDorder[3] = LEDS[3]; }
  
}
// ==================================

// ----------------------------------
// Reset LEDs order
// ----------------------------------
void MSG4LED::ResetOrder () {  
  
  // LEDOrder as Init pins number  
  for (int i = 0; i < 4; i++) { LEDorder[i] = LEDS[i]; }  
  
}
// ==================================


// ----------------------------------
// ReMap Any digital to 4LED
// ----------------------------------
byte MSG4LED::ReMap (long x, long max_x) {
  
  byte ColorPin;
  
  if (x > max_x) {max_x = x;} // Correction for wrong value
  
  // Convert X-value, use a function called map()
  ColorPin = LEDorder[map(x, 0, max_x, 0, 4)];
  // (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
  
  return ColorPin;
  
}
// ==================================


// ----------------------------------
// Power On/Off LED
// ----------------------------------
void MSG4LED::PowerOnColor(byte ColorPin) {
  
  digitalWrite(ColorPin, !digitalRead(ColorPin));
  
}
// ==================================

// ----------------------------------
// Simple for Num
// ----------------------------------
void MSG4LED::PowerOnNum(byte OrderNum) {
  
  PowerOnColor(LEDorder[OrderNum-1]);
  
}
// ==================================

// ----------------------------------
// Power Off for All LEDs
// ----------------------------------
void MSG4LED::TurnOffLine() {
  
  for (int i = 0; i < 4; i++) {
    // Power off LED
    digitalWrite(LEDorder[i], LOW);
  }
}
// ==================================

// ----------------------------------
// Turn On/Off Line
// ----------------------------------
void MSG4LED::TurnOnLine () {
  
  TurnOffLine();
  for (int i = 0; i < 4; i++) {
    // Power On LED
    PowerOnColor (LEDorder[i]);
  }
}
// ==================================

// ----------------------------------
// Fill Line to Num
// ----------------------------------
void MSG4LED::FillTo (byte OrderNum, bool TurnOff) {
  
  if (TurnOff) { TurnOffLine();}
  
  if (OrderNum > 4) { OrderNum = 4; }
  
  for (int i = 0; i < OrderNum; i++) {
    // Power On LED
    PowerOnColor (LEDorder[i]);
  }
}
// ==================================

// ----------------------------------
// Fill Line from Num
// ----------------------------------
void MSG4LED::FillFrom (byte OrderNum, bool TurnOff) {
  
  if (TurnOff) { TurnOffLine();}
  
  if (OrderNum > 4) { OrderNum = 4; }
    else if (OrderNum == 0)  { OrderNum = 1; }
  
  for (int i = OrderNum-1; i < 4; i++) {
    // Power On LED
    PowerOnColor (LEDorder[i]);
  }
}
// ==================================

// ----------------------------------
// Blink By Color or Pin
// ----------------------------------
void MSG4LED::BlinkByColor(byte ColorPin, byte countBlink, unsigned long time) {

  for (int i = 0; i < countBlink; i++)
  {
    PowerOnColor(ColorPin);
    delay(time);
    PowerOnColor(ColorPin);
    delay(time);
  }
  
}
// ==================================

// ----------------------------------
// Blink By OrderNum
// ----------------------------------
void MSG4LED::BlinkByNum (byte OrderNum, byte countBlink, unsigned long time) {
  
  // Smart correction
  if (OrderNum > 4) { OrderNum = 4; }
  
  // Blink LED
  BlinkByColor (LEDorder[OrderNum-1], countBlink, time);
  
}
// ==================================

// ----------------------------------
// Blink Random
// ----------------------------------
void MSG4LED::BlinkRandom (byte countBlink, unsigned long time) {
  
  // Blink LED
  BlinkByColor (LEDorder[random(0,4)], countBlink, time);
  
}
// ==================================

// ----------------------------------
// Blink Line
// ----------------------------------
void MSG4LED::BlinkLine (unsigned long time) {
  
  TurnOffLine();
  for (int i = 0; i < 4; i++) {
    // Blink LED
    BlinkByColor (LEDorder[i], 1, time);
  }
}

// ----------------------------------
// Alias for BlinkLine (RTL mode)
void MSG4LED::BlinkLineRTL (unsigned long time) {
  
  BlinkLine (time);
  
}
// ==================================

// ----------------------------------
// Blink Line with LTR mode
// ----------------------------------
void MSG4LED::BlinkLineLTR (unsigned long time) {
  
  TurnOffLine();
  for (int i = 3; i >= 0; i--) {
    // Blink LED
    BlinkByColor (LEDorder[i], 1, time);
  }
}
// ==================================


// ----------------------------------
// Morse Code
// ----------------------------------
void MSG4LED::MorseCodeBlinkChar (long DigCode) {
  
  byte CurNum = 0;
  long RevCode = 0;
  byte x = 0;
  
  while (DigCode > 0) {
    CurNum = DigCode % 10;
    RevCode = RevCode+CurNum;
    DigCode = DigCode / 10;
    if (DigCode > 0) { RevCode = RevCode*10; }
    x++;
  } 
  Serial.print(F("x="));
  Serial.println(x);
  
  while (RevCode > 0) {
    CurNum = RevCode % 10;
    BlinkByNum (CurNum, 1);
    RevCode = RevCode / 10;
  } 
  
  for (int i = x; x <= 6; x++) { delay(1000); }
  
}
// ----------------------------------

void MSG4LED::MorseCode (String mcode) {
  
  mcode.toUpperCase();
  
  long DigCode;
  
  for (int i = 0; i < mcode.length(); i++)
    {
      switch (mcode.charAt(i)) {
        case 'A': DigCode = 13; break;
        case 'B': DigCode = 321; break;
        case 'C': DigCode = 3131; break;
        case 'D': DigCode = 32; break;
        case 'E': DigCode = 1; break;
        case 'F': DigCode = 231; break;
        case 'G': DigCode = 41; break;
        case 'H': DigCode = 22; break;
        case 'I': DigCode = 2; break;
        case 'J': DigCode = 143; break;
        case 'K': DigCode = 313; break;
        case 'L': DigCode = 132; break;
        case 'M': DigCode = 4; break;
        case 'N': DigCode = 31; break;
        case 'O': DigCode = 43; break;
        case 'P': DigCode = 141; break;
        case 'Q': DigCode = 413; break;
        case 'R': DigCode = 131; break;
        case 'S': DigCode = 21; break;
        case 'T': DigCode = 3; break;
        case 'U': DigCode = 23; break;
        case 'V': DigCode = 213; break;
        case 'W': DigCode = 14; break;
        case 'X': DigCode = 323; break;
        case 'Y': DigCode = 314; break;
        case 'Z': DigCode = 42; break;
        case '1': DigCode = 144; break;
        case '2': DigCode = 241; break;
        case '3': DigCode = 214; break;
        case '4': DigCode = 223; break;
        case '5': DigCode = 221; break;
        case '6': DigCode = 322; break;
        case '7': DigCode = 421; break;
        case '8': DigCode = 432; break;
        case '9': DigCode = 441; break;
        case '0': DigCode = 443; break;
        case ' ': DigCode = 2221; break;
        case '.': DigCode = 222; break;
        case ',': DigCode = 131313; break;
        case ':': DigCode = 4321; break;
        case ';': DigCode = 313131; break;
        case '(': case ')': DigCode = 31413; break;
        case '\'': DigCode = 1441; break;
        case '"': DigCode = 13231; break;
        case '-': DigCode = 3223; break;
        case '/': DigCode = 3231; break;
        case '?': DigCode = 242; break;
        case '!': DigCode = 424; break;
        case '@': DigCode = 14131; break;
        default: DigCode = 0; TurnOffLine(); break;
      }
      MorseCodeBlinkChar(DigCode);
    }
  
}
// ==================================

