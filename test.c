#ifndef F_CPU
#define F_CPU 16000000UL // or whatever may be your frequency
#endif

#include <avr/io.h>
#include <util/delay.h>                // for _delay_ms()
#include <math.h>
#include "commons.h"
#include "shield.h"

void send_bit(uint8_t bit)
{
    BIT_CLR(CLK_PORT, CLK_BIT);
    if (bit)
        BIT_SET(DATA_PORT, DATA_BIT);
    else
        BIT_CLR(DATA_PORT, DATA_BIT);
    
    _delay_ms(1);
    BIT_SET(CLK_PORT, CLK_BIT);
    _delay_ms(1);
}

void send_word(word data)
{
    BIT_CLR(OUTCLK_PORT, OUTCLK_BIT);
    for (byte i = 0; i < 16; i++)
    {
        send_bit(~data & 1);
        data = data >> 1;
    }
    BIT_SET(OUTCLK_PORT, OUTCLK_BIT);
}

double getR(word adc)
{
    return (1023.0 - (double)adc) / (double)adc * 10.0;
}

double calcT(double R)
{
    double A1 = 3.354016/1000.0;
    double B1 = 2.744032/10000.0;
    double C1 = 3.666944/1000000.0;
    double D1 = 1.375492/10000000.0;
    return 1.0/(A1+B1*log(R/22.0)+C1*pow(log(R/22.0), 2.0)+D1*pow(log(R/22.0), 3.0));
}


word dig2seg(byte val, byte tens)
{
    val %= 10;
    if (tens)
    {
        switch (val)
        {
        case 0: return SEG1A | SEG1B | SEG1C | SEG1D | SEG1E | SEG1F;
        case 1: return SEG1B | SEG1C;
        case 2: return SEG1A | SEG1B | SEG1D | SEG1E | SEG1G;
        case 3: return SEG1A | SEG1B | SEG1C | SEG1D | SEG1G;
        case 4: return SEG1B | SEG1C | SEG1F | SEG1G;
        case 5: return SEG1A | SEG1C | SEG1D | SEG1F | SEG1G;
        case 6: return SEG1A | SEG1C | SEG1D | SEG1E | SEG1F | SEG1G;
        case 7: return SEG1A | SEG1B | SEG1C;
        case 8: return SEG1A | SEG1B | SEG1C | SEG1D | SEG1E | SEG1F | SEG1G;
        case 9: return SEG1A | SEG1B | SEG1C | SEG1D | SEG1F | SEG1G;
        
        default: return 0;
        }
    }
    else
    {
        switch (val)
        {
        case 0: return SEG2A | SEG2B | SEG2C | SEG2D | SEG2E | SEG2F;
        case 1: return SEG2B | SEG2C;
        case 2: return SEG2A | SEG2B | SEG2D | SEG2E | SEG2G;
        case 3: return SEG2A | SEG2B | SEG2C | SEG2D | SEG2G;
        case 4: return SEG2B | SEG2C | SEG2F | SEG2G;
        case 5: return SEG2A | SEG2C | SEG2D | SEG2F | SEG2G;
        case 6: return SEG2A | SEG2C | SEG2D | SEG2E | SEG2F | SEG2G;
        case 7: return SEG2A | SEG2B | SEG2C;
        case 8: return SEG2A | SEG2B | SEG2C | SEG2D | SEG2E | SEG2F | SEG2G;
        case 9: return SEG2A | SEG2B | SEG2C | SEG2D | SEG2F | SEG2G;
        
        default: return 0;
        }
    }
}

void dispnum(byte value)
{

}

word readADC()
{
    BIT_SET(ADCSRA, 6);
    while(!BIT_GET(ADCSRA, 4));
    word adcread = ADCL;
    adcread |= ADCH << 8;
    adcread &= 0x3FF;
    return adcread;
}

void printNum(word num)
{
    if (num > 99) num = 99;
    if (num < 0) num = 0;
    word tens = dig2seg(num / 10, 1);
    word ones = dig2seg(num % 10, 0);
    send_word(tens | ones);
}

int main(void)
{
    PORTD = 0;
    ADMUX = 0b01000000;
    ADCSRA = (1 << 7) | 7;

    BIT_SET(DATA_DDR, DATA_BIT);
    BIT_SET(CLK_DDR, CLK_BIT);
    BIT_SET(OUTCLK_DDR, OUTCLK_BIT);

    byte k = 0;
    while(1)
    {
        word adc = readADC();
        double R = getR(adc);
        double T = calcT(R)-273.0;
        printNum(((word)T));
        //if (adc > 99) adc = 99;

        k++;
        if (k > 99) k = 0;
    }
}

