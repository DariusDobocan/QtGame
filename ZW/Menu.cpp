#include "Menu.h"
#include <QBrush>
#include <QGraphicsTextItem>

Menu::Menu(QString name, QGraphicsItem *parent): QGraphicsRectItem(parent){

    //Creare buton
    setRect(0,0,200,50);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkRed);
    setBrush(brush);

    text = new QGraphicsTextItem(name,this);
    text->setDefaultTextColor(Qt::white);
    int x = rect().width()/2 - text->boundingRect().width()/2;
    int y = rect().height()/2 - text->boundingRect().height()/2;
    text->setPos(x,y);

    setAcceptHoverEvents(true);
}

void Menu::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit clicked();

}

void Menu::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    //daca trecem cu click-ul peste buton schimbam culoarea
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::red);
    setBrush(brush);
    setBrush(brush);

}

void Menu::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    //revenim la culoarea initiala
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkRed);
    setBrush(brush);
}



