/*
 * rtc.c
 *
 *  Created on: 22.08.2018
 *      Author: Giordano Altomare
 */

#include "rtc.h"

static time_t time;
static date_t date;
time_t* timePtr = &time;
date_t* datePtr = &date;

void initRTC(void)
{
    timePtr->hour   = 88;
    timePtr->minute = 88;
    timePtr->second = 00;
}

time_t* getTime(void)
{
    return timePtr;
}

void setTime(void)
{

}


