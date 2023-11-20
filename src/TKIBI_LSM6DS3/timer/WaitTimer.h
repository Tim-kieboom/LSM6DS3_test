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

    void startTimer();
    void updateNow();

    bool wait_ms(uint16_t time);
    bool wait_sec(uint16_t time);
};

#endif