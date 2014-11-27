#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <QMouseEvent>


// PLEASE NOTE FOR 3G MY TOOL TIP APPEARS IN THE STATUS BAR!! THANK YOUUUU

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Pcount = 0;

    setButtons();

    setSceneInitial();


     timer = new QTimer(this); //timer function is needed for the start and stop functionality
     connect(timer, SIGNAL(timeout()), this, SLOT(moveSun()));
     timer->start(20);

    connect(ui->LawnScreen,SIGNAL(click(int,int,Plants*)),this,SLOT(click(int,int,Plants*)));


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
        QGraphicsPixmapItem *pic = new QGraphicsPixmapItem(QPixmap::fromImage(mower));
        //pic->setScale(0.4);
        pic->setPos(0,126);
        scene->addItem(pic);

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

    drawSun(0);

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
    qDebug() << event->pos();

    if(event->x()==x&&event->y()==0)
    {
        //delete *pic;
        //delete sunF;
        //scene->removeItem();
    }
    if(type=='p')
    {
        if(Pcount==0)
        {
            P1bx = event->x()-140;
            P1by = event->y()-125;
        }
        else if(Pcount==1)
        {
            P2bx = event->x()-140;
            P2by = event->y()-125;
        }
        QImage pea("C:/Qt/Tools/QtCreator/bin/PlantsvsZombies/PeaShooter.png");
        QGraphicsPixmapItem *pic = new QGraphicsPixmapItem(QPixmap::fromImage(pea));
        //pic->setScale(0.4);
        pic->setPos(event->x()-140, event->y()-125);
        scene->addItem(pic);
        type = 'v';

        Plants *point = new Plants(peaShooter);
        plantVector.push_back(point);


    }
    else if(type=='s')
    {
        QImage pea("C:/Qt/Tools/QtCreator/bin/PlantsvsZombies/Sunflower.png");
        QGraphicsPixmapItem *pic = new QGraphicsPixmapItem(QPixmap::fromImage(pea));
        //pic->setScale(0.4);
        pic->setPos(event->x()-140, event->y()-125);
        scene->addItem(pic);
        type = 'v';

        sX = event->x()-130;
        sY = event->y()-115;
        Plants *point2 = new Plants(sunFlower);
        plantVector.push_back(point2);

        QTimer::singleShot(24000, this, SLOT(createSunFlowerSun()));

    }
    else if(type=='c')
    {
        QImage pea("C:/Qt/Tools/QtCreator/bin/PlantsvsZombies/CherryBomb.png");
        QGraphicsPixmapItem *pic = new QGraphicsPixmapItem(QPixmap::fromImage(pea));
        //pic->setScale(0.4);
        pic->setPos(event->x()-140, event->y()-100);
        scene->addItem(pic);
        type = 'v';

        Plants *point3 = new Plants(cherryBomb);
        plantVector.push_back(point3);

    }
    else if(type=='w')
    {
        QImage pea("C:/Qt/Tools/QtCreator/bin/PlantsvsZombies/WallNut.png");
        QGraphicsPixmapItem *pic = new QGraphicsPixmapItem(QPixmap::fromImage(pea));
        //pic->setScale(0.4);
        pic->setPos(event->x()-145, event->y()-125);
        scene->addItem(pic);
        type = 'v';

        Plants *point4 = new Plants(wallNut);
        plantVector.push_back(point4);

    }
    else if(type=='m')
    {
        QImage pea("C:/Qt/Tools/QtCreator/bin/PlantsvsZombies/PotatoMine.png");
        QGraphicsPixmapItem *pic = new QGraphicsPixmapItem(QPixmap::fromImage(pea));
        //pic->setScale(0.4);
        pic->setPos(event->x()-140, event->y()-110);
        scene->addItem(pic);
        type = 'v';

        Plants *point5 = new Plants(potatoMine);
        plantVector.push_back(point5);

    }
    else if(type=='n')
    {
        QImage pea("C:/Qt/Tools/QtCreator/bin/PlantsvsZombies/SnowPea.png");
        QGraphicsPixmapItem *pic = new QGraphicsPixmapItem(QPixmap::fromImage(pea));
        //pic->setScale(0.4);
        pic->setPos(event->x()-140, event->y()-125);
        scene->addItem(pic);
        type = 'v';

        Plants *point6 = new Plants(snowPea);
        plantVector.push_back(point6);

    }
    else if(type=='h')
    {
        QImage pea("C:/Qt/Tools/QtCreator/bin/PlantsvsZombies/Chomper.png");
        QGraphicsPixmapItem *pic = new QGraphicsPixmapItem(QPixmap::fromImage(pea));
        //pic->setScale(0.4);
        pic->setPos(event->x()-140, event->y()-125);
        scene->addItem(pic);
        type = 'v';

        Plants *point7 = new Plants(chomper);
        plantVector.push_back(point7);

    }
    else if(type=='r')
    {
        QImage pea("C:/Qt/Tools/QtCreator/bin/PlantsvsZombies/Repeater.png");
        QGraphicsPixmapItem *pic = new QGraphicsPixmapItem(QPixmap::fromImage(pea));
        //pic->setScale(0.4);
        pic->setPos(event->x()-140, event->y()-125);
        scene->addItem(pic);
        type = 'v';

        Plants *point8 = new Plants(repeater);
        plantVector.push_back(point8);

    }


    if(type=='v')
    {
        ui->statusBar->showMessage("Pick a new plant!!");
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
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updatePeaShooter()
{
    ui->PeaShooterButton->setEnabled(true);
    pA = 1;
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
            drawMyLawn(3);
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
        QImage pea("C:/Qt/Tools/QtCreator/bin/PlantsvsZombies/SunFA");
        QGraphicsPixmapItem *pic = new QGraphicsPixmapItem(QPixmap::fromImage(pea));
        pic->setScale(0.8);
        pic->setPos(sX, sY);
        scene->addItem(pic);

}

void MainWindow::on_UserChoose_currentIndexChanged(const QString &arg1)
{


}

void MainWindow::on_StartButton_clicked()
{

    updateSnowPea();
    updatePeaShooter();
    SunFlower();
    updateWalNut();
    updatePotato();
    updateCherry();
    updateChomp();
    updateRepeat();

    timer->start(20);
    drawMyLawn(rowsOnLevel);

    ui->AddNewUserButton->setEnabled(false);
    ui->DeleteUserButton->setEnabled(false);
    ui->StartButton->setEnabled(false);
    ui->UserChoose->setEnabled(false);


}

void MainWindow::moveSun(double time, double y, double velocity)
{

    ycoSun = y - (velocity*time*100);

}
void MainWindow::drawSun(double y)
{
    x = (qrand()%600);

    QImage sunF("C:/Qt/Tools/QtCreator/bin/PlantsvsZombies/SunFA.png");
    QGraphicsPixmapItem *pic = new QGraphicsPixmapItem(QPixmap::fromImage(sunF));
    pic->setScale(0.8);
    pic->setPos(x,0);
    scene->addItem(pic);

    suntimer = new QTimer;

    connect(suntimer,SIGNAL(timeout()),this, SLOT(movedaSun()));
    suntimer->start(15);
}

void MainWindow::on_PeaShooterButton_clicked()
{
    if(sunpoint.sunPoints >= 100)
    {
        updatePeaShooter();
        sunpoint.sunPointSubtract(100);
        ui->SunPoints->setNum(sunpoint.sunPoints);

        type = 'p';


        ui->PeaShooterButton->setEnabled(false);
        pA = 0;

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
        sunpoint.sunPointSubtract(50);
        ui->SunPoints->setNum(sunpoint.sunPoints);

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
        sunpoint.sunPointSubtract(150);
        ui->SunPoints->setNum(sunpoint.sunPoints);

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
        sunpoint.sunPointSubtract(50);
        ui->SunPoints->setNum(sunpoint.sunPoints);

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
        sunpoint.sunPointSubtract(25);
        ui->SunPoints->setNum(sunpoint.sunPoints);

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
        sunpoint.sunPointSubtract(175);
        ui->SunPoints->setNum(sunpoint.sunPoints);

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
        sunpoint.sunPointSubtract(150);
        ui->SunPoints->setNum(sunpoint.sunPoints);

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
        sunpoint.sunPointSubtract(200);
        ui->SunPoints->setNum(sunpoint.sunPoints);

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
    ui->StartButton->setEnabled(true);
    ui->RestartLevelButton->setEnabled(true);
    ui->QuitButon->setEnabled(true);

}
