#include "WaitTimer.h" 

WaitTimer::WaitTimer() 
{

}

void WaitTimer::startTimer() 
{
    start = millis();
}

void WaitTimer::updateNow()
{
    now = millis();
}


bool WaitTimer::wait_ms(uint16_t timeInMilieSecond)
{
    if(now - start >= timeInMilieSecond)
    {
        start = millis();
        return true;
    }
    return false;
}

bool WaitTimer::wait_sec(uint16_t timeInSeconds)
{
    uint32_t timeInMilieSecond = timeInSeconds * 1000;

    if(now - start >= timeInMilieSecond)
    {
        start = millis();
        return true;
    }
    return false;
}

