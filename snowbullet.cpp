#include "snowbullet.h"

snowBullet::snowBullet()
{
}
double snowBullet::getSpeed() const
{
    return speed;
}

void snowBullet::setSpeed(double value)
{
    speed = value;
}
double snowBullet::getXCo() const
{
    return xCo;
}

void snowBullet::setXCo(double value)
{
    xCo = value;
}
double snowBullet::getYCo() const
{
    return yCo;
}

void snowBullet::setYCo(double value)
{
    yCo = value;
}
int snowBullet::getSlow() const
{
    return slow;
}

void snowBullet::setSlow(int value)
{
    slow = value;
}




