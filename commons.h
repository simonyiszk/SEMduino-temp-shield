#ifndef COMMONS_H_
#define COMMONS_H_

#include <stdint.h>

// Alap típusok definiálása.
typedef uint8_t			byte;
typedef int8_t			sbyte;
typedef uint16_t		word;
typedef int16_t			sword;
typedef uint32_t		dword;
typedef int32_t			sdword;

//#define _BV(BIT) (1 << BIT)
#define BIT_SET(REG, BIT) (REG |= _BV(BIT))
#define BIT_CLR(REG, BIT) (REG &= ~_BV(BIT))
#define BIT_TGL(REG, BIT) (REG ^= _BV(BIT))
#define BIT_GET(REG, BIT) (REG & _BV(BIT))
#define BIT_WRT(REG, BIT, VAL) (VAL? BIT_SET(REG, BIT) : BIT_CLR(REG_CLR))
#define _NOP() (asm volatile ("nop"))

#endif /* COMMONS_H_ */