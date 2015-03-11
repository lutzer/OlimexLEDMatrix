# OlimexLEDMatrix
Arduino Library for interfacing a single Olimex (RGB and non-RGB) 8x8 Matrix

## Instructions
Check matrixExample for information on how to use the library

Since the Single Color Matrix does not support multiplexing, it has to be done by the arduino, so matrix.display() function has to be called in every loop.

The RGB Matrix does support multiplexing, so it just has to be called on update.

1. Initialize the matrix in your setup() method
2. in loop(): call matrix.clear(), then draw something (i.e matrix.drawRectangle(0,0,2,2) and then display it through matrix.display();

