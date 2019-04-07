#include <msp430.h>
#include <stdint.h>
#include <stdbool.h>

#include "hw.h"
#include "dcf.h"
#include "rtc.h"
/**
 * main.c
 */

void takeBit(void);
void writeByteToSerial(uint8_t byte);




int main ( void )
{
    // initalize clock, pins, timer..
    initHW();
    __delay_cycles(WAIT10US);              // wait to initialize all systems
    //P2OUT |= not_SRCLR;                     // release Shiftregister (low active)
    __delay_cycles(WAIT10US);

    //writeByteToSerial(0x09);                // write one byte to bit register

    //P1OUT &= ~not_OE;

    // start timer
    TACTL |= MC_1 ;                    //start timer in up-mode (count to TACCRx)


    // init DCF state machine
    initDCF();
    initRTC();
    __enable_interrupt();
    while(1)
    {
                dcfStateMachine();
    }
}

/*
 *
 */
void takeBit(void)
{
    __delay_cycles(WAIT10US);
    P1OUT |= SRCLK;
    __delay_cycles(WAIT10US);
    P1OUT &= ~SRCLK;
}

void writeByteToSerial(uint8_t byte)
{
    int8_t i;
    for(i=7; i>=0; i--)
    {
        if (byte & (1u << i))
        {
            P1OUT |= SER;
        } else
        {
            P1OUT &= ~SER;
        }
        takeBit();
    }
    takeBit(); //last bit into storage register
}

