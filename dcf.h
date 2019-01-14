/*
 * dcf.h
 *
 *  Created on: 22.08.2018
 *      Author: Giordano Altomare
 */

#ifndef DCF_H_
#define DCF_H_

#include <stdbool.h>
#include <stdint.h>
#include <msp430.h>

#include "rtc.h"

#define DCF_IN      TA0CCTL1 & (1u << 3)  //check if dcf-in is high


typedef enum dcfSignalType_ {
    low=1,
    high,
    invalid,
    none
} dcfSignalType_t;

typedef enum dcfState {
    dcfStart,
    dcfFirstLow,
    dcfLow,
    dcfHigh,
    dcfCalc,
    dcfInvalid
} dcfState_t;

typedef struct {
    dcfSignalType_t type;
    uint16_t captureNew;
    uint16_t captureOld;
    uint16_t captureDiff;
} logicDetect_t;


void initDCF(void);
void restartDCF(void);
struct dcfData_ collectData(void);
void dcfStateMachine(void);
void dcfSignalKind(uint16_t);

extern dcfState_t state;
extern bool dcfFlag;
extern logicDetect_t logicDetect;


#endif /* DCF_H_ */
