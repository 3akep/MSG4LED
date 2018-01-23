#include <MSG4LED.h>

#define BLUE_4LED    5
#define RED_4LED     4
#define GREEN_4LED   3
#define YELLOW_4LED  2

MSG4LED my_leds (BLUE_4LED, RED_4LED, GREEN_4LED, YELLOW_4LED); // SET LEDs pins

//  SETUP Section
void setup() {

}
// end SETUP
// ---------------------


// MAIN LOOP
void loop() {
  
 my_leds.BlinkByColor(RED_4LED); // Blink Red LED
 
 delay(3000); // Delay for next function
 
 my_leds.BlinkLine(); // Blink each LED in the line with RTL mode
 
 my_leds.BlinkLineLTR(); // Blink each LED with LTR mode
 
 delay(3000); // Delay for next loop

}
// end LOOP
// ---------------------
