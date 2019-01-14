/*
 * rtc.h
 *
 *  Created on: 22.08.2018
 *      Author: Giordano
 */

#include <stdint.h>

#ifndef RTC_H_
#define RTC_H_

typedef struct {
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
} time_t;

typedef struct {
    uint8_t year;
    uint8_t month;
    uint8_t day;
} date_t;

extern time_t* timePtr;
extern date_t* datePtr;


void initRTC(void);
time_t* getTime(void);
void setTime(void);

#endif /* RTC_H_ */
