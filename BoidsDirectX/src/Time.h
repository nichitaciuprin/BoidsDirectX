long GetTime()
{
    LARGE_INTEGER ticks;
    QueryPerformanceCounter(&ticks);
    return (long)ticks.QuadPart;
}
float GetDeltaTime(long oldTime, long newTime)
{
    // TODO cache this. Value is system readonly
    LARGE_INTEGER perfFreq;
    QueryPerformanceFrequency(&perfFreq);
    LONGLONG perfCounterFrequency = perfFreq.QuadPart;

    double diff = (double)(newTime - oldTime);
    double ticksPerSecond = (double)perfCounterFrequency;

    return (float)(diff/ticksPerSecond);
}