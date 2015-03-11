#include "OliLedMatrix.h"

/* LED MATRIX PINS */
#define LED_LATCH 4
#define LED_DATA 6
#define LED_CLOCK 5

//setup pins for led Matrix
OliLedMatrix ledMatrix(LED_LATCH,LED_DATA,LED_CLOCK);

void setup() {

}

void loop() {
  
  unsigned long time = millis();
  
  ledMatrix.clear();
  
  if (time%1000 < 100)
      //draws a rectangle at position 3,3 with height 2 and width 2
      ledMatrix.drawRectangle(3,3,2,2); 
  else if (time%1000 < 200)
      ledMatrix.drawRectangle(2,2,4,4);
  else if (time%1000 < 300)
      ledMatrix.drawRectangle(1,1,6,6);
  else if (time%1000 < 300)
      ledMatrix.drawRectangle(0,0,8,8);
      
  ledMatrix.display();
}
