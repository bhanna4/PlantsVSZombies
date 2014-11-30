#ifndef SNOWBULLET_H
#define SNOWBULLET_H

class snowBullet
{
public:
    snowBullet();

    double getSpeed() const;
    void setSpeed(double value);

    double getXCo() const;
    void setXCo(double value);

    double getYCo() const;
    void setYCo(double value);

    int getSlow() const;
    void setSlow(int value);

private:
    double speed=3, xCo, yCo;
    int slow;
};

#endif // SNOWBULLET_H
