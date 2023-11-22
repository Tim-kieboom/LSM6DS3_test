#pragma once
#ifndef WAITTIMER_H
#define WAITTIMER_H

#include "Arduino.h"

class WaitTimer
{
private:

    uint16_t start = 1;
    uint16_t now = 0;

public:
    WaitTimer();

    //set start at currentTime
    void startTimer();
    //set now at currentTime
    void updateNow();

    //returns true if time has elapsed (time in milliseconds)
    bool wait_ms(uint16_t time); 
    //returns true if time has elapsed (time in seconds)
    bool wait_sec(uint16_t time); 
};

#endif