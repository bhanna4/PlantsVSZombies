#include "peas.h"

Peas::Peas()
{
}
double Peas::getSpeed() const
{
    return speed;
}

void Peas::setSpeed(double value)
{
    speed = value;
}
double Peas::getXCo() const
{
    return xCo;
}

void Peas::setXCo(double value)
{
    xCo = value;
}
double Peas::getYCo() const
{
    return yCo;
}

void Peas::setYCo(double value)
{
    yCo = value;
}
int Peas::getSlow() const
{
    return slow;
}

void Peas::setSlow(int value)
{
    slow = value;
}




