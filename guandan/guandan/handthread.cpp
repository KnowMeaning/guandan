#include "handthread.h"

HandThread::HandThread(Player *player)
{
    onplayer=player;
}

void HandThread::run()
{
    msleep(600);
    onplayer->ThinkForPlayHand();
}
