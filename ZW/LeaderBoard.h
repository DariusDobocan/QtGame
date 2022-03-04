#ifndef LEADERBOARD_H
#define LEADERBOARD_H
#include <QGraphicsTextItem>

class LeaderBoard
{
public:
    QList<QString> nume;
    QList<int> score;
    void sortare(QList<int> score,QList<QString> nume);
};

#endif // LEADERBOARD_H
