#ifndef TRIBUTETHREAD_H
#define TRIBUTETHREAD_H

#include <QObject>
#include<player.h>
#include<QThread>
class TributeThread:public QThread
{
    Q_OBJECT
public:
    explicit TributeThread(Player* player);
protected:
    virtual void run();

private:
    Player* onplayer;
};

#endif // TRIBUTETHREAD_H
