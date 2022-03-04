#ifndef GLONT_H
#define GLONT_H
#include <QGraphicsRectItem>
#include <QObject>
#include "Zombie.h"
class Glont:public QObject,public QGraphicsRectItem{
    Q_OBJECT
public:
    Glont();
    int dirX=0,dirY=0;
public slots:
    void move();
};

#endif // GLONT_H
