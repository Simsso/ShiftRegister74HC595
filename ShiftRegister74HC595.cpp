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
    
    setAll(_digitalValues); // reset shift register
}


// Set all pins of the shift registers at once.
// digitalVAlues is a uint8_t array where the length is equal to the number of shift registers.
void ShiftRegister74HC595::setAll(uint8_t * digitalValues)
{
    int byte;
    
    for (byte = _numberOfShiftRegisters - 1; byte >= 0; byte--) {
        shiftOut(_serialDataPin, _clockPin, MSBFIRST, digitalValues[byte]);
    }
    
    _digitalValues = digitalValues; 
    
    digitalWrite(_latchPin, HIGH); 
    digitalWrite(_latchPin, LOW); 
}


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
void ShiftRegister74HC595::updateRegisters()
{
	 setAll(_digitalValues);
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
    int i; 
    for (i = 0; i < _numberOfShiftRegisters; i++) {
        _digitalValues[i] = 255;
    }
    setAll(_digitalValues); 
}


// Sets all pins of all shift registers to LOW (0).
void ShiftRegister74HC595::setAllLow()
{
    int i; 
    for (i = 0; i < _numberOfShiftRegisters; i++) {
        _digitalValues[i] = 0;
    }
    setAll(_digitalValues); 
}
