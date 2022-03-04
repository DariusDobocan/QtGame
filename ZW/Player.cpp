#include "Player.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <math.h>
#include "glont.h"
#include "Game.h"
#include <QDebug>
extern Game * game; //anuntam faptul ca exista o instanta globala game

Player::Player()
{
    //creare player
    setRect(0,0,25,25);
    setBrush(Qt::blue);

    //creare si conectare timer spawn zombie
    timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(spawn()));
    timer->start(1500);
}

void Player::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Left){
        l = true;
        r = false;  //verificam ultima directie a jucatorului
        u = false;
        d = false;
        if(pos().x()>0)
        setPos(x()-10,y());//miscare la stanga
    }
    else if(event->key() == Qt::Key_Right){
        l = false;
        r = true;
        u = false;
        d = false;
        if(pos().x()+10<800)
        setPos(x()+10,y());//miscare la dreapta
    }
    else if(event->key() == Qt::Key_Up){
        l = false;
        r = false;
        u = true;
        d = false;
        if(pos().y()>0)
        setPos(x(),y()-10);//miscare sus
    }
    else if(event->key() == Qt::Key_Down){
        l = false;
        r = false;
        u = false;
        d = true;
        if(pos().y()+10<600)
        setPos(x(),y()+10);// miscare jos
    }
    if(event->key() == Qt::Key_Space){
            Glont* glont = new Glont(); //creare nou glont
            glont->setBrush(Qt::black);
            glont->setPos(x(),y());
            if(l == true) glont->dirX=-15; //tragem in ultima directie in care ne-am miscat
            if(r == true) glont->dirX=15;
            if(u == true) glont->dirY=-15;
            if(d == true) glont->dirY=15;
            scene()->addItem(glont);
        }
}

void Player::spawn()
{

        Zombie * zombie1 = new Zombie(); //creare zombie
        scene()->addItem(zombie1);

        //modificare dificultate in functie de scor
        if(game->score->getScore() > scoreLmt1) //folosim pointer din game catre scor
        {
            spwnSpd -= 250;
            scoreLmt1+=500;
        }

        if(game->score->getScore() >1000)
        {
            Zombie * zombie2 = new Zombie();
            scene()->addItem(zombie2);
        }
        if(spwnSpd > 50)
            timer->setInterval(spwnSpd);

}



