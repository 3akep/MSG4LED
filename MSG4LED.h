/*
  MSG4LED Arduino Library
*/
#ifndef MSG4LED_h

#define MSG4LED_h

#include "Arduino.h"


class MSG4LED
{
    private:
      byte LEDS[4] = {2, 3, 4, 5}; // BLUE, RED, GREEN, YELLOW
      byte LEDorder[4] =  {2, 3, 4, 5};

    
    public:
      MSG4LED (byte _blue = 2, byte _red = 3, byte _green = 4, byte _yellow = 5); // Init LEDs pins
      
      // Check Pin present in LEDS array
      byte CheckLEDs (byte ColorPin);
      
      // Change LEDs Order
      void ChangeOrder (byte _pos_1, byte _pos_2, byte _pos_3, byte _pos_4);
      // Reset LEDs Order      
      void ResetOrder ();
  
      // ReMap any Digital value to 4LED
      byte ReMap (long x, long max_x);
      //long map(long x, long in_min, long in_max, long out_min, long out_max)
      
      // Power On/Off LED 
      void PowerOnColor (byte ColorPin); // by Color
      void PowerOnNum (byte OrderNum); // by Order
      void TurnOffLine (); // Turn Off All 
      void TurnOnLine ();  // Turn On Line
      void FillTo (byte OrderNum, bool TurnOff = true); // Turn On to OrderNum pin
      void FillFrom (byte OrderNum, bool TurnOff = true); // Turn On from OrderNum pin
          
      // Blink by COLOR (or Pin Number)
      void BlinkByColor (byte ColorPin, byte countBlink = 1, unsigned long time = 1000);
      // Blink by Number
      void BlinkByNum (byte OrderNum, byte countBlink = 1, unsigned long time = 1000);
      // Blink Random
      void BlinkRandom (byte countBlink = 1, unsigned long time = 1000);
      
      // Run Line (to Right)
      // for change blink order use ChangeOrder
      void BlinkLine (unsigned long time = 1000);
      void BlinkLineRTL (unsigned long time = 1000); // Right-To-Left mode (as default BlinkLine)
      void BlinkLineLTR (unsigned long time = 1000); // Left-To-Right mode
      
      // Blink Morse Code
      void MorseCode (String mcode);
      void MorseCodeBlinkChar (long DigCode);
      

};

#endif
