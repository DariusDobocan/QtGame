#include "glont.h"
#include "Game.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsTextItem>

extern Game* game;//anuntam faptul ca exista o instanta globala game

Glont::Glont()
{
 // desenat glontul
    setRect(0,0,5,5);

 // conectam
    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    timer->start(50);
}

void Glont::move()
{
    //verificare coliziune
    QList<QGraphicsItem *> colliding_items = collidingItems();

    for(int i= 0 ,n=colliding_items.size();i < n;++i)
    {
        if(!colliding_items[i]->flags().testFlag(QGraphicsItem::ItemIsFocusable)) //verificare daca atinge player-ul

            if(!colliding_items[i]->flags().testFlag(QGraphicsItem::ItemIsPanel)) //verificare daca atinge alte componente
        {
            game->score->increaseScoreBy(100); //crestere scor

            game->scene->removeItem(colliding_items[i]);//stergere glont si zombie
            game->scene->removeItem(this);

            delete colliding_items[i];
            delete this;
            return;
        }


    }

    setPos(x()+dirX,y()+dirY);
    if(pos().y()<0 || pos().y()>600 || pos().x()<0 || pos().x()>800) //stergere glont daca a iesit de pe fereastra
    {
        scene()->removeItem(this);
        delete(this);
    }
}
