/*
  ShiftRegister74HC595.h - Library for easy control of the 74HC595 shift register.
  Created by Timo Denk (www.simsso.de), Nov 2014.
  Additional information are available on http://shiftregister.simsso.de/
  Released into the public domain.
*/

#ifndef ShiftRegister74HC595_h
#define ShiftRegister74HC595_h

#include "Arduino.h"

class ShiftRegister74HC595 
{
    public:
        ShiftRegister74HC595(int numberOfShiftRegisters, int serialDataPin, int clockPin, int latchPin);
        void setAll(uint8_t * digitalValues);
        uint8_t * getAll(); 
        void set(int pin, uint8_t value);
        void setAllLow();
        void setAllHigh(); 
        uint8_t get(int pin);

    private:
        int _numberOfShiftRegisters;
        int _clockPin;
        int _serialDataPin;
        int _latchPin;
        uint8_t * _digitalValues;
};

#endif