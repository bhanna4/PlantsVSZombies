#ifndef SUNSHINE_H
#define SUNSHINE_H
#include <QTime>

class Sunshine
{
public:
    Sunshine();
    double sunPoints;
    void sunPointAdd();
    void sunPointSubtract(int cost);
};

#endif // SUNSHINE_H
