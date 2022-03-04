#include "Game.h"
#include "Player.h"
#include "QTimer"
#include "Menu.h"
#include "Score.h"
#include "LeaderBoard.h"
#include <QGraphicsItem>
#include <QFile>
#include <QLineEdit>
#include <QDebug>
#include <QMessageBox>
#include <QPushButton>
#include <QValidator>
Game::Game()
{
    //stergere scroll
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800,600);

    //creare scena
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,800,600);
    setScene(scene);


}
void Game::start()
{
    scene->clear();

    player = new Player();

    // adaugare player in scena
    scene->addItem(player);

    // adaugare scor in scena
    score = new Score();
    scene->addItem(score);

    player->setFlag(QGraphicsItem::ItemIsFocusable); // player-ul este "miscabil"
    player->setFocus();

    // adaugare fereastra
    QGraphicsView * view = new QGraphicsView(scene);
    view->setFixedSize(800,600);

    player->setPos(view->width()/2,view->height()/2);

    //creare buton meniu
    Menu* butonMenu = new Menu(QString("Main menu"));
    butonMenu->setPos(600,550);
    butonMenu->setFlag(QGraphicsItem::ItemIsPanel);
    scene->addItem(butonMenu);
    connect(butonMenu,SIGNAL(clicked()),this,SLOT(back1()));

    //timer scor
    timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(scoreOverTime()));
    timer->start(1000);

}
void Game::closed()
{
    this->close(); //inchidere
}

void Game::restart()
{
    this->start();//repornire
}

void Game::help() //fereastra help
{
    scene->clear();
    drawPanel(0,0,800,600,Qt::white,0.55); //desenare fundal

    //creare titlu
    QGraphicsTextItem* TitluText = new QGraphicsTextItem(QString("How to play"));
    QFont titluFont("comic sans",25);
    TitluText->setFont(titluFont);
    TitluText->setPos(this->width()/2 - TitluText->boundingRect().width()/2,100);
    scene->addItem(TitluText);

    //creare text
    QGraphicsTextItem* text = new QGraphicsTextItem(QString("Foloseste [↑][↓][→][←] pentru a te misca, si [space] pentru a trage."));
    QFont textFont("comic sans",15);
    text->setFont(textFont);
    text->setPos(12,245);
    scene->addItem(text);


    //creare buton back
    Menu* butonBack = new Menu(QString("Go back"));
    int bhxPos = this->width()/2 - butonBack->boundingRect().width()/2;
    int bhyPos = 425;
    butonBack->setPos(bhxPos,bhyPos);
    scene->addItem(butonBack);
    connect(butonBack,SIGNAL(clicked()),this,SLOT(back()));
}

void Game::back() //apelare reintoarcere main menu
{
    scene->clear();
    displayMenu();
}

void Game::back1()//apelare reintoarcere main menu in game
{
    scene->clear();
    disconnect(timer,SIGNAL(timeout()),this,SLOT(scoreOverTime())); //deconectam timer-ul pentru scor
    displayMenu();
}

void Game::drawPanel(int x, int y, int width, int height, QColor color, double opacity) //metoda desenare fundal
{
    QGraphicsRectItem* panel = new QGraphicsRectItem(x,y,width,height); //creare patrat
    QBrush brush;
    brush.setStyle(Qt::SolidPattern); //alegere culoare
    brush.setColor(color);
    panel->setBrush(brush);
    panel->setOpacity(opacity);//alegere opacitate
    scene->addItem(panel);//adaugare

}

void Game::displayMenu()//meniul principal
{
 QGraphicsTextItem* titluText = new QGraphicsTextItem(QString("ZWorld")); //adaugare titlu
 QFont titluFont("comic sans",50);
 titluText->setFont(titluFont);
 int txPos = this->width()/2 - titluText->boundingRect().width()/2;
 int tyPos = 150;
 titluText->setPos(txPos,tyPos);
 scene->addItem(titluText);

 //adaugare buton play
 Menu* butonPlay = new Menu(QString("Play"));
 int bpxPos = this->width()/2 - butonPlay->boundingRect().width()/2;
 int bpyPos = 275;
 butonPlay->setPos(bpxPos,bpyPos);
 QObject::connect(butonPlay,SIGNAL(clicked()),this,SLOT(start()));
 scene->addItem(butonPlay);

 //adaugare buton quit
 Menu* butonQuit = new Menu(QString("Quit"));
 int bqxPos = this->width()/2 - butonPlay->boundingRect().width()/2;
 int bqyPos = 350;
 butonQuit->setPos(bqxPos,bqyPos);
 connect(butonQuit,SIGNAL(clicked()),this,SLOT(closed()));
 scene->addItem(butonQuit);

 //adaugare buton how to play
 Menu* butonHow = new Menu(QString("How to play"));
 int bhxPos = this->width()/2 - butonPlay->boundingRect().width()/2;
 int bhyPos = 425;
 butonHow->setPos(bhxPos,bhyPos);
 scene->addItem(butonHow);
 connect(butonHow,SIGNAL(clicked()),this,SLOT(help()));

 //adaugare buton LeaderBoard
 Menu* butonScore = new Menu(QString("LeaderBoard"));
 int bsxPos = this->width()/2 - butonPlay->boundingRect().width()/2;
 int bsyPos = 500;
 butonScore->setPos(bsxPos,bsyPos);
 scene->addItem(butonScore);
 connect(butonScore,SIGNAL(clicked()),this,SLOT(showBoard()));
}

void Game:: gameOver()//incheierea jocului
{
    QString message;
    timer->disconnect(timer,SIGNAL(timeout()),this,SLOT(scoreOverTime()));
    displayGameOver(QString("Felicitari, ai facut ") + QString::number(score->getScore()) + QString(" de puncte"));
}

void Game::displayGameOver(QString textToDisplay)//meniu game over
{
    //desenare fundal
    scene->clear();
    drawPanel(0,0,800,600,Qt::darkRed,0.80);
    drawPanel(215,110,400,600,Qt::lightGray,0.75);


    //creare butoane
    Menu* butonAgain = new Menu(QString("Play again"));
    butonAgain->setPos(320,375);
    scene->addItem(butonAgain);
    connect(butonAgain,SIGNAL(clicked()),this,SLOT(restart()));

    Menu* butonQuit = new Menu(QString("Quit"));
    butonQuit->setPos(320,450);
    scene->addItem(butonQuit);
    connect(butonQuit,SIGNAL(clicked()),this,SLOT(closed()));

    Menu* butonBack = new Menu(QString("Main menu"));
    butonBack->setPos(320,525);
    scene->addItem(butonBack);
    connect(butonBack,SIGNAL(clicked()),this,SLOT(back()));


    //creare titlu
    QGraphicsTextItem* titluText = new QGraphicsTextItem(QString(textToDisplay));
    QFont titluFont("comic sans",15);
    titluText->setFont(titluFont);
    titluText->setPos(225,150);
    scene->addItem(titluText);


    //creare mod salvare scor
    nume = new QLineEdit();
    QPushButton* save = new QPushButton();
    save->move(485,290);
    save->resize(100,40);
    save->setText("Save Here");
    nume->move(250,300);

    scene->addWidget(nume);
    scene->addWidget(save);

    //setare doar litere si cifre, fara spatii
    nume->setValidator(new QRegExpValidator( QRegExp("^[A-Za-z0-9]+"), this ));
    connect(save,SIGNAL(clicked()),this,SLOT(addScore()));

}

void Game::displayLeaderBoard(QString textToDisplay, QList<int> score, QList<QString> nume)//fereastra top jucatori
{
    //creare fundal
    scene->clear();
    drawPanel(0,0,800,600,Qt::darkRed,0.75);
    drawPanel(200,100,400,600,Qt::gray,1);

    //creare titlu
    QGraphicsTextItem* titluText = new QGraphicsTextItem(QString(textToDisplay));
    QFont titluFont("comic sans",30);
    titluText->setFont(titluFont);
    titluText->setPos(315,150);
    titluText->setDefaultTextColor(Qt::yellow);
    scene->addItem(titluText);

    int x=0;
    //afisare top 10
    for(int i = 0;i<score.size() && i<=10;++i){
        scene->addText(QString::number(i+1) +"."+ QString(nume[i])+" "+QString::number(score[i]))->setPos(350,250 + x);
        x += 25;
    }

    //creare buton meniu
    Menu* butonBack = new Menu(QString("Go back"));
    int bhxPos = this->width()/2 - butonBack->boundingRect().width()/2;
    int bhyPos = 525;
    butonBack->setPos(bhxPos,bhyPos);
    scene->addItem(butonBack);
    connect(butonBack,SIGNAL(clicked()),this,SLOT(back()));

}

void Game::scoreOverTime()
{
    score->increaseScoreBy(50);//creste scorul cu 50 pe secunda
}

void Game::addScore()//metoda adaugare scor fisier
{
    QFile file("C:/Users/doboc/Documents/ZW/scor.txt"); //ATENTIE trebuie modificata calea de acces, mie altfel nu imi mergea

    //verificare fisier
    if(!file.open(QIODevice::Append))
    {
        qCritical() << "Nu am deschis fisierul";
        qCritical() << file.errorString();
        return;
    }

    //scriere in fisier
    QTextStream stream(&file);
    stream << nume->text() + ' ' + QString::number(score->getScore()) << endl;

    file.close();
}

void Game::showBoard()// sortarea si adaugare in top 10
{
    QFile file("C:/Users/doboc/Documents/ZW/scor.txt");//ATENTIE trebuie modificata calea de acces, mie altfel nu imi mergea

    //verificare fisier
    if(!file.open(QIODevice::ReadOnly))
    {
        qCritical() << "Nu am deschis fisierul";
        qCritical() << file.errorString();
        return;
    }
    LeaderBoard* l = new LeaderBoard();

    QTextStream stream(&file);
    QStringList list1;

    //citire din fisier
    while(!stream.atEnd())
    {
        list1 = stream.readLine().split(QLatin1Char(' ')); //stim ca in fisier se afla nume si apoi scor, asa ca folosim split unde vom
        //adaugare in leaderboard                           // avea in list[0] numele si in list[1] scorul
        l->nume.append(list1[0]);
        l->score.append(list1[1].toInt());
    }

    l->sortare(l->score,l->nume); //sortare leaderboard


    displayLeaderBoard("Top 10",l->score,l->nume);

    file.close();
}


