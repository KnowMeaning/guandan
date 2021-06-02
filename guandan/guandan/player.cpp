#include "player.h"
#include<handthread.h>
#include<tributethread.h>
#include<QDebug>
Player::Player(QObject *parent) : QObject(parent)
{
    type=Unknow;
    punchPlayer=nullptr;
    StraightCards.clear();
}

void Player::SetPrevPlayer(Player *player)
{
    prevPlayer=player;
}

Player *Player::GetPrevPlayer()
{
    return prevPlayer;
}

void Player::SetNextPlayer(Player *player)
{
    nextPlayer=player;
}

Player *Player::GetNextPlayer()
{
    return nextPlayer;
}

void Player::SetName(QString Name)
{
    name=Name;
}

QString Player::GetName()
{
    return name;
}
void Player::SetType(Type s_type)
{
    type=s_type;
}
Type Player::GetType()
{
    return type;
}

QVector<Cards> Player::getstringhcards()
{
    return StraightCards;
}

QVector<Cards> Player::getTStrightcards()
{
    return TStraightCards;
}

void Player::addstringcards(const Cards &cards)
{
    Hand hand(cards);
    if(!oucards.Contains(cards))return ;
    if(hand.getcardstype()==Type_common_Straight||hand.getbombvalve()==Bomb_StraightFlush){
        oucards.Remove(cards);
        StraightCards.push_back(cards);
    }
    else if(hand.getcardstype()==Type_common_TStraight){
        oucards.Remove(cards);
        TStraightCards.push_back(cards);
    }
}

void Player::outstringcards(const Cards &cards)
{
    Hand hand(cards);
    if(hand.getcardstype()==Type_common_Straight||hand.getbombvalve()==Bomb_StraightFlush){
        for(int i=0;i<StraightCards.count();i++){
            if(StraightCards[i]==cards){
                StraightCards.remove(i);
                oucards.Add(cards);
                break;
            }
        }
    }
    else if(hand.getcardstype()==Type_common_TStraight){
        for(int i=0;i<TStraightCards.count();i++){
            if(TStraightCards[i]==cards){
                TStraightCards.remove(i);
                oucards.Add(cards);
                break;
            }
        }
    }
}

void Player::clearcard()
{
    oucards.Clear();
    StraightCards.clear();
    TStraightCards.clear();
}

void Player::PickCards(const Cards &cards)
{
    oucards.Add(cards);
    emit Send_PickCards(this,cards);
}

void Player::PickCard(const Card &card)
{
    Cards cards;
    cards.Add(card);
    PickCards(cards);

}

Cards Player::getcard()
{
    return oucards;

}

void Player::HandCard(const Cards &cards)
{
    outstringcards(cards);
    if(oucards.Contains(cards)){
    oucards.Remove(cards);}
    emit Send_PlayHand(this,cards);
}

void Player::RemoveCard(const Card &card)
{
    oucards.Remove(card);
}

void Player::TributeCard(const Cards &cards)
{
    oucards.Remove(cards);
    emit Send_TributeHand(this,cards,tributePlayer);
}

void Player::TributeCard(const Card card)
{
    Cards cards;
    cards.Clear();
    cards.Add(card);
    TributeCard(cards);
}



void Player::StartForPlayHand( Player *player, const Cards &cards)
{
    HandThread* thread=new HandThread(this);
    punchCards=cards;
    punchPlayer=player;
    thread->start();
}


void Player::ThinkForPlayHand()
{

}

void Player::StartForTribute(Player *player)
{
    tributePlayer=player;
    TributeThread* thread=new TributeThread(this);
    thread->start();

}

void Player::ThinkForTribute()
{

}

void Player::SearchStraight()
{

}

void Player::setfriend(Player *player)
{
    friendplayer=player;
}

Player *Player::getfriend()
{
    return friendplayer;
}

int Player::getcardssize()
{
    return oucards.Count()+StraightCards.size()*5+TStraightCards.size()*6;
}




