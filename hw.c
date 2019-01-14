/*
 * hw.c
 *
 *  Created on: 14.01.2019
 *      Author: Giordano
 */

#include "hw.h"



/*
 *
 */
void initHW (void)
{
    WDTCTL = WDTPW + WDTHOLD;                   // Stop WDT

    // config internal clock
    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL = CALDCO_1MHZ;

    // config external clock
    BCSCTL1 &= (~XTS);                          // ACLK = LFXT1CLK
    BCSCTL3 &= ~(BIT4|BIT5);                    // 32'768Hz crystal on LFXT1
    BCSCTL3 |= XCAP_3 ;                         // Capacitance seen by LFXT1 crystal

    //set up Timer
    TACTL |= TASSEL_1;                          // select ACLK for timebase
    TACCR0 |= TIMERPERIOD;                      // timer0 count to 32768 = 1sec
    TACCTL0 |= CCIE;                            // timer0 compare mode + Interrupt enable

    TACCTL1 |= CAP|CM_3|CCIE|SCS;               // timer0 ccr1 capture mode + on rising edge + interrupt enable + capture synchronize



    // init in-& output Port & Pin
    P1DIR = 0X00 | (SER|not_OE|SRCLK|~DCF|LED2);  //
    P2DIR = 0x00 | not_SRCLR;
    P1OUT = 0x00 | not_OE;                   // set Data and clock to 0,  and disable output (low_active)
    P2OUT = 0x00;                             // clear Shiftregister (low active)
    P1SEL |= DCF;                           // Set DCF Pin for input compare
    P1SEL2 &= ~DCF;
   // P2SEL |= (BIT6 | BIT7);                 // Set P2.6 and P2.6 SEL for XIN, XOUT
   // P2SEL2 &= ~(BIT6|BIT7);
    P1REN |= DCF;
    P1OUT |= DCF;                           //activate internal pullup resistor



}

