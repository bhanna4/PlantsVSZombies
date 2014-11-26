#include "lawn.h"
#include <QMouseEvent>
#include <QDebug>

Lawn::Lawn(QWidget *parent) :
    QGraphicsView(parent)
{

}

void Lawn::setType(plants daType)
{
    currentType = daType;
}

