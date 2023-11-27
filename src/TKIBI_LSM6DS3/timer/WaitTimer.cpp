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

bool WaitTimer::wait_ms(uint64_t timeInMilieSecond)
{
    if(now - start >= timeInMilieSecond)
    {
        start = millis();
        return true;
    }
    return false;
}

bool WaitTimer::wait_sec(uint32_t timeInSeconds)
{
    uint64_t timeInMilieSecond = timeInSeconds * 1000;

    if(now - start >= timeInMilieSecond)
    {
        start = millis();
        return true;
    }
    return false;
}

