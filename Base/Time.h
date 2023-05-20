#include <windows.h>

double TicksPerSecondCache = 0;
long TimeOld = 0;
double TicksPerSecond()
{
    if (TicksPerSecondCache == 0)
    {
        LARGE_INTEGER perfFreq;
        QueryPerformanceFrequency(&perfFreq);
        LONGLONG perfCounterFrequency = perfFreq.QuadPart;
        TicksPerSecondCache = (double)perfCounterFrequency;
    }
    return TicksPerSecondCache;
}
long GetTime()
{
    LARGE_INTEGER ticks;
    QueryPerformanceCounter(&ticks);
    return (long)ticks.QuadPart;
}
float GetDeltaTime(long oldTime, long newTime)
{
    double diff = (double)(newTime - oldTime);
    return (float)(diff/TicksPerSecond());
}
float GetDeltaTime2()
{
    long TimeNew = GetTime();
    float result = GetDeltaTime(TimeOld,TimeNew);
    TimeOld = TimeNew;
    return result;
}