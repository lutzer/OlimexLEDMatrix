/*
  OliLedMatrix is a Library to drive one Olimex 8x8 rgb matrix
  Created by Lutz Reiter, Dec 2014.
  Use it however you want to.
 
  The standard SPI pins are: CLOCK: 13, DATA: 10 on Arduinon Uno and Duemilanove, 
  see http://arduino.cc/en/Reference/SPI for other models
 */
 
#ifndef OliLedMatrixRGB_h
#define OliLedMatrixRGB_h

#define ROWS 8

#include "Arduino.h"
#include "SPI.h"

typedef unsigned char uchar;

enum LedColor {
  Blue = 1, //001
  Green = 2, //010
  Cyan = 3, //011
  Red = 4, //100
  Purple = 5, //101
  Yellow = 6, //110
  White = 7 //111
};

class OliLedMatrixRGB {

public:

  OliLedMatrixRGB(int latchPin) {
    this->latchPin = latchPin;
    pinMode (latchPin, OUTPUT);
    
    //SPI.setDataMode(SPI_MODE1);
    SPI.setClockDivider(SPI_CLOCK_DIV64);
    SPI.begin();
    
    this->color = White;

    this->clear();
  }

  void clear() {
    for (int i=0;i<ROWS*3;i++)
      this->matrix[i] = 0;   
  }
  
  void setColor(LedColor color) {
    this->color = color;
  }

  void drawPixel(int x, int y) {
    if (y < ROWS && y >= 0) {
      
      // reset color
      matrix[3*y] &= ~(1 << (8-x-1));
      matrix[3*y+1] &= ~(1 << (8-x-1));
      matrix[3*y+2] &= ~(1 << (8-x-1));
      
      // draw color
      if ( (this->color & (1 << 2)) > 0)
        matrix[3*y] |= (1 << (8-x-1) );
      if ( (this->color & (1 << 1)) > 0)
        matrix[3*y+1] |= (1 << (8-x-1) );
      if ( (this->color & 1) > 0)
        matrix[3*y+2] |= (1 << (8-x-1) );
    }   
  }

  void drawRectangle(int x, int y, int w, int h, boolean filled) {
    if (filled) {
      for(int i=y; i<y+h; i++)
        for(int j=x; j<x+w; j++)
          this->drawPixel(i,j);
    } else {
      for(int i=y; i<y+h; i++) {
        this->drawPixel(x,i);
        this->drawPixel(x+w-1,i);
      }
      for(int i=x; i<x+w; i++) {
        this->drawPixel(i,y);
        this->drawPixel(i,y+h-1);
      }  
    }
  }
  
  void drawArray(int x, int y, const uchar *array, int rows) {
    for (int i=0; i<rows; i++) {
      if ( (this->color & (1 << 2)) > 0)
        matrix[3*(y+i)] |= (array[i] >> x);
      if ( (this->color & (1 << 1)) > 0)
        matrix[3*(y+i)+1] |= (array[i] >> x);
      if ( (this->color & 1) > 0)
        matrix[3*(y+i)+2] |= (array[i] >> x);
    }
  }
  
  void display() {
    digitalWrite(this->latchPin, LOW);
    for (byte i=0; i<ROWS*3; i++) {
      SPI.transfer(matrix[i]);
      delayMicroseconds(10);
    }
    digitalWrite(this->latchPin, HIGH);
  }

private:

  uchar matrix[ROWS*3];
  int latchPin;
  LedColor color;
  uchar brightness;

};

#endif

