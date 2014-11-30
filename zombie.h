#ifndef ZOMBIE_H
#define ZOMBIE_H

enum zomb{Regular, Flag, Conehead, Buckethead, Newspaper};

class Zombie
{
public:
    Zombie();
    Zombie(zomb object);
    zomb type;

    double getSpeed() const;
    void setSpeed(double value);

    double getXCo() const;
    void setXCo(double value);

    double getYCo() const;
    void setYCo(double value);

    int getSlow() const;
    void setSlow(int value);

private:
    int life1, life2, attack;
    double rate, speed2;

    double speed=5, xCo, yCo;
    int slow;
    /*QGraphicsPixmapItem *imageMap;
    QImage *image;*/
};

#endif // ZOMBIE_H
