#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <QMouseEvent>
#include <QBrush>
#include <QPen>


// PLEASE NOTE FOR 3G MY TOOL TIP APPEARS IN THE STATUS BAR!! THANK YOUUUU

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    peaCount = 0;

    pA=1;

    setButtons();

    setSceneInitial();


     timer = new QTimer(this); //timer function is needed for the start and stop functionality
     connect(timer, SIGNAL(timeout()), this, SLOT(moveSun()));
     timer->start(20);

    connect(ui->LawnScreen,SIGNAL(click(int,int,Plants*)),this,SLOT(click(int,int,Plants*)));

    QTimer *bulletTimer = new QTimer;

    connect(bulletTimer, SIGNAL(timeout()), this, SLOT(bulletMove()));
    bulletTimer->start(100);

    QTimer *snowbulletTimer = new QTimer;

    connect(snowbulletTimer, SIGNAL(timeout()), this, SLOT(snowBulletMove()));
    snowbulletTimer->start(100);

    QTimer *zombieTimer = new QTimer;

    connect(zombieTimer, SIGNAL(timeout()), this, SLOT(zombMove()));
    zombieTimer->start(100);

    QTimer *chomperTimer = new QTimer;

    connect(chomperTimer, SIGNAL(timeout()), this, SLOT(chomperCheck()));
    chomperTimer->start(100);


    QString MyFiles = "C:/Qt/Tools/QtCreator/bin/PlantsvsZombies";
    QFile UsersFiles("C:/Qt/Tools/QtCreator/bin/PlantsvsZombies/pvz_players.csv");

   /* if(!(checkValidity(UsersFiles)))
    {
        ui->statusBar->showMessage("Unable to load player data.");
    }
    else
    {
        ui->statusBar->showMessage("Player Loaded.");
        //SetUser(UsersFiles);
    }
    //SetUser(UsersFiles);*/

    //ReadParseUserFile(UsersFiles);

    qDebug()<<players.size();

    for(int i = 0; i<players.size(); i++)
    {
        qDebug()<<players.size();
    }

    if(players.size()==0)
    {
        ui->DeleteUserButton->setEnabled(false);
        ui->UserChoose->setEnabled(false);
        ui->StartButton->setEnabled(false);
        ui->QuitButon->setEnabled(false);
        ui->RestartLevelButton->setEnabled(false);
    }

    comboBoxSet();

    QString LevelFiles = "C:/Qt/Tools/QtCreator/bin/PlantsvsZombies/pvz_levels.csv";

    if(!(checkValidity(LevelFiles)))
    {
        ui->statusBar->showMessage("Unable to load level data.");
        daMessageBox.setText("Level data not found. The zombies have eaten it.");
        daMessageBox.setStandardButtons(QMessageBox::Ok);
        daMessageBox.setDefaultButton(QMessageBox::Ok);
        int ret = daMessageBox.exec();
        if (ret == QMessageBox::Ok) close();

    }
    else
    {
        //ui->statusBar->showMessage("Levels Loaded.");
        SetFile(LevelFiles);
    }

    ReadParseLevelFile();

    /*if (!validateLevelInfo())
        {
            ui->statusBar->showMessage("Levels not able to be loaded.");
            daMessageBox.setText("The levels are not able to be loaded.");
            daMessageBox.setStandardButtons(QMessageBox::Ok);
            daMessageBox.setDefaultButton(QMessageBox::Ok);
            int q = daMessageBox.exec();
            switch (q){
            case QMessageBox::Ok:
                close();
                break;
            default:
                break;
            }
        }*/
    /* if (!validateUserInfo())
        {
            daMessageBox.setText("Warning: You may not save data with this user file. Game will continue without users.");
            daMessageBox.setStandardButtons(QMessageBox::Ok);
            daMessageBox.setDefaultButton(QMessageBox::Ok);
            int q = daMessageBox.exec();
            switch (q){
            case QMessageBox::Ok:
                break;
            default:
                break;
            }
        }*/


}

void MainWindow::drawMyLawn(int row)
{

    QBrush myBrush;
    QPen myPen(QColor(0,0,0));

    if(row==1)
    {
        for(int i =0; i<5; i++)
        {
            for(int j = 0; j<10; j++)
            {
                if(j==0)
                {
                    myBrush = QColor(131, 80, 28);
                }
                else
                {
                   if((i==0)||(i==1)||(i==3)||(i==4))
                   {
                       myBrush = QColor(131, 80, 28);
                   }
                   else if((i==2)&&(j%2==0))
                   {
                    myBrush = QColor(20,215,53);
                   }
                   else if((i==2)&&(!j%2==0))
                   {
                       myBrush = QColor(32, 131, 28);
                   }
                }
                double column = j;
                double row = i;
                scene->addRect(column*63, row*63, 63, 63, myPen, myBrush);
            }
        }

        QImage mower("C:/Qt/Tools/QtCreator/bin/PlantsvsZombies/Lawn_Mower.png");
        regz4 = new QGraphicsPixmapItem(QPixmap::fromImage(mower));
        //pic->setScale(0.4);
        regz4->setPos(0,126);
        scene->addItem(regz4);

    }
    else if(row==3)
    {
        for(int i =0; i<5; i++)
        {
            for(int j = 0; j<10; j++)
            {
                if(j==0)
                {
                    myBrush = QColor(131, 80, 28);
                }
                else
                {
                   if((i==0)||(i==4))
                   {
                        myBrush = QColor(131, 80, 28);
                   }
                   else if((i%2==0)&&(j%2==0))
                   {
                    myBrush = QColor(32, 131, 28);
                   }
                   else if((i%2==0)&&(!j%2==0))
                   {
                       myBrush = QColor(20,215,53);
                   }
                   else if((!i%2==0)&&(j%2==0))
                   {
                    myBrush = QColor(20,215,53);
                   }
                   else if((!i%2==0)&&(!j%2==0))
                   {
                       myBrush = QColor(32, 131, 28);
                   }
                }
                double column = j;
                double row = i;
                scene->addRect(column*63, row*63, 63, 63, myPen, myBrush);
            }
        }
        for(int i = 1; i<4; i++)
        {
            int y;
            y = i*63;
            QImage mower("C:/Qt/Tools/QtCreator/bin/PlantsvsZombies/Lawn_Mower.png");
            QGraphicsPixmapItem *pic = new QGraphicsPixmapItem(QPixmap::fromImage(mower));
            //pic->setScale(0.4);
            pic->setPos(0,y);
            scene->addItem(pic);
        }

    }
    else if(row==5)
    {
        for(int i =0; i<5; i++)
        {
            for(int j = 0; j<10; j++)
            {
                if(j==0)
                {
                    myBrush = QColor(131, 80, 28);
                }
                else
                {
                   if((i%2==0)&&(j%2==0))
                   {
                    myBrush = QColor(32, 131, 28);
                   }
                   else if((i%2==0)&&(!j%2==0))
                   {
                       myBrush = QColor(20,215,53);
                   }
                   else if((!i%2==0)&&(j%2==0))
                   {
                    myBrush = QColor(20,215,53);
                   }
                   else if((!i%2==0)&&(!j%2==0))
                   {
                       myBrush = QColor(32, 131, 28);
                   }
                }
                double column = j;
                double rows = i;
                scene->addRect(column*63, rows*63, 63, 63, myPen, myBrush);
            }
        }

        for(int i = 0; i<5; i++)
        {
            int y;
            y = i*63;
            QImage mower("C:/Qt/Tools/QtCreator/bin/PlantsvsZombies/Lawn_Mower.png");
            QGraphicsPixmapItem *pic = new QGraphicsPixmapItem(QPixmap::fromImage(mower));
            //pic->setScale(0.4);
            pic->setPos(0,y);
            scene->addItem(pic);
        }
    }

}

void MainWindow::comboBoxSet()
{
    ui->UserChoose->clear();
    for(int i =0; i<players.size(); i++)
    {
        ui->UserChoose->addItem(players.at(i)->getUserName());
    }
}

void MainWindow::setButtons()
{
    ui->PeaShooterButton->setIcon(QIcon("C:/Qt/Tools/QtCreator/bin/PlantsvsZombies/PeaShooter.png"));
    ui->PeaShooterButton->setIconSize(QSize(30,30));
    ui->PeaShooterButton->setEnabled(false);
    ui->PeaShooterButton->setToolTip("PeaShooter..100pts");
    ui->SunFlowerButton->setIcon(QIcon("C:/Qt/Tools/QtCreator/bin/PlantsvsZombies/Sunflower.png"));
    ui->SunFlowerButton->setIconSize(QSize(30,30));
    ui->SunFlowerButton->setEnabled(false);
    ui->SunFlowerButton->setToolTip("Sunflower..50pts");
    ui->CherryBombButton->setIcon(QIcon("C:/Qt/Tools/QtCreator/bin/PlantsvsZombies/CherryBomb.png"));
    ui->CherryBombButton->setIconSize(QSize(30,30));
    ui->CherryBombButton->setEnabled(false);
    ui->CherryBombButton->setToolTip("Cherry Bomb..50pts");
    ui->ChomperButton->setIcon(QIcon("C:/Qt/Tools/QtCreator/bin/PlantsvsZombies/Chomper.png"));
    ui->ChomperButton->setIconSize(QSize(30,30));
    ui->ChomperButton->setEnabled(false);
    ui->ChomperButton->setToolTip("Chomper..150pts");
    ui->PotatoMineButton->setIcon(QIcon("C:/Qt/Tools/QtCreator/bin/PlantsvsZombies/PotatoMine.png"));
    ui->PotatoMineButton->setIconSize(QSize(30,30));
    ui->PotatoMineButton->setEnabled(false);
    ui->PotatoMineButton->setToolTip("Potato Mine..25pts");
    ui->WalNutButton->setIcon(QIcon("C:/Qt/Tools/QtCreator/bin/PlantsvsZombies/WallNut.png"));
    ui->WalNutButton->setIconSize(QSize(30,30));
    ui->WalNutButton->setEnabled(false);
    ui->WalNutButton->setToolTip("WallNut..50pts");
    ui->SnowPeaButton->setIcon(QIcon("C:/Qt/Tools/QtCreator/bin/PlantsvsZombies/SnowPea.png"));
    ui->SnowPeaButton->setIconSize(QSize(30,30));
    ui->SnowPeaButton->setEnabled(false);
    ui->SnowPeaButton->setToolTip("Snowpea..175pts");
    ui->RepeaterButton->setIcon(QIcon("C:/Qt/Tools/QtCreator/bin/PlantsvsZombies/Repeater.png"));
    ui->RepeaterButton->setIconSize(QSize(30,30));
    ui->RepeaterButton->setEnabled(false);
    ui->RepeaterButton->setToolTip("Repeater..200pts");
}

void MainWindow::setSceneInitial()
{
    scene = new QGraphicsScene(this);   // scene holds all objects in the scene
    ui->LawnScreen->setScene(scene);  // graphicsView is the viewport on to the scene

    QPixmap bkgnd("C:/Qt/Tools/QtCreator/bin/PlantsvsZombies/Background.jpg");
        bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
        QPalette palette;
        palette.setBrush(QPalette::Background, bkgnd);
        this->setPalette(palette);

        ui->SunPoints->setNum(sunpoint.sunPoints);
}

bool MainWindow::validNewName(QString name)
{
    QRegExp rx("\\w{0,9}");
        QRegExpValidator validator (rx,0);
     int pos=0;
     if (validator.validate(name,pos)==QValidator::Acceptable|| validator.validate(name,pos)==QValidator::Intermediate)
     {
         qDebug()<<"validation complete";
         return 1;
     }
     else {qDebug()<<"not validated";
         return false;}

}

void MainWindow::levelFunction(int level)
{
    if(level==1)
    {
        rowsOnLevel=1;
        drawMyLawn(rowsOnLevel);

        double time;
        time = 20000;
        for(int i = 1; i < 5; i++)
        {
            QTimer::singleShot(time*i, this, SLOT(createRegZom()));
            time -= 200;
        }
        QTimer::singleShot(75000, this, SLOT(createFlagZom()));

    }
    else if(level==2)
    {
        ui->LevelOnDisplay->setNum(2);
        rowsOnLevel = 3;
        drawMyLawn(rowsOnLevel);

        double time;
        time = 20000;
        for(int i = 1; i < 5; i++)
        {
            QTimer::singleShot(time, this, SLOT(createRegZom()));
            time -= 200;
        }
        QTimer::singleShot(75000, this, SLOT(createFlagZom()));
    }
    else if(level==3)
    {
        rowsOnLevel = 5;
        drawMyLawn(rowsOnLevel);
    }
    else if(level==11)
    {
        ui->AddNewUserButton->setEnabled(true);
        ui->DeleteUserButton->setEnabled(true);
        ui->StartButton->setEnabled(true);
        ui->UserChoose->setEnabled(true);

        daMessageBox.setFixedWidth(441);
        daMessageBox.setFixedHeight(189);
        daMessageBox.setText("YOU BEAT THE ZOMBIES! ");
        daMessageBox.setStandardButtons(QMessageBox::Ok);
        daMessageBox.setDefaultButton(QMessageBox::Ok);
        int choice = daMessageBox.exec();
        switch (choice){

            case QMessageBox::Ok:
            {

                scene->clear();
                currentLevel = 1;
                ui->LevelOnDisplay->setNum(1);

                break;
            }

            default:
                break;

            }
    }


}
bool MainWindow::checkValidity(QString file)
{
    optionalFile = new QFile(file);

        if ( !optionalFile->open(QIODevice::ReadOnly|QIODevice::Text))
            return false;
        else
        {
            optionalFile->close();
            return true;
        }
}

void MainWindow::ReadParseUserFile(QFile fileN)     //used to open up the user file and run it
{
    // all taken from Lab 2 where we parsed and read files
    QString path;
    QTextStream text(&fileN);
    QStringList tempList;

    while(!text.atEnd())
    {
        path = text.readLine();
        tempList = path.split(':');

        userName *user;

        user = new userName;

        user->setTime(tempList.at(0).toDouble());
        user->setUserName(tempList.at(1));
        user->setLevel(tempList.at(2).toInt());

        players.push_back(user);


    }


}

bool MainWindow::validateUserInfo()
{

    for(int i =0; i < ListofNames.size()-1; i++)
    {
        for(int j=0; j < ListofNames.at(i).size(); j++)
        {
            int characterCheck;
            characterCheck = ListofNames.at(i).at(j).unicode();

            if(((characterCheck<'A')||(characterCheck<'a'))&&((characterCheck>'Z')||(characterCheck>'z'))) return 0;
        }
    }
    return 1;
    // we need to add in the 0-100 check.
}

void MainWindow::SetUser(QString file)
{
    //userFile = new QFile(file);
    // delete userFile; ????
}

void MainWindow::ReadParseLevelFile()
{
    // all taken from Lab 2 where we parsed and read files
    QString path;
    QTextStream text(levelFile);
    QStringList tempList;

    while(!text.atEnd())
    {
        path = text.readLine();
        tempList = path.split(':');
        tempList << path;

        /*LevelIdentifier.push_back(tempList[0].toInt());
        ListofSequences << tempList[1];
        ListofRows.push_back(tempList[2].toInt());
        ListofWheretoStart.push_back(tempList[3].toInt());
        IntervalTimeList.push_back(tempList[4].toInt());
        ListofDecrement.push_back(tempList[5].toInt());*/


        /*QString path2;
        QTextStream text2(tempList[1]);
        QStringList tempList2;

        path2 = text2.readLine();
        tempList2 = path2.split(",");
        tempList << path2;

        for(int i = 0; i<tempList.size - 1; i++)
        {
            SequencesParsedSoFar.push_back(tempList[i].toInt());
        }*/


    }
}

bool MainWindow::validateLevelInfo()
{
    /*for (int i =0; i < LevelIdentifier.size(); i++)
    {
        int ID = LevelIdentifier.at(i);
        int asciiTens = '0' + (ID/10)%100;
        int asciiOnes = '0' + ID%10;

        if((ID<=0)||(ID>=100)||(asciiTens<'0')||(asciiTens>'9')||(asciiOnes>'9')||(asciiOnes<'0')) return 0;
    }
    return 1;*/
}

void MainWindow::SetFile(QString file)
{
    levelFile = new QFile(file);
    //delete levelFile;???
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "Position of mouse event:" << event->pos();
    qDebug()<<"sX from start of mousepress:"<<x;
    qDebug()<<"sY from start of mousepress:" << sY;



    if((event->x()>(sX-30)&&event->x()<(sX+30))&&(event->y()>(sY-30)&&event->y()<(sY+30)))
    {
        qDebug () << "hello world"<<pic;
        qDebug () << "sX from in if#1:" << sX;
        qDebug () << "sY from in if#2:" <<  sY;




        //delete *pic;
        //delete sunF;

        scene->removeItem(SunSun);

        sunpoint.sunPointAdd();
        ui->SunPoints->setNum(sunpoint.sunPoints);

        if(sunpoint.sunPoints>=200)
         {

             updateSnowPea();
             updatePeaShooter();
             SunFlower();
             updateWalNut();
             updatePotato();
             updateCherry();
             updateChomp();
             updateRepeat();
         }
         else if(sunpoint.sunPoints<200&&sunpoint.sunPoints>=175)
         {
             updateSnowPea();
             updatePeaShooter();
             SunFlower();
             updateWalNut();
             updatePotato();
             updateCherry();
             updateChomp();
         }
         else if(sunpoint.sunPoints<175&&sunpoint.sunPoints>=150)
         {
             updatePeaShooter();
             SunFlower();
             updateWalNut();
             updatePotato();
             updateCherry();
             updateChomp();
         }
         else if(sunpoint.sunPoints<150&&sunpoint.sunPoints>=100)
         {
             updatePeaShooter();
             SunFlower();
             updateWalNut();
             updatePotato();
         }
         else if(sunpoint.sunPoints<100&&sunpoint.sunPoints>=50)
         {
             SunFlower();
             updateWalNut();
             updatePotato();
         }
         else if(sunpoint.sunPoints<50&&sunpoint.sunPoints>=25)
         {
            updatePotato();
         }
    }
    if((event->x()>(x-190)&&event->x()<(x+210))&&(event->y()>(130)&&event->y()<(150)))

    {
        //delete *pic;
        //delete sunF;

        scene->removeItem(sunF);

        sunpoint.sunPointAdd();
        ui->SunPoints->setNum(sunpoint.sunPoints);

        if(sunpoint.sunPoints>=200)
         {

             updateSnowPea();
             updatePeaShooter();
             SunFlower();
             updateWalNut();
             updatePotato();
             updateCherry();
             updateChomp();
             updateRepeat();
         }
         else if(sunpoint.sunPoints<200&&sunpoint.sunPoints>=175)
         {
             updateSnowPea();
             updatePeaShooter();
             SunFlower();
             updateWalNut();
             updatePotato();
             updateCherry();
             updateChomp();
         }
         else if(sunpoint.sunPoints<175&&sunpoint.sunPoints>=150)
         {
             updatePeaShooter();
             SunFlower();
             updateWalNut();
             updatePotato();
             updateCherry();
             updateChomp();
         }
         else if(sunpoint.sunPoints<150&&sunpoint.sunPoints>=100)
         {
             updatePeaShooter();
             SunFlower();
             updateWalNut();
             updatePotato();
         }
         else if(sunpoint.sunPoints<100&&sunpoint.sunPoints>=50)
         {
             SunFlower();
             updateWalNut();
             updatePotato();
         }
         else if(sunpoint.sunPoints<50&&sunpoint.sunPoints>=25)
         {
            updatePotato();
         }
    }

    if((currentLevel==1) && (((event->x()>164)&&(event->x()<730))&&((event->y()>204)&&(event->y()<267))))
    {
            if(type=='p')
    {
        if(peaCount==0)
        {
            P1bx = event->x()-140;
            P1by = event->y()-125;

        }
        else if(peaCount==1)
        {
            P1bx = event->x()-140;
            P1by = event->y()-125;
        }

        sunpoint.sunPointSubtract(100);
        ui->SunPoints->setNum(sunpoint.sunPoints);

        QImage pea("C:/Qt/Tools/QtCreator/bin/PlantsvsZombies/PeaShooter.png");
        pics = new QGraphicsPixmapItem(QPixmap::fromImage(pea));
        //pic->setScale(0.4);
        pics->setPos(event->x()-140, event->y()-125);
        scene->addItem(pics);
        type = 'v';
        peaCount++;

        int time = 1500;

        for(int i = 1; i < 200; i++)
        {
            QTimer::singleShot((time*i), this, SLOT(drawPea()));
        }




        Plants *point = new Plants(peaShooter);
        plantVector.push_back(point);

        sunPointCheck();


    }
            else if(type=='s')
    {

        sunpoint.sunPointSubtract(50);
        ui->SunPoints->setNum(sunpoint.sunPoints);

        QImage pea("C:/Qt/Tools/QtCreator/bin/PlantsvsZombies/Sunflower.png");
        pic = new QGraphicsPixmapItem(QPixmap::fromImage(pea));
        //pic->setScale(0.4);
        pic->setPos(event->x()-140, event->y()-125);
        scene->addItem(pic);
        type = 'v';

        sX = event->x();
        sY = event->y();
        Plants *point2 = new Plants(sunFlower);
        plantVector.push_back(point2);

        for(int i = 1; i<3; i++)
        {
            int time = 24000*i;
            QTimer::singleShot(time, this, SLOT(createSunFlowerSun()));
            int timed = 31500*i;
            QTimer::singleShot(timed, this, SLOT(deleteSunSun()));
        }
        sunPointCheck();



    }
            else if(type=='c')
    {
        sunpoint.sunPointSubtract(150);
        ui->SunPoints->setNum(sunpoint.sunPoints);

        QImage cherry("C:/Qt/Tools/QtCreator/bin/PlantsvsZombies/CherryBomb.png");
        pic2 = new QGraphicsPixmapItem(QPixmap::fromImage(cherry));
        //pic->setScale(0.4);
        pic2->setPos(event->x()-140, event->y()-100);
        scene->addItem(pic2);
        type = 'v';

        cherryX = event->x();
        cherryY = event->y();

        QTimer::singleShot(1000, this, SLOT(cherryExplode()));

        Plants *point3 = new Plants(cherryBomb);
        plantVector.push_back(point3);
        sunPointCheck();

    }
            else if(type=='w')
    {
        sunpoint.sunPointSubtract(50);
        ui->SunPoints->setNum(sunpoint.sunPoints);

        QImage wall("C:/Qt/Tools/QtCreator/bin/PlantsvsZombies/WallNut.png");
        pic3 = new QGraphicsPixmapItem(QPixmap::fromImage(wall));
        //pic->setScale(0.4);
        pic3->setPos(event->x()-145, event->y()-125);
        scene->addItem(pic3);
        type = 'v';

        Plants *point4 = new Plants(wallNut);
        plantVector.push_back(point4);

        sunPointCheck();

    }
            else if(type=='m')
    {
        sunpoint.sunPointSubtract(25);
        ui->SunPoints->setNum(sunpoint.sunPoints);

        potatoX = event->x()-140;
        potatoY = event->y()-110;

        QImage mine("C:/Qt/Tools/QtCreator/bin/PlantsvsZombies/PotatoMinePreExplode.png");
        pic4 = new QGraphicsPixmapItem(QPixmap::fromImage(mine));
        //pic->setScale(0.4);
        pic4->setPos(event->x()-140, event->y()-110);
        scene->addItem(pic4);
        type = 'v';

        QTimer::singleShot(15000, this, SLOT(spawnBigPotato()));

        Plants *point5 = new Plants(potatoMine);
        plantVector.push_back(point5);

        sunPointCheck();

    }
            else if(type=='n')
    {
        S1bx = event->x()-140;
        S1by = event->y() - 125;

        sunpoint.sunPointSubtract(175);
        ui->SunPoints->setNum(sunpoint.sunPoints);

        QImage snow("C:/Qt/Tools/QtCreator/bin/PlantsvsZombies/SnowPea.png");
        pic5 = new QGraphicsPixmapItem(QPixmap::fromImage(snow));
        //pic->setScale(0.4);
        pic5->setPos(event->x()-140, event->y()-125);
        scene->addItem(pic5);
        type = 'v';

        int time = 1500;

        for(int i = 1; i < 200; i++)
        {
            QTimer::singleShot((time*i), this, SLOT(drawsnowPea()));
        }


        Plants *point6 = new Plants(snowPea);
        plantVector.push_back(point6);

        sunPointCheck();


    }
            else if(type=='h')
    {
        sunpoint.sunPointSubtract(150);
        ui->SunPoints->setNum(sunpoint.sunPoints);

        QImage chomp("C:/Qt/Tools/QtCreator/bin/PlantsvsZombies/Chomper.png");
        pic6 = new QGraphicsPixmapItem(QPixmap::fromImage(chomp));
        //pic->setScale(0.4);
        pic6->setPos(event->x()-140, event->y()-125);
        scene->addItem(pic6);
        type = 'v';

        chompx = event->x()-140;
        chompy = event->y()-125;

        Plants *point7 = new Plants(chomper);
        plantVector.push_back(point7);

        sunPointCheck();

    }
            else if(type=='r')
    {
        if(((event->x()-140)>(P1bx-63)&&(event->x()-140)<(P1bx+63))&&((event->y()-125)>(P1by-63)&&(event->y()-125)<(P1by+63)))
        {
            scene->removeItem(pics);
            sunpoint.sunPointSubtract(200);
            ui->SunPoints->setNum(sunpoint.sunPoints);

            QImage repeat("C:/Qt/Tools/QtCreator/bin/PlantsvsZombies/Repeater.png");
            pic7 = new QGraphicsPixmapItem(QPixmap::fromImage(repeat));
            pic7->setScale(1.3);
            pic7->setPos(event->x()-145, event->y()-125);
            scene->addItem(pic7);
            type = 'v';

            Plants *point8 = new Plants(repeater);
            plantVector.push_back(point8);

            sunPointCheck();
        }

    }
            if(type=='v')
    {
        ui->statusBar->showMessage("Pick a new plant!!");
        sunPointCheck();
    }
    }
    else if((currentLevel==2)&&((event->x()>164)&&(event->x()<730))&&((event->y()>146)&&(event->y()<335)))
    {
            if(type=='p')
    {
        if(peaCount==0)
        {
            P1bx = event->x()-140;
            P1by = event->y()-125;

        }
        else if(peaCount==1)
        {
            P2bx = event->x()-140;
            P2by = event->y()-125;
        }

        sunpoint.sunPointSubtract(100);
        ui->SunPoints->setNum(sunpoint.sunPoints);

        QImage pea("C:/Qt/Tools/QtCreator/bin/PlantsvsZombies/PeaShooter.png");
        pics = new QGraphicsPixmapItem(QPixmap::fromImage(pea));
        //pic->setScale(0.4);
        pics->setPos(event->x()-140, event->y()-125);
        scene->addItem(pics);
        type = 'v';
        peaCount++;

        QTimer::singleShot(1500, this, SLOT(drawPea()));

        Plants *point = new Plants(peaShooter);
        plantVector.push_back(point);

        sunPointCheck();


    }
            else if(type=='s')
    {

        sunpoint.sunPointSubtract(50);
        ui->SunPoints->setNum(sunpoint.sunPoints);

        QImage pea("C:/Qt/Tools/QtCreator/bin/PlantsvsZombies/Sunflower.png");
        pic = new QGraphicsPixmapItem(QPixmap::fromImage(pea));
        //pic->setScale(0.4);
        pic->setPos(event->x()-140, event->y()-125);
        scene->addItem(pic);
        type = 'v';

        sX = event->x();
        sY = event->y();
        Plants *point2 = new Plants(sunFlower);
        plantVector.push_back(point2);

        for(int i = 1; i<3; i++)
        {
            int time = 24000*i;
            QTimer::singleShot(time, this, SLOT(createSunFlowerSun()));
            int timed = 31500*i;
            QTimer::singleShot(timed, this, SLOT(deleteSunSun()));
        }
        sunPointCheck();



    }
            else if(type=='c')
    {
        sunpoint.sunPointSubtract(150);
        ui->SunPoints->setNum(sunpoint.sunPoints);

        QImage cherry("C:/Qt/Tools/QtCreator/bin/PlantsvsZombies/CherryBomb.png");
        pic2 = new QGraphicsPixmapItem(QPixmap::fromImage(cherry));
        //pic->setScale(0.4);
        pic2->setPos(event->x()-140, event->y()-100);
        scene->addItem(pic2);
        type = 'v';

        cherryX = event->x();
        cherryY = event->y();

        scene->removeItem(regz);

        QTimer::singleShot(1000, this, SLOT(cherryExplode()));

        Plants *point3 = new Plants(cherryBomb);
        plantVector.push_back(point3);
        sunPointCheck();

    }
            else if(type=='w')
    {
        sunpoint.sunPointSubtract(50);
        ui->SunPoints->setNum(sunpoint.sunPoints);

        QImage wall("C:/Qt/Tools/QtCreator/bin/PlantsvsZombies/WallNut.png");
        pic3 = new QGraphicsPixmapItem(QPixmap::fromImage(wall));
        //pic->setScale(0.4);
        pic3->setPos(event->x()-145, event->y()-125);
        scene->addItem(pic3);
        type = 'v';

        Plants *point4 = new Plants(wallNut);
        plantVector.push_back(point4);

        sunPointCheck();

    }
            else if(type=='m')
    {
        sunpoint.sunPointSubtract(25);
        ui->SunPoints->setNum(sunpoint.sunPoints);

        potatoX = event->x()-140;
        potatoY = event->y()-110;

        QImage mine("C:/Qt/Tools/QtCreator/bin/PlantsvsZombies/PotatoMinePreExplode.png");
        pic4 = new QGraphicsPixmapItem(QPixmap::fromImage(mine));
        //pic->setScale(0.4);
        pic4->setPos(event->x()-140, event->y()-110);
        scene->addItem(pic4);
        type = 'v';

        QTimer::singleShot(15000, this, SLOT(spawnBigPotato()));

        Plants *point5 = new Plants(potatoMine);
        plantVector.push_back(point5);

        sunPointCheck();

    }
            else if(type=='n')
    {

        sunpoint.sunPointSubtract(175);
        ui->SunPoints->setNum(sunpoint.sunPoints);

        QImage snow("C:/Qt/Tools/QtCreator/bin/PlantsvsZombies/SnowPea.png");
        pic5 = new QGraphicsPixmapItem(QPixmap::fromImage(snow));
        //pic->setScale(0.4);
        pic5->setPos(event->x()-140, event->y()-125);
        scene->addItem(pic5);
        type = 'v';

        Plants *point6 = new Plants(snowPea);
        plantVector.push_back(point6);

        sunPointCheck();


    }
            else if(type=='h')
    {
        sunpoint.sunPointSubtract(150);
        ui->SunPoints->setNum(sunpoint.sunPoints);

        QImage chomp("C:/Qt/Tools/QtCreator/bin/PlantsvsZombies/Chomper.png");
        pic6 = new QGraphicsPixmapItem(QPixmap::fromImage(chomp));
        //pic->setScale(0.4);
        pic6->setPos(event->x()-140, event->y()-125);
        scene->addItem(pic6);
        type = 'v';

        Plants *point7 = new Plants(chomper);
        plantVector.push_back(point7);

        sunPointCheck();

    }
            else if(type=='r')
    {
        if(((event->x()-140)>(P1bx-63)&&(event->x()-140)<(P1bx+63))&&((event->y()-125)>(P1by-63)&&(event->y()-125)<(P1by+63)))
        {
            scene->removeItem(pics);
            sunpoint.sunPointSubtract(200);
            ui->SunPoints->setNum(sunpoint.sunPoints);

            QImage repeat("C:/Qt/Tools/QtCreator/bin/PlantsvsZombies/Repeater.png");
            pic7 = new QGraphicsPixmapItem(QPixmap::fromImage(repeat));
            pic7->setScale(1.3);
            pic7->setPos(event->x()-145, event->y()-125);
            scene->addItem(pic7);
            type = 'v';

            Plants *point8 = new Plants(repeater);
            plantVector.push_back(point8);

            sunPointCheck();
        }

    }
            if(type=='v')
    {
        ui->statusBar->showMessage("Pick a new plant!!");
        sunPointCheck();
    }
    }

}

void MainWindow::sunPointCheck()
{
   if(sunpoint.sunPoints>=200)
    {

        /*updateSnowPea();
        updatePeaShooter();
        SunFlower();
        updateWalNut();
        updatePotato();
        updateCherry();
        updateChomp();
        updateRepeat();*/
    }
    else if(sunpoint.sunPoints<200&&sunpoint.sunPoints>=175)
    {
        ui->RepeaterButton->setEnabled(false);

        /*updateSnowPea();
        updatePeaShooter();
        SunFlower();
        updateWalNut();
        updatePotato();
        updateCherry();
        updateChomp();*/
    }
    else if(sunpoint.sunPoints<175&&sunpoint.sunPoints>=150)
    {
        ui->RepeaterButton->setEnabled(false);
        ui->SnowPeaButton->setEnabled(false);
        /*updatePeaShooter();
        SunFlower();
        updateWalNut();
        updatePotato();
        updateCherry();
        updateChomp();*/
    }
    else if(sunpoint.sunPoints<150&&sunpoint.sunPoints>=100)
    {
        ui->RepeaterButton->setEnabled(false);
        ui->SnowPeaButton->setEnabled(false);
        ui->CherryBombButton->setEnabled(false);
        ui->ChomperButton->setEnabled(false);
        /*updatePeaShooter();
        SunFlower();
        updateWalNut();
        updatePotato();*/
    }
    else if(sunpoint.sunPoints<100&&sunpoint.sunPoints>=50)
    {
        ui->RepeaterButton->setEnabled(false);
        ui->SnowPeaButton->setEnabled(false);
        ui->CherryBombButton->setEnabled(false);
        ui->ChomperButton->setEnabled(false);
        ui->PeaShooterButton->setEnabled(false);
        /*SunFlower();
        updateWalNut();
        updatePotato();*/
    }
    else if(sunpoint.sunPoints<50&&sunpoint.sunPoints>=25)
    {
        ui->RepeaterButton->setEnabled(false);
        ui->SnowPeaButton->setEnabled(false);
        ui->CherryBombButton->setEnabled(false);
        ui->ChomperButton->setEnabled(false);
        ui->PeaShooterButton->setEnabled(false);
        ui->SunFlowerButton->setEnabled(false);
        ui->WalNutButton->setEnabled(false);
        /*updatePotato();*/
    }
    else if(sunpoint.sunPoints<25)
    {
        ui->RepeaterButton->setEnabled(false);
        ui->SnowPeaButton->setEnabled(false);
        ui->CherryBombButton->setEnabled(false);
        ui->ChomperButton->setEnabled(false);
        ui->PeaShooterButton->setEnabled(false);
        ui->SunFlowerButton->setEnabled(false);
        ui->WalNutButton->setEnabled(false);
        ui->PotatoMineButton->setEnabled(false);
    }

    progressBar1 = this->findChild<QProgressBar*>("progressBar");
    progressBar1->setValue(0);
}

void MainWindow::moveBullet()
{
    //set to move the bullet from its location
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updatePeaShooter()
{
    ui->PeaShooterButton->setEnabled(true);
}

void MainWindow::updateSnowPea()
{
    ui->SnowPeaButton->setEnabled(true);
    spA = 1;
}

void MainWindow::SunFlower()
{
    ui->SunFlowerButton->setEnabled(true);
    snA = 1;
}

void MainWindow::updateWalNut()
{
    ui->WalNutButton->setEnabled(true);
    wA = 1;
}

void MainWindow::updatePotato()
{
    ui->PotatoMineButton->setEnabled(true);
    pmA = 1;
}

void MainWindow::updateCherry()
{
    ui->CherryBombButton->setEnabled(true);
    cbA = 1;
}

void MainWindow::updateChomp()
{
    ui->ChomperButton->setEnabled(true);
    cA = 1;
}

void MainWindow::updateRepeat()
{
    ui->RepeaterButton->setEnabled(true);
    rA = 1;
}

void MainWindow::on_QuitButon_clicked()
{
    timer->stop();

    ui->AddNewUserButton->setEnabled(true);
    ui->DeleteUserButton->setEnabled(true);
    ui->StartButton->setEnabled(true);
    ui->UserChoose->setEnabled(true);

    daMessageBox.setText("Are you sure you want to quit this level?");
    daMessageBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    daMessageBox.setDefaultButton(QMessageBox::No);
    int choice = daMessageBox.exec();
    switch (choice){

        case QMessageBox::Yes:
        {
            daMessageBox.setText("Would you like to save your progress?");
            daMessageBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            daMessageBox.setDefaultButton(QMessageBox::Yes);
            int choice2 = daMessageBox.exec();
            switch (choice2){
            case QMessageBox::No:
                scene->clear();
            case QMessageBox::Yes:
                scene->clear();
            }

            scene->clear();

            break;
        }
        case QMessageBox::No:
            break;
        default:
            break;

        }



}

void MainWindow::on_RestartLevelButton_clicked()
{

    daMessageBox.setText("Do you really want to restart this level?!");
    daMessageBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    daMessageBox.setDefaultButton(QMessageBox::No);
    int choice = daMessageBox.exec();
    switch (choice){

        case QMessageBox::Yes:
        {
            drawMyLawn(currentLevel);
            sunpoint.sunPoints = 1000;
            ui->SunPoints->setNum(sunpoint.sunPoints);
            ui->CherryBombButton->setEnabled(true);
            ui->ChomperButton->setEnabled(true);
            ui->PeaShooterButton->setEnabled(true);
            ui->PotatoMineButton->setEnabled(true);
            ui->RepeaterButton->setEnabled(true);
            ui->SnowPeaButton->setEnabled(true);
            ui->SunFlowerButton->setEnabled(true);
            ui->WalNutButton->setEnabled(true);
            peaVector.clear();
            zombieVector.clear();
            snowVector.clear();
            P1bx = 0;
            P1by = 0;

            break;
        }
        case QMessageBox::No:
            break;
        default:
            break;

    }
}

void MainWindow::movedaSun()
{


}

void MainWindow::createSunFlowerSun()
{
        QImage Sun("C:/Qt/Tools/QtCreator/bin/PlantsvsZombies/SunFA");
        SunSun = new QGraphicsPixmapItem(QPixmap::fromImage(Sun));
        SunSun->setScale(0.8);
        SunSun->setPos(sX-135, sY-125);
        scene->addItem(SunSun);

}

void MainWindow::on_UserChoose_currentIndexChanged(const QString &arg1)
{


}

void MainWindow::on_StartButton_clicked()
{


    timer->start(20);


    ui->AddNewUserButton->setEnabled(false);
    ui->DeleteUserButton->setEnabled(false);
    ui->StartButton->setEnabled(false);
    ui->UserChoose->setEnabled(false);

    for(int i =1; i<11; i++)
    {
        int time = 10000*i;
        int timed = 17500*i;
        QTimer::singleShot(time, this, SLOT(drawSun()));

        QTimer::singleShot(timed, this, SLOT(deleteFallSun()));
    }


    levelFunction(currentLevel);


}

void MainWindow::moveSun(double time, double y, double velocity)
{

    ycoSun = y - (velocity*time*100);

}
void MainWindow::drawSun()
{
    x = (qrand()%600);

    QImage SUN("C:/Qt/Tools/QtCreator/bin/PlantsvsZombies/SunFA.png");
    sunF = new QGraphicsPixmapItem(QPixmap::fromImage(SUN));
    sunF->setScale(0.8);
    sunF->setPos(x,0);
    scene->addItem(sunF);

    suntimer = new QTimer;

    connect(suntimer,SIGNAL(timeout()),this, SLOT(movedaSun()));
    suntimer->start(15);
}

void MainWindow::deleteFallSun()
{
    scene->removeItem(sunF);
}

void MainWindow::deleteSunSun()
{
    scene->removeItem(SunSun);
}

void MainWindow::cherryExplode()
{
    scene->removeItem(pic2);
    QImage cherrybomb("C:/Qt/Tools/QtCreator/bin/PlantsvsZombies/CherryExplode.png");
    pic2 = new QGraphicsPixmapItem(QPixmap::fromImage(cherrybomb));
    //pic->setScale(0.4);
    pic2->setPos(cherryX-230, cherryY-175);
    scene->addItem(pic2);

    if ((((zombieVector[0].getXCo())<(cherryX+300))&&((zombieVector[0].getXCo())>(cherryX-300)))&&((regy<(cherryY+300))&&(regy>(cherryY-300))))
    {

        QTimer::singleShot(2000, this, SLOT(cherryDelete()));
        QTimer::singleShot(1000, this, SLOT(deleteRegZ()));
    }
    if ((((zombieVector[1].getXCo())<(cherryX+300))&&((zombieVector[1].getXCo())>(cherryX-300)))&&((regy<(cherryY+300))&&(regy>(cherryY-300))))
    {

        QTimer::singleShot(2000, this, SLOT(cherryDelete()));
        QTimer::singleShot(1000, this, SLOT(deleteRegZ()));
    }
    //scene->removeItem(pic2);

}

void MainWindow::cherryDelete()
{
    scene->removeItem(pic2);
}

void MainWindow::createRegZom()
{
    Zombie *zombPointer = new Zombie();
    zombPointer->setXCo(570);
    zombPointer->setYCo(110);
    QImage zombie("C:/Qt/Tools/QtCreator/bin/PlantsvsZombies/RegularZombie.png");
    QGraphicsPixmapItem *regZPicture = new QGraphicsPixmapItem;
    regZPicture->setPixmap(QPixmap::fromImage(zombie));
    //regZPicture->setScale(0.075);
    regZPicture->setPos(zombPointer->getXCo(), zombPointer->getYCo());
    scene->addItem(regZPicture);
    zombieVector.push_back(*zombPointer);
    zombieRegPic.push_back(regZPicture);


    regx = 570;
    regy = 110;

    qDebug() << regz ;

}

void MainWindow::createFlagZom()
{
    QImage flagZomb("C:/Qt/Tools/QtCreator/bin/PlantsvsZombies/FlagZombie.png");
    flagz = new QGraphicsPixmapItem(QPixmap::fromImage(flagZomb));
    //pic->setScale(0.4);
    flagz->setPos(570, 120);
    scene->addItem(flagz);
}

void MainWindow::drawPea()
{
    if((!P1bx==0)&&(!P1by==0))
    {
    Peas *peaPointer = new Peas();
    peaPointer->setXCo(P1bx);
    peaPointer->setYCo(P1by);
    QImage bullet("C:/Qt/Tools/QtCreator/bin/PlantsvsZombies/bullet.png");
    QGraphicsPixmapItem *peaPicture = new QGraphicsPixmapItem;
    peaPicture->setPixmap(QPixmap::fromImage(bullet));
    peaPicture->setScale(0.075);
    peaPicture->setPos(peaPointer->getXCo()+75, peaPointer->getYCo()+10);
    scene->addItem(peaPicture);
    peaVector.push_back(*peaPointer);
    peaPictures.push_back(peaPicture);
    }
}

void MainWindow::drawsnowPea()
{
    snowBullet *snowPeaPointer = new snowBullet();
    snowPeaPointer->setXCo(S1bx);
    snowPeaPointer->setYCo(S1by);
    QImage bullet("C:/Qt/Tools/QtCreator/bin/PlantsvsZombies/snowPeaBullet.png");
    QGraphicsPixmapItem *snowPeaPicture = new QGraphicsPixmapItem;
    snowPeaPicture->setPixmap(QPixmap::fromImage(bullet));
    snowPeaPicture->setScale(0.075);
    snowPeaPicture->setPos(snowPeaPointer->getXCo()+75, snowPeaPointer->getYCo()+10);
    scene->addItem(snowPeaPicture);
    snowVector.push_back(*snowPeaPointer);
    snowPeaPictures.push_back(snowPeaPicture);

    for(int i =0; i < zombieVector.size(); i++)
    {
    zombieVector[i].setSpeed(2.5);
    }

}

void MainWindow::spawnBigPotato()
{
    scene->removeItem(pic4);
    QImage mineafter("C:/Qt/Tools/QtCreator/bin/PlantsvsZombies/PotatoMine.png");
    pic4 = new QGraphicsPixmapItem(QPixmap::fromImage(mineafter));
    //pic->setScale(0.4);
    pic4->setPos(potatoX, potatoY);
    scene->addItem(pic4);

    if (((zombieVector[0].getXCo())<(potatoX+150))&&((zombieVector[0].getXCo())>(potatoX-150)))
    {
        scene->removeItem(pic4);
        QImage mineafter("C:/Qt/Tools/QtCreator/bin/PlantsvsZombies/spudow.png");
        pic4 = new QGraphicsPixmapItem(QPixmap::fromImage(mineafter));
        //pic->setScale(0.4);
        pic4->setPos(potatoX-20, potatoY-50);
        scene->addItem(pic4);
        QTimer::singleShot(2000, this, SLOT(deletePotato()));
        QTimer::singleShot(100, this, SLOT(deleteRegZ()));
    }
    if (((zombieVector[1].getXCo())<(potatoX+150))&&((zombieVector[1].getXCo())>(potatoX-150)))
    {
        scene->removeItem(pic4);
        QImage mineafter("C:/Qt/Tools/QtCreator/bin/PlantsvsZombies/spudow.png");
        pic4 = new QGraphicsPixmapItem(QPixmap::fromImage(mineafter));
        //pic->setScale(0.4);
        pic4->setPos(potatoX-20, potatoY-50);
        scene->addItem(pic4);
        QTimer::singleShot(2000, this, SLOT(deletePotato()));
        QTimer::singleShot(100, this, SLOT(deleteRegZ()));
    }

}

void MainWindow::deleteRegZ()
{

    scene->removeItem(zombieRegPic[0]);
}

void MainWindow::deletePotato()
{
    scene->removeItem(pic4);
}

void MainWindow::bulletMove()
{
    for(int i = 0; i < peaVector.size();i++)
        {
            peaVector[i].setXCo(peaVector[i].getXCo() - peaVector[i].getSpeed());
            //zombiePicVector[i]->setPos(rand()% 500, rand()% 300);
            peaPictures[i]->setPos((peaPictures[i]->x() + peaVector[i].getSpeed()), peaPictures[i]->y());
    }
}

void MainWindow::snowBulletMove()
{
    for(int i = 0; i < snowVector.size();i++)
        {
            snowVector[i].setXCo(snowVector[i].getXCo() - snowVector[i].getSpeed());
            //zombiePicVector[i]->setPos(rand()% 500, rand()% 300);
            snowPeaPictures[i]->setPos((snowPeaPictures[i]->x() + snowVector[i].getSpeed()), snowPeaPictures[i]->y());
    }
}

void MainWindow::zombMove()
{
    for(int i = 0; i < zombieVector.size();i++)
    {
            zombieVector[i].setXCo(zombieVector[i].getXCo() - zombieVector[i].getSpeed());
            //zombiePicVector[i]->setPos(rand()% 500, rand()% 300);
            zombieRegPic[i]->setPos((zombieRegPic[i]->x() - zombieVector[i].getSpeed()), zombieRegPic[i]->y());
            if(zombieVector[i].getXCo()==0)
            {
                if(pA==1)
                {
                    scene->removeItem(zombieRegPic[0]);
                    scene->removeItem(regz4);

                }
                else if(pA==2)
                {
                daMessageBox.setText("Zombies ate your brains!!! DUH.");
                daMessageBox.setStandardButtons(QMessageBox::Ok);
                daMessageBox.setDefaultButton(QMessageBox::Ok);
                int choice = daMessageBox.exec();
                switch (choice){

                    case QMessageBox::Ok:
                    {
                        drawMyLawn(currentLevel);
                        bulletMove();

                        break;
                    }
                    default:
                        break;
                }
                }
                pA++;
            }
    }
}

void MainWindow::chomperCheck()
{
    for(int i = 0; i < zombieVector.size();i++)
    {
       if(((zombieVector[i].getXCo()>chompx-75)&&((zombieVector[i].getXCo()<chompx+75)))&&((zombieVector[i].getYCo()>chompy-75)&&(zombieVector[i].getYCo()<chompy+75)))
       {
           scene->removeItem(zombieRegPic[i]);
           scene->removeItem(pic6);
       }
    }
}

void MainWindow::on_PeaShooterButton_clicked()
{
    if(sunpoint.sunPoints >= 100)
    {
        updatePeaShooter();

        type = 'p';


        ui->PeaShooterButton->setEnabled(false);

        //Plants *point = new Plants;
        Plants *point = new Plants(peaShooter);
        plantVector.push_back(point);

        QTimer::singleShot(7500, this, SLOT(updatePeaShooter()));
        /*while(!QTimer==7500)
        {
            ui->peashooterProgressBar->setValue((QTimer/7500)*100);
        }*/
        //How do I check the time it is on?


    }
    sunPointCheck();

}

void MainWindow::on_SunFlowerButton_clicked()
{
    if(sunpoint.sunPoints >= 50)
    {

        type = 's';

        ui->SunFlowerButton->setEnabled(false);

        snA = 0;

        QTimer::singleShot(7500, this, SLOT(SunFlower()));

    }
    sunPointCheck();

}

void MainWindow::on_CherryBombButton_clicked()
{
    if(sunpoint.sunPoints >= 150)
    {

        type = 'c';

        ui->CherryBombButton->setEnabled(false);

        cbA = 0;

        QTimer::singleShot(50000, this, SLOT(updateCherry()));
    }
    sunPointCheck();

}

void MainWindow::on_WalNutButton_clicked()
{
    if(sunpoint.sunPoints >= 50)
    {

        type = 'w';

        ui->WalNutButton->setEnabled(false);

        wA = 0;

        QTimer::singleShot(3000, this, SLOT(updateWalNut()));


    }
    sunPointCheck();

}

void MainWindow::on_PotatoMineButton_clicked()
{
    if(sunpoint.sunPoints >= 25)
    {

        type = 'm';

        ui->PotatoMineButton->setEnabled(false);

        pmA = 0;

        QTimer::singleShot(30000, this, SLOT(updatePotato()));

    }
    sunPointCheck();

}

void MainWindow::on_SnowPeaButton_clicked()
{
    if(sunpoint.sunPoints >= 175)
    {

        type = 'n';

        ui->SnowPeaButton->setEnabled(false);

        spA = 0;

        QTimer::singleShot(7500, this, SLOT(updateSnowPea()));


    }
    sunPointCheck();
}

void MainWindow::on_ChomperButton_clicked()
{
    if(sunpoint.sunPoints >= 150)
    {

        type = 'h';

        ui->ChomperButton->setEnabled(false);

        cA = 0;

        QTimer::singleShot(7500, this, SLOT(updateChomp()));


    }
    sunPointCheck();

}

void MainWindow::on_RepeaterButton_clicked()
{
    if(sunpoint.sunPoints >= 200)
    {

        type = 'r';

        ui->RepeaterButton->setEnabled(false);

        rA = 0;

        QTimer::singleShot(7500, this, SLOT(updateRepeat()));


    }
    sunPointCheck();

}

void MainWindow::click(int x, int y, Plants *daPlant)
{

}

void MainWindow::on_AddNewUserButton_clicked()
{
    currentLevel=1;
    rowsOnLevel = 1;

    checkName = (ui->lineEdit->text());

    if(validNewName(checkName)==false)
    {
        daMessageBox.setText("I'm sorry that isnt a valid username....");
        daMessageBox.setStandardButtons(QMessageBox::Ok);
        daMessageBox.setDefaultButton(QMessageBox::Ok);
        int choice = daMessageBox.exec();
        switch (choice){

            case QMessageBox::Ok:
            {
                ui->lineEdit->setText("");


                break;
            }
            default:
                break;

        }
    }
    else
    {

        daMessageBox.setText("Are you sure you wish to add this new user?");
        daMessageBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
        daMessageBox.setDefaultButton(QMessageBox::Cancel);
        int choice = daMessageBox.exec();
        switch (choice){

            case QMessageBox::Yes:
            {
                ui->UserChoose->setEnabled(true);
                ui->UserChoose->setItemText(1, checkName);
                ui->StartButton->setEnabled(true);
                ui->RestartLevelButton->setEnabled(true);
                ui->QuitButon->setEnabled(true);
                ui->LevelOnDisplay->setNum(currentLevel);

                break;
            }
            case QMessageBox::Cancel:
            {
                ui->lineEdit->setText("");
                break;
            }
            default:
                break;

            }

    }





    qDebug() << checkName;

}
