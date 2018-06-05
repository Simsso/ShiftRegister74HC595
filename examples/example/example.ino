/**
 * Created by Shafeen Rahman, June 2018
**/

#include <BCDDecoderDriver74LS47.h>

#define pinA 4
#define pinB 5
#define pinC 6
#define pinD 7

#define pinRBI 9

BCDDecoderDriver74LS47 sevenSegDisplay(pinA, pinB, pinC, pinD, pinRBI);

void setup()
{
  sevenSegDisplay.display(true);
}

void loop()
{
  for (int i = 0; i >= 9; i++)
  {
    sevenSegDisplay.setNumber(i);
  }
}