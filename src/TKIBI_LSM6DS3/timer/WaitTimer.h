#pragma once
#ifndef WAITTIMER_H
#define WAITTIMER_H

#include "Arduino.h"

class WaitTimer
{
private:

    uint32_t start;
    uint32_t now;

public:
    WaitTimer();

    void startTimer();
    void updateNow();

    bool wait_ms(uint32_t time);
    bool wait_sec(uint32_t time);
};

#endif