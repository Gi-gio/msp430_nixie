/*
 * hw.h
 *
 *  Created on: 24.08.2018
 *      Author: Giordano
 */

#ifndef HW_H_
#define HW_H_

#include <msp430.h>

#define CLK 1000000
#define TIMERPERIOD 0x7FFF
#define WAIT10US 10

#define SHIFTLENGTH 8

// Port 1
#define DCF         BIT2          // DCF out
#define SER         BIT3          // Serial out for Bit-shifter
#define not_OE      BIT4          // Output not enalbe for Bit-Shifter
#define SRCLK       BIT5          // Clock for Bit-shifter

// Port 2
#define not_SRCLR   BIT0          // Serial clear for Bit-Shifter
#define LED2        BIT6          //


void initHW(void);

#endif /* HW_H_ */
