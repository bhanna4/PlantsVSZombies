#include "fileloader.h"
#include <iostream>


fileloader::fileloader()
{
}

bool fileloader::checkValidity(QString file)
{
    optionalFile = new QFile(file);

        if ( !optionalFile->open(QIODevice::ReadOnly|QIODevice::Text))
            return false;
        else
            return true;
}

void fileloader::ReadParseUserFile()     //used to open up the user file and run it
{
    // all taken from Lab 2 where we parsed and read files
    QString path;
    QTextStream text(userFile);
    QStringList tempList;

    while(!text.atEnd())
    {
        path = text.readLine();
        tempList = path.split(':');    //Brandon, always :??
        tempList << path;

        timeStampList.push_back(tempList[0].toInt());  //this is done since the time stamp of the game is the first thing in the csv file
        ListofNames << tempList[1];                   // sets the QStringList for the names to the second spot of the file
        levelOnList.push_back(tempList[1].toInt()); // makes sure the level they are on is set to an integer
    }


}

bool fileloader::validateUserInfo()
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

void fileloader::SetUser(QString file)
{
    userFile = new QFile(file);
    // delete userFile; ????
}

void fileloader::ReadParseLevelFile()
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

        LevelIdentifier.push_back(tempList[0].toInt());
        ListofSequences << tempList[1];
        ListofRows.push_back(tempList[2].toInt());
        ListofWheretoStart.push_back(tempList[3].toInt());
        IntervalTimeList.push_back(tempList[4].toInt());
        ListofDecrement.push_back(tempList[5].toInt());


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

bool fileloader::validateLevelInfo()
{
    for (int i =0; i < LevelIdentifier.size(); i++)
    {
        int ID = LevelIdentifier.at(i);
        int asciiTens = '0' + (ID/10)%100;
        int asciiOnes = '0' + ID%10;

        if((ID<=0)||(ID>=100)||(asciiTens<'0')||(asciiTens>'9')||(asciiOnes>'9')||(asciiOnes<'0')) return 0;
    }
    return 1;
}

void fileloader::SetFile(QString file)
{
    levelFile = new QFile(file);
    //delete levelFile;???
}
