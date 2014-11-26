#ifndef USERNAME_H
#define USERNAME_H
#include <QString>
#include <QDateTime>

class userName
{
public:
    userName();
    userName(QString name);

    void setUserName(QString name);
    void setLevel(int currentLev);
    void setTime(double time);

    QString getUserName();
    int getLevel();
    double getTime();

private:
    QString usersName;
    int level;
    double currentScore;
    double timeStamp;

};


#endif // USERNAME_H
