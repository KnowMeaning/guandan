#ifndef ROBOT_H
#define ROBOT_H

#include <QObject>
#include<player.h>

class robot : public Player
{
public:
    robot(QObject* parent = nullptr);
    void ThinkForPlayHand();
    void ThinkForTribute();
    void SearchStraight();
};

#endif // ROBOT_H
