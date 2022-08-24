# dotstar
Driver for apa102-2020 and similar two-wire serial LEDs

This has been tested on pic16f1832X processors.

# Using dotstar:
To use this driver, simply #include "dotstar.h" and provide the driver with an appropriate SPI (or another interface) driver running at 1MHz. 

Example using MCC-generated SPI driver:

`#include "dotstar/dotstar.h"
`
`void main(void)
`{
`   SPI1_Open(0);
`   dotstar_setup(SPI1_WriteBlock); // Tell dotstar which interface to use. In this case, SPI1 driver from MCC
`   dotstar_set_brightness(15);
`   
`   while(1) // Blink red
`   {
`     dotstar_set_all(0xFF, 0x00, 0x00);
`     dotstar_show();
`     __delay_ms(500);
`     dotstar_clear();
`     dotstar_show();
`     __delay_ms(500);
`   }
`}

