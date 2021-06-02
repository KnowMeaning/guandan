#ifndef HAND_H
#define HAND_H

#include<cards.h>
#include <QVector>
class Hand
{
public:
    Hand();
    Hand(CardsType type,CardPoint base,int extra);
    Hand(Cards cards);
    void Analysis(Cards cards);
    void Judge();
    QVector<CardPoint> getvector(int a);
    QVector<Card> getgoust();
    CardsType getcardstype();
    int getbasevalve();
    BombValve getbombvalve();
    int getextra();
    bool if_beat(Hand other);
    bool operator ==(const Hand& hand);
private:
    QVector<CardPoint> Bomb;
    QVector<CardPoint> ThreeCard;
    QVector<CardPoint> TwoCard;
    QVector<CardPoint> OneCard;
    QVector<Card> Goust;
    CardsType cardstype;
    int BaseValve;
    int main_card;
    int anyknumber;
    BombValve bombvalve;
    int Extra_Card;
    int cardnumber;
    bool ifSameSuit;


};

#endif // HAND_H
