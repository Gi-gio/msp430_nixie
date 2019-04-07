/*
 * timer.c
 *
 *  Created on: 24.08.2018
 *      Author: Giordano Altomare
 */

#include "hw.h"
#include "rtc.h"
#include "dcf.h"

// 1 sec Timer
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer0A0_ISR(void)
{
    if(++(timePtr->second) > 59) timePtr->second = 0;
    P1OUT ^= BIT0;
    //checkDCFSignal();
}

#pragma vector=TIMER0_A1_VECTOR
__interrupt void Timer0A1_ISR(void)
{
    switch(_even_in_range(TAIV,0x0A))
    {
        case 0x00:  break;
        case 0x02:  dcfSignalKind(DCF_IN);
                    if(DCF_IN)
                    {
                        P1OUT |= LED2;
                    } else
                    {
                        P1OUT &= ~LED2;

                    }
                    //__bic_SR_register_on_exit(GIE);

                    break;
        case 0x04:  break;
        case 0x06:  break;
        case 0x08:  break;
        case 0x0A:  break;
        case 0x0C:  break;
        case 0x0E:  break;
        default: _never_executed();
    }
}

