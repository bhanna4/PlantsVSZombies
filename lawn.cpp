#include "lawn.h"
#include <QMouseEvent>
#include <QDebug>

Lawn::Lawn(QWidget *parent) :
    QGraphicsView(parent)
{
}

void Lawn::mousePressEvent(QMouseEvent *event)
{
    qDebug() << event->pos();
}
