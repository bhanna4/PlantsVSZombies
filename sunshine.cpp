#include "sunshine.h"

Sunshine::Sunshine()
{
    sunPoints = 500;
}

void Sunshine::sunPointAdd()
{
    sunPoints += 25;
}

void Sunshine::sunPointSubtract(int cost)
{
    sunPoints -= cost;
}
