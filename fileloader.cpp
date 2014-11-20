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

}
