/* ========================================
 * project: Driver for sending data to DotStar (APA102 LED) via SPI.
 * File:    dotstar.h
 *
 * Drive dotstar. Tested on pic16f18325
 *
 * Zach Martin
 * Initial version: 7/14/22, Zach Martin
 *
 * ========================================
*/

/* Note! This driver requires a functioning SPI driver running at 800 - 1200 kHz
 * For this test, I ran it at 1MHz
 */
#ifndef DOTSTAR_H
#define	DOTSTAR_H


#define NUM_LEDS 16

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
    
void dotstar_setup(void(*block_write_func)(void*, size_t)); // tell us which spi driver to use
void dotstar_close(void);      // Close dotstar driver
void dotstar_set_all(uint8_t red, uint8_t green, uint8_t blue);    // Set all LEDs in memory (rgb)
void dotstar_set_pixel(uint8_t num, uint8_t red, uint8_t green, uint8_t blue);  // Set one LED in memory (rgb)
void dotstar_show(void);       // Drive memory to output LED string
void dotstar_clear(void);      // Set all LEDs in memory to off
void dotstar_colorfade(void);
void dotstar_chase(void);
void dotstar_set_brightness(uint8_t brightness);
void dotstar_set_pixel_brightness(uint8_t pixel, uint8_t brightness);
void spiral_clockwise(void);
void spiral_counterclockwise(void);


#ifdef	__cplusplus
}
#endif

#endif	/* DOTSTAR_H */

