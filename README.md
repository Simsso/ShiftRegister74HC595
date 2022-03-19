# ShiftRegister 74HC595 Arduino Library

This library simplifies the usage of shift registers. For instance, it allows to set pins of the shift register just like normal Arduino pins: 
```
sr.set(1, HIGH)
```

Please find the detailed **documentation** at https://timodenk.com/blog/shift-register-arduino-library/.

An **example** sketch can be found in this repository at [/examples/example/example.ino](https://github.com/Simsso/ShiftRegister74HC595/blob/master/examples/example/example.ino).



New:

to shift data via SPI define `SHIFT_REGISTER_USES_SPI_WITH_FREQUENCY 20000000UL` before you include ShiftRegister74HC595.h 

Arduino UNO uses pin 13 for CLOCK and pin 11 for MOSI (data) - latch pin - configurable.