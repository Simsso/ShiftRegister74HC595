/*
  ShiftRegister74HC595 - Library for simplified control of 74HC595 shift registers.
  Developed and maintained by Timo Denk and contributers, since Nov 2014.
  Additional information is available at https://timodenk.com/blog/shift-register-arduino-library/
  Released into the public domain.
*/

// 20000000UL <- your chip speed. if arduino cant handle that, it will work at max it can. On uno up to 8mhz. 20000000UL means 20Mhz
// MOSI to shift register DATA pin, SCLK to CLock pin, Latch pin configurable
#define SHIFT_REGISTER_USES_SPI_WITH_FREQUENCY 20000000UL
#include <ShiftRegister74HC595.h>

// create a global shift register object
// parameters: <number of shift registers> (latch pin)
ShiftRegister74HC595<1> sr(7);
 
void setup() { 
}

void loop() {

  // setting all pins at the same time to either HIGH or LOW
  sr.setAllHigh(); // set all pins HIGH
  delay(500);
  
  sr.setAllLow(); // set all pins LOW
  delay(500); 
  

  // setting single pins
  for (int i = 0; i < 8; i++) {
    
    sr.set(i, HIGH); // set single pin HIGH
    delay(250); 
  }
  
  
  // set all pins at once
  uint8_t pinValues[] = { B10101010 }; 
  sr.setAll(pinValues); 
  delay(1000);

  
  // read pin (zero based, i.e. 6th pin)
  uint8_t stateOfPin5 = sr.get(5);
  sr.set(6, stateOfPin5);


  // set pins without immediate update
  sr.setNoUpdate(0, HIGH);
  sr.setNoUpdate(1, LOW);
  // at this point of time, pin 0 and 1 did not change yet
  sr.updateRegisters(); // update the pins to the set values
}
