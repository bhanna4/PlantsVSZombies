#include "username.h"


userName::userName()
{
    usersName="";
    level = 1;
    timeStamp = QDateTime::currentDateTime().toTime_t();
}

userName::userName(QString name)
{
    usersName = name;
    level = 0;
    timeStamp= QDateTime::currentDateTime().toTime_t();
}

void userName::setUserName(QString name)
{
    usersName = name;
}

void userName::setLevel(int currentLev)
{
    level = currentLev;
}

void userName::setTime(double time)
{
    timeStamp = time;
}

QString userName::getUserName()
{
    return usersName;
}

int userName::getLevel()
{
    return level;
}

double userName::getTime()
{
    return timeStamp;
}

