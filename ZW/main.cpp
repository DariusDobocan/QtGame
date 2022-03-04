#include <QApplication>
#include <QGraphicsScene>
#include "Player.h"
#include "Zombie.h"
#include <QGraphicsView>
#include <QTimer>
#include "Game.h"

Game*  game; //declarare globala game
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    game = new Game();
    game->show();
    game->displayMenu();

    return a.exec();
}
