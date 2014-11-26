#ifndef LAWN_H
#define LAWN_H

#include "sunshine.h"
#include <QGraphicsView>
#include "plants.h"


class Lawn : public QGraphicsView
{
    Q_OBJECT
public:
    explicit Lawn(QWidget *parent = 0);
    Sunshine sun;
    plants currentType;
    void setType(plants daType);
    void drawMyLawn(int row);

signals:
    void click(int x, int y, Plants *daPlant);

public slots:

};

#endif // LAWN_H
