#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QMainWindow>
#include <QMessageBox>
#include "sunshine.h"
#include "lawn.h"
#include <QTime>
#include <QFile>
#include <vector>
#include "username.h"
#include <QTextStream>
#include "zombie.h"
#include <QTimer>
#include <QProgressBar>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QMessageBox daMessageBox;
    void drawMyLawn(int row);
    void comboBoxSet();
    void setButtons();
    void setSceneInitial();
    Sunshine sun;
    Lawn lawn;
    void createSun();

    QGraphicsPixmapItem *pic, *sunF;
    QGraphicsPixmapItem *SunSun;

    char type;

    int currentLevel;
    int rowsOnLevel;


    //functions used on all files
    bool checkValidity(QString file); //to check and see if the file is valid

    //all user functions
    void ReadParseUserFile(QFile fileN);
    bool validateUserInfo();
    //void MakeUserVector(vector <userName>);
    void SetUser(QString file);
    //void CreateNewUser(QString username, vector <userName*> &username);

    //all level functions
    void ReadParseLevelFile();
    bool validateLevelInfo();
    void SetFile(QString file);




    double ycoSun;

    void mousePressEvent(QMouseEvent *event);

    void sunPointCheck();

    int pA, snA, wA, pmA, cbA, cA, spA, rA;

    double sX, sY;
    int dSX, dSY;

    int x;

    int P1bx, P1by, P2bx, P2by, P3bx, P3by, P4bx, P4by, Pcount;


    ~MainWindow();
public slots:
    void updatePeaShooter();
    void updateSnowPea();
    void SunFlower();
    void updateWalNut();
    void updatePotato();
    void updateCherry();
    void updateChomp();
    void updateRepeat();
    void drawSun();
    void deleteFallSun();
    void deleteSunSun();


private slots:
    void on_QuitButon_clicked();
    void moveSun(double time, double y, double velocity);
    void on_RestartLevelButton_clicked();

    void movedaSun();

    void createSunFlowerSun();

    void on_UserChoose_currentIndexChanged(const QString &arg1);

    void on_StartButton_clicked();

    void on_PeaShooterButton_clicked();

    void on_SunFlowerButton_clicked();

    void on_CherryBombButton_clicked();

    void on_WalNutButton_clicked();

    void on_PotatoMineButton_clicked();

    void on_SnowPeaButton_clicked();

    void on_ChomperButton_clicked();

    void on_RepeaterButton_clicked();

    void click(int x, int y, Plants *daPlant);

    void on_AddNewUserButton_clicked();

private:
    Ui::MainWindow *ui;
    Sunshine sunpoint;
    QGraphicsScene *scene;

    QTimer *suntimer;

    QTimer *timer;

    QFile *optionalFile; //used in check validity function
    QFile *levelFile; //used in setting the level
    QFile *userFile; // used in setting our user

    vector <userName*> players;

    vector <Plants*> plantVector;

    vector <Zombie*> zombieVector;

    /*vector <int> timeStampList;   // used to hold the info of the time stamp on the user info
    vector <int> levelOnList;     // used to hold the info of the level the user is on

    vector <int> LevelIdentifier;  // used to distinguish the levels
    vector <int> ListofRows;       // used to tell how many rows are on that level
    vector <int> ListofWheretoStart;  //
    vector <int> IntervalTimeList;  // used to tell the interval of time between zombie approaches on that level
    vector <int> SequencesParsedSoFar; //

    vector <double> ListofDecrement; // decrements on that level????*/

    QStringList ListofNames;
    QStringList ListofSequences;
    QProgressBar *progressBar1;
};

#endif // MAINWINDOW_H
