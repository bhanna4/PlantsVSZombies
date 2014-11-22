#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);   // scene holds all objects in the scene
    ui->LawnScreen->setScene(scene);  // graphicsView is the viewport on to the scene


    QString MyFiles = "C:/Qt/Tools/QtCreator/bin/PlantsvsZombies";
    QString UsersFiles = "C:/Qt/Tools/QtCreator/bin/PlantsvsZombies/pvz_players.csv";

    if(!(loader.checkValidity(UsersFiles)))
    {
        ui->statusBar->showMessage("Unable to load player data.");
    }
    else
    {
        ui->statusBar->showMessage("Player Loaded.");
        loader.SetUser(UsersFiles);
    }

    loader.ReadParseUserFile();


    QString LevelFiles = "C:/Qt/Tools/QtCreator/bin/PlantsvsZombies/pvz_levels.csv";

    if(!(loader.checkValidity(LevelFiles)))
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
        ui->statusBar->showMessage("Levels Loaded.");
        loader.SetFile(LevelFiles);
    }





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
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_QuitButon_clicked()
{
    QMessageBox::question(this, "Quit?","Are you sure you want to quit this level", QMessageBox::Yes|QMessageBox::Cancel);
}

void MainWindow::on_RestartLevelButton_clicked()
{
    QMessageBox::question(this, "Restart Level?","Are you sure you want to restart this level", QMessageBox::Yes|QMessageBox::Cancel);
}

void MainWindow::on_UserChoose_currentIndexChanged(const QString &arg1)
{


}

void MainWindow::on_StartButton_clicked()
{
        drawMyLawn(5);
}
