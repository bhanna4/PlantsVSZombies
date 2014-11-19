#ifndef LAWN_H
#define LAWN_H

#include <QGraphicsView>

class Lawn : public QGraphicsView
{
    Q_OBJECT
public:
    explicit Lawn(QWidget *parent = 0);

signals:

public slots:
    void mousePressEvent(QMouseEvent *event);
};

#endif // LAWN_H
