#include "OliLedMatrix.h"
#include "numbers.h"

/* LED MATRIX PINS */
#define LED_LATCH 4
#define LED_DATA 6
#define LED_CLOCK 5

//setup pins for led Matrix
OliLedMatrix ledMatrix(LED_LATCH,LED_DATA,LED_CLOCK);

void setup() {

}

void loop() {
  
  int seconds = (millis() / 1000)% 100;
  
  ledMatrix.clear();
  
  ledMatrix.drawArray(1,2,Numbers[seconds/10],4);
  ledMatrix.drawArray(5,2,Numbers[seconds%10],4);
      
  ledMatrix.display();
}
