#pragma once
#ifndef WAITTIMER_H
#define WAITTIMER_H

#include "Arduino.h"

class WaitTimer
{
private:

    uint64_t start;
    uint64_t now;

public:
    WaitTimer();

    void startTimer();
    void updateNow();

    bool wait_ms(uint64_t time);
    bool wait_sec(uint64_t time);
};

#endif