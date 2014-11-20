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
    QPen my_pen = QPen(Qt::red);
    QBrush my_brush = QBrush(Qt::blue);
    scene->addRect(0,0,100,100, my_pen, my_brush);


    QString MyFiles = "C:\Qt\Tools\QtCreator\bin\PlantsvsZombies";
    QString UsersFiles = ":/pvz_players.csv";

    if(!(loader.checkValidity(UsersFiles)))
    {
        ui->statusBar->showMessage("Unable to load player data.");
    }
    else
    {
        ui->statusBar->showMessage("Player Loaded.");
        loader.SetUser(UsersFiles);
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
