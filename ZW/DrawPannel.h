#ifndef DRAWPANNEL_H
#define DRAWPANNEL_H
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
class DrawPannel:public QGraphicsView
{
public:
    void drawPanel(int x,int y,int width,int height,QColor color,double opacity);
};

#endif // DRAWPANNEL_H
