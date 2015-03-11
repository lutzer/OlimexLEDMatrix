/*
  OliLedMatrix is a Library to drive the Olimex 8x8 (non-rgb) matrix
  Created by Lutz Reiter, Dec 2014.
  Use it however you want to.
*/ 

#ifndef OliLedMatrix_h
#define OliLedMatrix_h

#define ROWS 8

#include "Arduino.h"

typedef unsigned char uchar;

class OliLedMatrix {
  
  public:
  
    OliLedMatrix(int latchPin, int dataPin, int clockPin) {
      this->dataPin = dataPin;
      this->latchPin = latchPin;
      this->clockPin = clockPin;
      
      pinMode (latchPin, OUTPUT);
      pinMode (clockPin, OUTPUT);
      pinMode (dataPin, OUTPUT);
      
      this->clear();
    }
    
    void setBrightness(uchar brightness) {
      this->brightness = brightness;
    }
    
    // clears matrix
    void clear() {
      for (int i=0;i<ROWS;i++)
        this->matrix[i] = 0;   
    }
    /* 
      draws an array to the matrix, one char represents one row with 8 columns
      x and y defines the offset where the input array should be drawn.
      rows is the lengh of the input array
    */
    void drawArray(int x, int y, const uchar *array, int rows) {
      for (int i=0; i<rows; i++)
	matrix[i+y] = matrix[i+y] | (array[i] >> x);
    }
    
    // draws a pixel
    void drawPixel(int x, int y) {
      if (y < ROWS && y >= 0)
        matrix[y] = matrix[y] | (1 << (8-x-1) );
    }
    
    // draws a rectangle
    void drawRectangle(int x, int y, int w, int h, boolean filled) {
      
      if (filled) {
        for(int i=y; i<=h; i++)
          for(int j=x; j<=w; j++)
             this->drawPixel(i,j);
      } else {
        for(int i=y; i<=h; i++) {
	  this->drawPixel(x,i);
	  this->drawPixel(x+w-1,i);
        }
        for(int i=x; i<=w; i++) {
  	  this->drawPixel(i,y);
  	  this->drawPixel(i,y+h-1);
        }  
      }
    }
    
    // shifts the data to the led-matrix to display it
    //the multiplexing has to be done by the arduino, so this function has to be called constantly
    void display() {
       for (byte i=0; i<ROWS; i++) {
         digitalWrite(this->latchPin, LOW);
         shiftOut(this->dataPin, this->clockPin, LSBFIRST, matrix[i]);
         shiftOut(this->dataPin, this->clockPin, LSBFIRST, 1 << i);
         digitalWrite(this->latchPin, HIGH);
         delayMicroseconds(2000);
       }
    }
    
  private:
  
    uchar matrix[ROWS];
    int latchPin,dataPin,clockPin;
    uchar brightness;
};

#endif
