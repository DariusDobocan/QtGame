#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QTimer>

class Zombie : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
    public:
    Zombie();
    int mvmSpd=5;
    int scoreLmt=500;
    bool top=false,bot=false,left=false,right=false;

public slots:
    void move();

};


#endif // ZOMBIE_H
