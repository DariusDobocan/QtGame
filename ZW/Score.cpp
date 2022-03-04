#include "Score.h"
#include <QFont>
Score::Score(QGraphicsItem* parent): QGraphicsTextItem(parent)
{
    score = 0;
    //desenare scor
    setPlainText(QString("Score: ")+ QString::number(score));
    setDefaultTextColor(Qt::blue);
    setFont(QFont("times",10));
    setFlag(GraphicsItemFlag::ItemIsPanel); //flag anti glont
}

void Score::increaseScoreBy(int x)
{
    score = score + x;
    setPlainText(QString("Score: ")+ QString::number(score));//scorul creste cu cat traim mai mult
}

int Score::getScore()
{
    return score;
}

void Score::setScore(int s)
{
    score = s;
}
