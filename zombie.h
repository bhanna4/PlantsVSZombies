#ifndef ZOMBIE_H
#define ZOMBIE_H

enum zomb{Regular, Flag, Conehead, Buckethead, Newspaper};

class Zombie
{
public:
    Zombie();
    Zombie(zomb object);
    zomb type;
private:
    int life1, life2, attack;
    double rate, speed, speed2;
    /*QGraphicsPixmapItem *imageMap;
    QImage *image;*/
};

#endif // ZOMBIE_H
