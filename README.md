# MSG4LED
[Arduino Library] Control &amp; Message via 4 LEDs (**Dev Release**)

All in our World can be presented by 4 LEDs (BLUE, RED, GREEN, YELLOW), this is a Arduino-library can help you do it.

Описание функций на русском язык: http://amigors.com/msg4led/

## Structure Elements class MSG4LED**
**byte LEDS[]** - Pins LED Array

**byte LEDorder[]** - Pins LED Array (elements order used for some functions)


Init element class MSG4LED: 
**MSG4LED (BLUE, RED, GREEN, YELLOW)** - colors are pins number for same color

## Main Functions
**void ChangeOrder(byte, byte, byte, byte)** - parameters are pins number for LEDs, pins must contains in the init LEDs array

**void ResetOrder()** - reset order as in the init LEDs array

**byte ReMap(long x, long max_x)** - resolve any value ***X*** with maximum ***MAX_X*** to pins with define number from LEDOrder

### Power On/Off LEDs
**void PowerOnColor(byte ColorPin)** - ***ColorPin*** - pin number for change current LED status (on/off)

**void PowerOnNum(byte OrderNum)** - ***OrderNum*** (values: ***1-4***) - change current status for LED from LEDOrder array

**void TurnOffLine()** - force Turn off all LEDs

**void TurnOnLine()** - change current status for all LEDs


**void FillTo(byte OrderNum, bool TurnOff)** - change current status LEDs from 1 to ***OrderNum*** from LEDOrder array; boolean optional parameter ***TurnOff*** can set force Turn Off all LEDs before action (default: ***TurnOff*** = true)

**void FillFrom(byte OrderNum, bool TurnOff)** - change current status LEDs ***OrderNum*** to last 4 LED from LEDOrder array; boolean optional parameter ***TurnOff*** can set force Turn Off all LEDs before action (default: ***TurnOff*** = true)

### Blink LEDs
**void BlinkByColor(byte ColorPin, byte countBlink, unsigned long time)** - blink LED for ColorPin pins, with optional parameters: ***countBlink*** (default: ***1***) and ***TIME*** (default: ***1000***) - time for delay

**void BlinkByNum(byte OrderNum, byte countBlink, unsigned long time)** - blink LED for ***OrderNum*** (values: ***1-4***) pins from LEDOrder array, with optional parameters: ***countBlink*** (default: ***1***) and ***TIME*** (default: ***1000***) - time for delay

**void BlinkRandom(byte countBlink, unsigned long time)** - blink random LED from LEDOrder array, with optional parameters: ***countBlink*** (default: ***1***) and ***TIME*** (default: ***1000***) - time for delay

**void BlinkLine(unsigned long time)** or **void BlinkLineRTL(unsigned long time)** - blink all LEDs as series with ***Right-To-Left*** direction from LEDOrder array with delay defined in optional parameter ***TIME*** (default: ***1000***)

**void BlinkLineLTR(unsigned long time)** - blink all LEDs as series with ***Left-To-Right*** direction from LEDOrder array with delay defined in optional parameter ***TIME*** (default: ***1000***)


### Morse LED-Codes
Modified codes for Morse, where:

**"."** - BLUE Led (or #1 from LEDOrder Array)

**".."** - RED Led (or #2 from LEDOrder Array)

**"-"** - GREEN Led (or #3 from LEDOrder Array)

**"--"** - YELLOW Led (or #4 from LEDOrder Array)

**void MorseCode(String mcode)** - Blink Morse Codes for all chars from ***MCODE*** string

**void MorseCodeBlinkChar (long DigCode)** - uses for transform char to modified Morse codes ***DigCode*** and blink it
