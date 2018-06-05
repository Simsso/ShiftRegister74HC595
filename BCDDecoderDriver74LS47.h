#ifndef BCDDecoderDriver74LS47
#define BCDDecoderDriver74LS47

#include "Arduino.h"

class BCDDecoderDriver74LS47
{
  public:
    BCDDecoderDriver74LS47(int pinA, int pinB, int pinC, int pinD, int pinRBI);
    void display(boolean state);
    void setNumber(int number);

  private:
    int _pinA;
    int _pinB;
    int _pinC;
    int _pinD;

    int _pinRBI;
};

#endif