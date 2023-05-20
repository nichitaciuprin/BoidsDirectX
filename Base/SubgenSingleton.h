#pragma once

#include "Subgen.h"

class SubgenSingleton
{
public:
    static int Next()
    {
        return subgen.Next();
    }
    static float FractionUnsigned()
    {
        return subgen.FractionUnsigned();
    }
    static float FractionSigned()
    {
        return subgen.FractionSigned();
    }
    static float Range(float min, float max)
    {
        return subgen.Range(min,max);
    }
private:
    static Subgen subgen;
    static bool inited;
};
Subgen SubgenSingleton::subgen = Subgen(0);
bool SubgenSingleton::inited = false;