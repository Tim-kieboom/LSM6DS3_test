#pragma once
#ifndef WAITTIMER_H
#define WAITTIMER_H

#include "Arduino.h"

class WaitTimer
{
private:

    uint64_t start = 1;
    uint64_t now = 0;

public:
    WaitTimer();

    //set start at currentTime (also can be called as a reset of the timer)
    void startTimer();
    //set now at currentTime
    void updateNow();


    //returns true if time has elapsed (time in milliseconds)
    bool wait_ms(uint64_t time); 
    //returns true if time has elapsed (time in seconds)
    bool wait_sec(uint32_t time); 
};

#endif