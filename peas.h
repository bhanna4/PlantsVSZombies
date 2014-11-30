#ifndef PEAS_H
#define PEAS_H

class Peas
{
public:
    Peas();


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

#endif // PEAS_H
