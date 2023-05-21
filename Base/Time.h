#pragma once

#include <windows.h>

typedef LONGLONG TICKS;

TICKS TicksPerSecondCache = 0;
TICKS TicksPerMillisecondCache = 0;
TICKS FixedTimeStepCache = 0;
TICKS TimeOld = 0;
TICKS TimeNew = 0;

TICKS TicksPerSecond()
{
    if (TicksPerSecondCache == 0)
    {
        LARGE_INTEGER perfFreq;
        QueryPerformanceFrequency(&perfFreq);
        auto perfCounterFrequency = perfFreq.QuadPart;
        TicksPerSecondCache = perfCounterFrequency;
    }
    return TicksPerSecondCache;
}
TICKS TicksPerMillisecond()
{
    if (TicksPerMillisecondCache == 0)
        TicksPerMillisecondCache = TicksPerSecond()/1000;
    return TicksPerMillisecondCache;
}
TICKS FixedTimeStep()
{
    if (FixedTimeStepCache == 0)
        FixedTimeStepCache = TicksPerMillisecond()*20;
    return FixedTimeStepCache;
}
TICKS GetTime()
{
    LARGE_INTEGER ticks;
    QueryPerformanceCounter(&ticks);
    return ticks.QuadPart;
}
TICKS GetCalcTime(TICKS oldTime, TICKS newTime)
{
    if (oldTime > newTime)
       return LLONG_MAX - oldTime + newTime;
    return newTime - oldTime;
}
void WaitAfterRender()
{
    TICKS waitTicks = 0;
    if (TimeOld == 0)
    {
        waitTicks = FixedTimeStep()/TicksPerMillisecond();
    }
    else
    {
        TimeNew = GetTime();
        auto calcTime = GetCalcTime(TimeOld, TimeNew);
        auto duno = FixedTimeStep();
        waitTicks = duno - calcTime;
        if (waitTicks < 0)
            waitTicks = 0;
    }
    auto milliseconds = (DWORD)(waitTicks/TicksPerMillisecond());
    Sleep(milliseconds);
    TimeOld = GetTime();
}