/*
 * dcf.c
 *
 *  Created on: 22.08.2018
 *      Author: Giordano Altomare
 */

#include <string.h>


#include "hw.h"
#include "dcf.h"
#include "rtc.h"



//uint8_t dcfSignalRaw[60];
dcfState_t state;
bool dcfFlag;
logicDetect_t logicDetect;

static struct dcfData_{
    bool start;
    bool invalid;
    bool end;
    dcfSignalType_t dcfSignalRaw[60];
    uint8_t countSignal;
} dcfData;

void initDCF(void)
{
    // set state-machine to start
    state = dcfInit;

    // 'reset' dcfData
    dcfData.start = true;
    dcfData.invalid &= false;;
    dcfData.end   &= false;
    memset(dcfData.dcfSignalRaw,none,60);           //set all signal values to 'none'
    dcfData.countSignal &= 0;
}

void restartDCF(void)
{
    initDCF();
}

struct dcfData_ collectData(void)
{
    static int8_t secondInit;
    logicDetect.captureDiff = (logicDetect.captureNew > logicDetect.captureOld) ? logicDetect.captureNew - logicDetect.captureOld : logicDetect.captureNew + 0x7FFF - logicDetect.captureOld;
    if(!(logicDetect.captureDiff<3200 || logicDetect.captureDiff>7300) && !dcfData.end)
    {
        if (dcfData.start)
        {
            secondInit = dcfData.countSignal - timePtr->second;
            dcfData.start = false;
        }
        if (dcfData.countSignal != secondInit + timePtr->second)        /*correction if pause was missed*/
        {
            dcfData.dcfSignalRaw[dcfData.countSignal++] = none;
        }
        dcfData.dcfSignalRaw[dcfData.countSignal++] = (logicDetect.captureDiff < 4000) ? low : high;
        if (dcfData.countSignal == 59) dcfData.end = true;
        if (dcfData.countSignal == 1)
        {
            dcfData.countSignal = dcfData.countSignal;
        }
    } else if (logicDetect.captureDiff>=7500 && !dcfData.end)
    {
        dcfData.invalid = true;
    }
    return dcfData;
}

void dcfStateMachine(void)
{
    switch(state)
    {
        case dcfInit:       state = dcfStart;


            break;
        case dcfStart:      if (logicDetect.type == low)
                            {
                                state = dcfFirstLow;
                            }
            break;
        case dcfFirstLow  : if (logicDetect.type == low)
                            {
                                state = dcfLow;
                                dcfFlag = false;
                            }
            break;
        case dcfLow  :      if (dcfFlag && logicDetect.type == low)
                            {
                                dcfFlag = false;
                                if(collectData().invalid)
                                {
                                    state = dcfInvalid;
                                } else if (collectData().end)
                                {
                                    state = dcfCalc;
                                }
                                else if (!(logicDetect.type == low))
                                {
                                    state = dcfHigh;
                                }
                            }
                            __enable_interrupt();
            break;
        case dcfHigh :      if(logicDetect.type == low)
                            state = dcfLow;
                            dcfFlag = false;
            break;
        case dcfInvalid:    restartDCF();
            break;
        case dcfCalc:      ;
            break;
    }
}

void dcfSignalKind(uint16_t rising_edge)
{
    logicDetect.captureOld = logicDetect.captureNew;

    logicDetect.captureDiff = (TACCR1 > logicDetect.captureOld) ? TACCR1 - logicDetect.captureOld : TACCR1 + 0x7FFF - logicDetect.captureOld;
    if (logicDetect.captureDiff>7500 || logicDetect.captureDiff<3200)
    {
        logicDetect.type = invalid;
    } else if (logicDetect.captureDiff < 4000)
    {
        logicDetect.type = low;
    } else
    {
        logicDetect.type = high;
    }
    logicDetect.captureNew = TACCR1;
}
