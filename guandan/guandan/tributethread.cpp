#include "tributethread.h"

TributeThread::TributeThread(Player *player)
{
    onplayer=player;
}

void TributeThread::run()
{
    msleep(600);
    onplayer->ThinkForTribute();
}



