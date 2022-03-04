#include "Zombie.h"
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QTimer>
#include "Game.h"
#include <windows.h>
#include <stdlib.h>
extern Game * game;//anuntam faptul ca exista o instanta globala game

Zombie::Zombie(): QGraphicsRectItem()
{
    //creare zombie
     setRect(0,0,35,35);
     setBrush(Qt::green);

     // aparitie aleatorie
     top=false;bot=false;left=false;right=false;
     int rnd1 = rand() % 4;
     int rnd2;
     if(rnd1 == 0) top = true;
     else if (rnd1==1) bot = true;
     else if (rnd1==2) left = true;
     else if (rnd1==3) right = true;

     if(top == true)
     {
         rnd2 = rand() % 700;
         setPos(rnd2,0);
     }
     if(bot == true)
     {
         rnd2 = rand() % 700;
         setPos(rnd2,600);
     }
     if(left == true)
     {
         rnd2 = rand() % 500;
         setPos(0,rnd2);
     }
     if(right == true)
     {
         rnd2 = rand() % 500;
         setPos(800,rnd2);
     }

     //creare si conectare timer la move()
     QTimer * timer = new QTimer();
     connect(timer,SIGNAL(timeout()),this,SLOT(move()));

     timer->start(50);
}
void Zombie::move()
{
    //verificare coliziune
    QList<QGraphicsItem *> colliding_items = collidingItems();

    for(int i= 0 ,n=colliding_items.size();i < n;++i)
    {
        if(colliding_items[i]->flags().testFlag(QGraphicsItem::ItemIsFocusable)) //daca este atins player-ul;
        {
            colliding_items[i]->setActive(false);

            game->scene->removeItem(colliding_items[i]); //eliberarea ecranului
            game->scene->removeItem(this);
            game->scene->removeItem(game->score);
            delete colliding_items[i];
            delete this;
            game->gameOver();   //apelare gameOver();

            return;
        }


    }

    //modificare dificultate in functie de scor
    if(game->score->getScore() > scoreLmt)
    {if(mvmSpd > 15)
     mvmSpd+= 2;
      else
     mvmSpd += 5;
     scoreLmt+=500;
    }

    //miscare in functie de zona de aparitie
    if(top) setPos(x(),y()+mvmSpd);
    if(bot) setPos(x(),y()-mvmSpd);
    if(left) setPos(x()+mvmSpd,y());
    if(right) setPos(x()-mvmSpd,y());

    // stergere zombie daca a iesit de pe ecran pentru a salva memorie
    if(pos().y()<0 || pos().y()>600 || pos().x()<0 || pos().x()>800)
    {
        scene()->removeItem(this);
        delete(this);
    }
}

