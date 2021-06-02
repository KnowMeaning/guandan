#ifndef USER_H
#define USER_H

#include <QObject>
#include<player.h>
class User : public Player
{
public:
    User(QObject* parent = nullptr);
    void SearchStraight();
};

#endif // USER_H
