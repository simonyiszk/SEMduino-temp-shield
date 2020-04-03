#ifndef SHIELD_H_
#define SHIELD_H_

#include "commons.h"
#include <avr/io.h>

#define DATA_DDR    DDRD
#define DATA_PORT   PORTD
#define DATA_PIN    PIND
#define DATA_BIT    4

#define CLK_DDR     DDRD
#define CLK_PORT    PORTD
#define CLK_PIN     PIND
#define CLK_BIT     2

#define OUTCLK_DDR  DDRD
#define OUTCLK_PORT PORTD
#define OUTCLK_PIN  PIND
#define OUTCLK_BIT  3

#define SEG1A _BV(0)
#define SEG1B _BV(1)
#define SEG1C _BV(2)
#define SEG1D _BV(7)
#define SEG1E _BV(6)
#define SEG1F _BV(5)
#define SEG1G _BV(4)
#define SEG1P _BV(3)

#define SEG2A _BV(11)
#define SEG2B _BV(10)
#define SEG2C _BV(9)
#define SEG2D _BV(12)
#define SEG2E _BV(13)
#define SEG2F _BV(14)
#define SEG2G _BV(15)
#define SEG2P _BV(8)

#endif /* COMMONS_H_ */
