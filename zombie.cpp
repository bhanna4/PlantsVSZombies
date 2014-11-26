#include "zombie.h"

Zombie::Zombie()
{

}
Zombie::Zombie(zomb object)
{
    life1 = 0;
    life2 = 0;
    rate = 0;
    speed = 0;
    attack = 1;
    speed2 = 0;

    type = object;

    switch(type)
    {
    case Regular:
        life2 = 10;
        rate = 0.5;
        speed = 5;
        /*image = new QImage(":/PeaShooter.png");
        imageMap->setPixmap(QPixmap::fromImage(*image).scaled(50,50));*/
        break;

    case Flag:
        life2 = 10;
        rate = 0.5;
        speed = 3.75;

        break;

    case Conehead:
        life1 = 18;
        life2 = 10;
        rate = 0.5;
        speed = 5;

        break;

    case Buckethead:
        life1 = 55;
        life2 = 10;
        rate = 0.5;
        speed = 5;

        break;

    case Newspaper:
        life1 = 8;
        life2 = 8;
        rate = 0.5;
        speed = 5;
        speed2 = 2;

        break;
}

}
