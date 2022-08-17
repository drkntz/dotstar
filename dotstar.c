/* ========================================
 * project: Driver for sending data to DotStar (APA102 LED) via SPI.
 * File:    dotstar.c
 *
 * Drive dotstar. Tested on pic16f18325
 *
 * Zach Martin
 * Initial version: 7/14/22, Zach Martin
 *
 *
 * ========================================
*/

#include "dotstar.h"
#include "mcc_generated_files/mcc.h"
typedef struct _BRGB{
    uint8_t brightness;
    uint8_t blue;
    uint8_t green;
    uint8_t red;    
}_BRGB;

struct _BRGB _led_data[NUM_LEDS];

void dotstar_setup(void)
{
    // Nothing for now
}

void dotstar_close(void)
{
    // Nothing for now
}

void dotstar_set_all(uint8_t red, uint8_t green, uint8_t blue)
{
    uint8_t i = 0;
    
    for(; i < NUM_LEDS; i++)
    {
        dotstar_set_pixel(i, red, green, blue);
    }
}

void dotstar_set_pixel(uint8_t pixel, uint8_t red, uint8_t green, uint8_t blue)
{
    _led_data[pixel].red = red;
    _led_data[pixel].green = green;
    _led_data[pixel].blue = blue;
}

void dotstar_set_brightness(uint8_t brightness)
{
    uint8_t i = 0;
    
    for(; i < NUM_LEDS; i++)
    {
        dotstar_set_pixel_brightness(i, brightness);
    }
}

void dotstar_set_pixel_brightness(uint8_t pixel, uint8_t brightness)
{
    _led_data[pixel].brightness = brightness | 0xE0;
    // brightness has to start with 111. 32 steps of brightness from 0-31
}

void dotstar_show(void)
{
    uint8_t i;
    uint8_t start_packet[4] = {0x00};
    uint8_t end_packet[4] = {
      0xFF,
      0xFF,
      0xFF,
      0xFF 
    };
    SPI1_WriteBlock(start_packet, 4);
    
    for(i = 0; i < NUM_LEDS; i++)
    {
        SPI1_WriteBlock(&_led_data[i].brightness, 1);
        SPI1_WriteBlock(&_led_data[i].blue, 1);
        SPI1_WriteBlock(&_led_data[i].green, 1);
        SPI1_WriteBlock(&_led_data[i].red, 1);        
    }
    SPI1_WriteBlock(end_packet, 4);
}

// Clear LEDs in ram
void dotstar_clear(void)
{
    dotstar_set_all( 0x00, 0x00, 0x00);
}

////////////////////////////////////////////////////////////////////////////////
//                       Cool animation stuff                                 //
////////////////////////////////////////////////////////////////////////////////

// Rainbow fade following ROYGBIV color
// This is only the updater, you have to run it in a loop
void dotstar_colorfade(void)
{
    static uint8_t green = 0;
    static uint8_t red = 20;
    static uint8_t blue = 0;
    static uint8_t state = 1;
    
    switch(state)
    {
        case 1:
            red ++;
            if(red > 250) state = 2;
        break;
        case 2:
            if(red > 0) red --;
            green++;
            if(green == 250) state = 3;
        break;

        case 3:
            if(green > 0) green --;
            blue ++;
            if(blue == 250) state = 4;
        break;

        case 4:
            if(blue > 0) blue --;
            red ++;
            if(red == 250) state = 2;
        break;
    }
        
    dotstar_set_all(red, green, blue);
    dotstar_show();                
}

const uint8_t _chase_pattern[21] = {
    
};
// Chase animation
// This is only the updater, you have to run it in a loop
void dotstar_chase(void)
{
    static int8_t head;
    static uint8_t red, green, blue;
    uint8_t i;
    
    blue = 150;
    red = 75;
    dotstar_set_all(0x00, 0x00, 0x01);
    
    dotstar_set_pixel(head, red, green, blue);
    
    for(i = 1; i < 6; i++)
    {
        red = red - 15;
        blue = blue - 20;
        if((head - i ) < 0)
        {
            dotstar_set_pixel(NUM_LEDS + (head - i),  red, green, blue);
        }
        else
        {
            dotstar_set_pixel(head - i, red, green, blue);
        }
    }
    
    if(head + 1 == NUM_LEDS) head = 0;
    else head++;
    
    dotstar_show();
}

// spiral animation. 4x regions chasing clockwise
void spiral_clockwise(void)
{
    static int8_t head;
    static uint8_t red, green, blue;
    uint8_t i, j;
    int8_t nexthead;
    
    nexthead = head;
    dotstar_set_all(0x00, 0x01, 0x01);
    blue = 189;
    red = 13;
    green = 40;
    
    for(j = 0; j < 4; j++)
    {
        dotstar_set_pixel(nexthead, red, green, blue);

        if(nexthead+4 >= NUM_LEDS) nexthead = 4 - (NUM_LEDS - nexthead);
        else nexthead += 4;
    }
    
    if(head + 1 == NUM_LEDS) head = 0;
    else head++;
    dotstar_show();
}


// spiral animation. 4x regions chasing clockwise
void spiral_counterclockwise(void)
{
    static int8_t head;
    static uint8_t red, green, blue;
    uint8_t i, j;
    int8_t nexthead;
    
    nexthead = head;
    dotstar_set_all(0x00, 0x01, 0x01);
    blue = 189;
    red = 13;
    green = 40;
    
    for(j = 0; j < 4; j++)
    {

        dotstar_set_pixel(nexthead, red, green, blue);

        if(nexthead-4 < 0) nexthead = (NUM_LEDS - 4) + nexthead;
        else nexthead -= 4;
    }
    
    if(head - 1 <= 0) head = NUM_LEDS;
    else head--;
    dotstar_show();
}