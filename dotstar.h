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

#include "mcc_generated_files/spi1.h" // SPI driver
#define NUM_LEDS 16

#ifdef	__cplusplus
extern "C" {
#endif
    
extern void dotstar_setup();      // Setup dotstar
extern void dotstar_close();      // Close dotstar driver
extern void dotstar_set_all(uint8_t red, uint8_t green, uint8_t blue);    // Set all LEDs in memory (rgb)
extern void dotstar_set_pixel(uint8_t num, uint8_t red, uint8_t green, uint8_t blue);  // Set one LED in memory (rgb)
extern void dotstar_show();       // Drive memory to output LED string
extern void dotstar_clear();      // Set all LEDs in memory to off
extern void dotstar_colorfade();
extern void dotstar_chase();
extern void dotstar_set_brightness(uint8_t brightness);
extern void dotstar_set_pixel_brightness(uint8_t pixel, uint8_t brightness);
void spiral_clockwise(void);
void spiral_counterclockwise(void);


#ifdef	__cplusplus
}
#endif

#endif	/* DOTSTAR_H */

