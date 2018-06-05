#include "Arduino.h"
#include "BCDDecoderDriver74LS47.h"

// BCDDecoderDriver74LS47 constructor
BCDDecoderDriver74LS47::BCDDecoderDriver74LS47(int pinA, int pinB, int pinC, int pinD, int pinRBI)
{
    _pinA = pinA;
    _pinB = pinB;
    _pinC = pinC;
    _pinD = pinD;

    _pinRBI = pinRBI;

    pinMode(pinA, OUTPUT);
    pinMode(pinB, OUTPUT);
    pinMode(pinC, OUTPUT);
    pinMode(pinD, OUTPUT);

    pinMode(pinRBI, OUTPUT);
}

void BCDDecoderDriver74LS47::display(boolean state)
{
    digitalWrite(_pinRBI, state);
}

void BCDDecoderDriver74LS47::setNumber(int number)
{
    digitalWrite(_pinA, bitRead(number, 0));
    digitalWrite(_pinB, bitRead(number, 1));
    digitalWrite(_pinC, bitRead(number, 2));
    digitalWrite(_pinD, bitRead(number, 3));
}