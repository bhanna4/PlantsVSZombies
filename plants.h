#ifndef PLANTS_H
#define PLANTS_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QImage>

enum plants{peaShooter, sunFlower, cherryBomb, wallNut, potatoMine, snowPea, chomper, repeater};
class Plants : public QObject
{
    Q_OBJECT
public:
    explicit Plants(QObject *parent = 0);
    Plants(plants object);
    void setCost(const int cost);
    void getCost() const;
    void setLife(const int life);
    void getLife() const;
    void setRange(const int range);
    void getRange() const;
    void setDamage(const int damage);
    void getDamage() const;
    void setSplash(const int splash);
    void getSplash() const;
    void setSlow(const int slow);
    void getSlow() const;
    void setBomb(const int bomb);
    void getBomb() const;
    void setSun(const int sun);
    void getSun() const;
    void setNeed(const int need);
    void getNeed() const;
    void setSeeding(const double seeding);
    void getSeeding() const;
    void setRate(const double rate);
    void getRate() const;
    plants type;
private:
    int cost, life, range, damage, splash, slow, bomb, sun, need;
    double seeding, rate;
    QGraphicsPixmapItem *imageMap;
    QImage *image;


signals:

public slots:

};

#endif // PLANTS_H
