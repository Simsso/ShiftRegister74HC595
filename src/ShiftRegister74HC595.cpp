/*
  ShiftRegister74HC595.cpp - Library for simplified control of 74HC595 shift registers.
  Created by Timo Denk (www.timodenk.com), Nov 2014.
  Additional information is available at http://shiftregister.simsso.de/
  Released into the public domain.
*/

#include "Arduino.h"
#include "ShiftRegister74HC595.h"


// ShiftRegister74HC595 constructor
ShiftRegister74HC595::ShiftRegister74HC595(int numberOfShiftRegisters, int serialDataPin, int clockPin, int latchPin)
{
    // set attributes
    _numberOfShiftRegisters = numberOfShiftRegisters;

    _clockPin = clockPin;
    _serialDataPin = serialDataPin;
    _latchPin = latchPin;

    // define pins as outputs
    pinMode(clockPin, OUTPUT);
    pinMode(serialDataPin, OUTPUT);
    pinMode(latchPin, OUTPUT);

    // set pins low
    digitalWrite(clockPin, LOW);
    digitalWrite(serialDataPin, LOW);
    digitalWrite(latchPin, LOW);

    // allocates the specified number of bytes and initializes them to zero
    _digitalValues = (uint8_t *)malloc(numberOfShiftRegisters * sizeof(uint8_t));
    memset(_digitalValues, 0, numberOfShiftRegisters * sizeof(uint8_t));

    updateRegisters();       // reset shift register
}


// ShiftRegister74HC595 destructor
// The memory allocated in the constructor is also released.
ShiftRegister74HC595::~ShiftRegister74HC595()
{
    free(_digitalValues);
}


// Set all pins of the shift registers at once.
// digitalVAlues is a uint8_t array where the length is equal to the number of shift registers.
void ShiftRegister74HC595::setAll(const uint8_t * digitalValues)
{
    memcpy( _digitalValues, digitalValues, _numberOfShiftRegisters);   // dest, src, size
    updateRegisters();
}


// Experimental
// The same as setAll, but the data is located in PROGMEM
// For example with:
//     const uint8_t myFlashData[] PROGMEM = { 0x0F, 0x81 };
#ifdef __AVR__
void ShiftRegister74HC595::setAll_P(const uint8_t * digitalValuesProgmem)
{
    PGM_VOID_P p = reinterpret_cast<PGM_VOID_P>(digitalValuesProgmem);
    memcpy_P( _digitalValues, p, _numberOfShiftRegisters);
    updateRegisters();
}
#endif


// Retrieve all states of the shift registers' output pins.
// The returned array's length is equal to the numbe of shift registers.
uint8_t * ShiftRegister74HC595::getAll()
{
    return _digitalValues; 
}


// Set a specific pin to either HIGH (1) or LOW (0).
// The pin parameter is a positive, zero-based integer, indicating which pin to set.
void ShiftRegister74HC595::set(int pin, uint8_t value)
{
    setNoUpdate(pin, value);
    updateRegisters();
}


// Updates the shift register pins to the stored output values.
// This is the function that actually writes data into the shift registers of the 74HC595
void ShiftRegister74HC595::updateRegisters()
{
    for (int i = _numberOfShiftRegisters - 1; i >= 0; i--) {
        shiftOut(_serialDataPin, _clockPin, MSBFIRST, _digitalValues[i]);
    }
    
    digitalWrite(_latchPin, HIGH); 
    digitalWrite(_latchPin, LOW); 
}


// Equivalent to set(int pin, uint8_t value), except the physical shift register is not updated.
// Should be used in combination with updateRegisters().
void ShiftRegister74HC595::setNoUpdate(int pin, uint8_t value)
{
    if (value == 1) {
        _digitalValues[pin / 8] |= 1 << (pin % 8);
    }
    else {
        _digitalValues[pin / 8] &= ~(1 << (pin % 8));
    }
}


// Returns the state of the given pin.
// Either HIGH (1) or LOW (0)
uint8_t ShiftRegister74HC595::get(int pin)
{
    return (_digitalValues[pin / 8] >> (pin % 8)) & 1;
}


// Sets all pins of all shift registers to HIGH (1).
void ShiftRegister74HC595::setAllHigh()
{
    for (int i = 0; i < _numberOfShiftRegisters; i++) {
        _digitalValues[i] = 255;
    }
    updateRegisters();
}


// Sets all pins of all shift registers to LOW (0).
void ShiftRegister74HC595::setAllLow()
{
    for (int i = 0; i < _numberOfShiftRegisters; i++) {
        _digitalValues[i] = 0;
    }
    updateRegisters();
}
