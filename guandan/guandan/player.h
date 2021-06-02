#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include<cards.h>
#include<hand.h>
enum Type
{
    Unknow,
    PUser,
    antirobot,
    friendrobot
};
class Player : public QObject
{
    Q_OBJECT
public:
    explicit Player(QObject *parent = nullptr);
    void SetPrevPlayer(Player* player);
    Player* GetPrevPlayer();
    void SetNextPlayer(Player* player);
    Player* GetNextPlayer();
    void SetName(QString Name);
    QString GetName();
    void SetType(Type s_type);
    Type GetType();
    QVector<Cards> getstringhcards();
    QVector<Cards> getTStrightcards();
    void addstringcards(const Cards& cards);
    void outstringcards(const Cards& cards);
    void clearcard();
    void PickCards(const Cards& cards);//加入手牌，发送信号Send_pickcards
    void PickCard(const Card& card);//同上
    Cards getcard();
    void HandCard(const Cards& cards);
    void RemoveCard(const Card& card);
    void TributeCard(const Cards& cards);
    void TributeCard(const Card card);
    virtual void StartForPlayHand( Player* player,const Cards& cards);
    virtual void ThinkForPlayHand();
    virtual void StartForTribute( Player* player);
    virtual void ThinkForTribute();
    virtual void SearchStraight();
    void setfriend(Player* player);
    Player* getfriend();
    int getcardssize();
signals:
    void Send_PlayHand(Player*, const Cards&);
    void Send_PickCards(Player*, const Cards&);
    void Send_EndHand();
    void Send_TributeHand(Player*,const Cards&,Player*);
public slots:
protected:
    QVector<Cards> StraightCards;
    QVector<Cards> TStraightCards;
    Player* tributePlayer;
    Player* punchPlayer;
    Cards punchCards;
    Player* friendplayer;
    Player* nextPlayer;
    Player* prevPlayer;
    QString name;//名字
    Cards oucards;
    Type type;
};

#endif // PLAYER_H
