/*
  ShiftRegister74HC595.h - Library for simplified control of 74HC595 shift registers.
  Developed and maintained by Timo Denk and contributers, since Nov 2014.
  Additional information is available at https://timodenk.com/blog/shift-register-arduino-library/
  Released into the public domain.
*/

#pragma once

#include <Arduino.h>

#if defined(SHIFT_REGISTER_USES_SPI_WITH_FREQUENCY)
#include <SPI.h>
#endif

template<uint8_t Size>
class ShiftRegister74HC595 
{
public:
#if !defined(SHIFT_REGISTER_USES_SPI_WITH_FREQUENCY)
    ShiftRegister74HC595(const uint8_t serialDataPin, const uint8_t clockPin, const uint8_t latchPin);
#else
    ShiftRegister74HC595(const uint8_t latchPin);
#endif
    
    void setAll(const uint8_t * digitalValues);
#ifdef __AVR__
    void setAll_P(const uint8_t * digitalValuesProgmem); // Experimental, PROGMEM data
#endif
    uint8_t * getAll(); 
    void set(const uint8_t pin, const uint8_t value);
    void setNoUpdate(const uint8_t pin, uint8_t value);
    void updateRegisters();
    void setAllLow();
    void setAllHigh(); 
    uint8_t get(const uint8_t pin);
    void order(uint8_t o);

private:
    uint8_t bo = MSBFIRST;
    uint8_t _clockPin;
    uint8_t _serialDataPin;
    uint8_t _latchPin;

    uint8_t  _digitalValues[Size];
};

#include "ShiftRegister74HC595.hpp"
