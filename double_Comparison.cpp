// double_comparison.cpp
#include "stdafx.h"
// double_comparison.cpp
#include "double_comparison.h"

bool AreDoubleSame(double dFirstVal, double dSecondVal)
{
    return std::fabs(dFirstVal - dSecondVal) < 0.3;
}

bool AreDoubleDifferent(double a, double b)
{
    return std::fabs(a - b) > 0.3;
}