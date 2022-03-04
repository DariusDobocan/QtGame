#ifndef PLAYER_H
#define PLAYER_H
#include <QGraphicsRectItem>
#include <QObject>


class Player:public QObject, public QGraphicsRectItem{
Q_OBJECT
   public:
     Player();
     void keyPressEvent(QKeyEvent * event);
     bool l,r,u,d;
     int spwnSpd=1500;
     int scoreLmt1=500;
     QTimer * timer;
public slots:
     void spawn();

};

#endif // PLAYER_H
