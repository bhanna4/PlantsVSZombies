#ifndef FILELOADER_H
#define FILELOADER_H

#include <iostream>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QStringList>
#include <vector>
#include "username.h"
#include <QDateTime>

// need to have one set of functions to handle the user and one set to handle the level.

using namespace std;

class fileloader
{
public:
    fileloader();

    //functions used on all files
    bool checkValidity(QString file); //to check and see if the file is valid

    //all user functions
    void ReadParseUserFile();
    bool validateUserInfo();
    //void MakeUserVector(vector <userName>);
    void SetUser(QString file);
    //void CreateNewUser(QString username, vector <userName*> &username);

    //all level functions
    void ReadParseLevelFile();
    bool validateLevelInfo();
    void SetFile(QString file);



private:

    QFile *optionalFile; //used in check validity function
    QFile *levelFile; //used in setting the level
    QFile *userFile; // used in setting our user

    vector <userName> players;
    vector <int> timeStampList;   // used to hold the info of the time stamp on the user info
    vector <int> levelOnList;     // used to hold the info of the level the user is on

    vector <int> LevelIdentifier;  // used to distinguish the levels
    vector <int> ListofRows;       // used to tell how many rows are on that level
    vector <int> ListofWheretoStart;  //
    vector <int> IntervalTimeList;  // used to tell the interval of time between zombie approaches on that level
    vector <int> SequencesParsedSoFar; //

    vector <double> ListofDecrement; // decrements on that level????

    QStringList ListofNames;
    QStringList ListofSequences;


};

#endif // FILELOADER_H
