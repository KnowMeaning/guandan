#ifndef HANDTHREAD_H
#define HANDTHREAD_H
#include <QThread>
#include<player.h>

class HandThread: public QThread
{
    Q_OBJECT
public:
    explicit HandThread(Player* player);

protected:
    virtual void run();

private:
    Player* onplayer;
};

#endif // HANDTHREAD_H
