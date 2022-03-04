#ifndef GAMECPP_H
#define GAMECPP_H
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QLineEdit>
#include "Player.h"
#include "Score.h"
class Game:public QGraphicsView
{Q_OBJECT
public:
    Game();
    void displayMenu();
    void gameOver();
    void displayGameOver(QString textToDisplay);
    void displayLeaderBoard(QString textToDisplay, QList<int> score,QList<QString> nume );
    void drawPanel(int x,int y,int width,int height,QColor color,double opacity);

    QGraphicsScene * scene;
    Player* player;
    Score* score;
    QTimer * timer;
    QLineEdit* nume;
public slots:
    void start();
    void closed();
    void restart();
    void help();
    void back();
    void back1();
    void scoreOverTime();
    void addScore();
    void showBoard();

};

#endif // GAMECPP_H
