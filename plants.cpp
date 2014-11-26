#include "plants.h"

Plants::Plants(QObject *parent) :
    QObject(parent)
{
}

Plants::Plants(plants object)
{
    cost=0;
    life=0;
    range=0;
    damage=0;
    rate=0;
    splash=0;
    slow=0;
    bomb=0;
    seeding=0;
    sun=0;
    need=0;

    type = object;

    switch(type)
    {
    case peaShooter:
        cost=100;
        life=4;
        range=9999;
        damage=1;
        rate=1.5;
        seeding=7.5;
        //image = new QImage(":/PeaShooter.png");
        //imageMap->setPixmap(QPixmap::fromImage(*image).scaled(50,50));
        break;

    case sunFlower:
        cost=50;
        life=4;
        rate=24;
        seeding=7.5;
        sun=1;
    case cherryBomb:
        cost=150;
        life=9999;
        range=1;
        damage=90;
        rate=1;
        splash=3;
        bomb=1;
        seeding=50;
    case wallNut:
        cost=50;
        life=72;
        seeding=30;
    case potatoMine:
        cost=25;
        life=4;
        range=1;
        damage=90;
        rate=15;
        bomb=1;
        seeding=30;
    case snowPea:
        cost=175;
        life=4;
        range=9999;
        damage=1;
        rate=1.5;
        slow=1;
        seeding=7.5;
    case chomper:
        cost=150;
        life=4;
        range=1;
        damage=150;
        rate=42;
        seeding=7.5;
    case repeater:
        cost=200;
        life=4;
        range=9999;
        damage=2;
        rate=1.5;
        seeding=7.5;
        need=1;
}


}

