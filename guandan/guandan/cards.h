#ifndef CARDS_H
#define CARDS_H

#include <QVector>
#include <QSet>
#include <QMap>
#include <QList>
enum CardPoint{//卡牌点数
    Card_Start=-1,
    Card_3=1,
    Card_4,
    Card_5,
    Card_6,
    Card_7,
    Card_8,
    Card_9,
    Card_10,
    Card_J,
    Card_Q,
    Card_K,
    Card_A=12,
    Card_2=0,
    Card_SG=13,
    Card_BG=14,

    Card_End
};
enum CardSuit{//卡牌花色
    Suit_Start,

    Diamond,	// 方块
    Club,		// 梅花
    Heart,		// 红桃
    Spade,		// 黑桃


    Suit_End
};
enum if_maincard{
    not_main=0,
    maincard=1,
};

struct Card{
    CardPoint cardpoint;
    CardSuit cardsuit;
    if_maincard maincard;
    uint deck;
    int valve;

};
inline bool operator ==(const Card& left, const Card& right)
{
    return (left.cardpoint==right.cardpoint && left.cardsuit==right.cardsuit&&left.deck==right.deck&&left.maincard==right.maincard&&left.valve==right.valve);
}
//重载运算符==（花色和点数都相等）
inline bool operator <(const Card& left, const Card& right)
{

    if (left.valve==right.valve&&left.cardpoint == right.cardpoint && left.cardsuit == right.cardsuit)
    {
        return left.deck < right.deck;
    }
    else if(left.valve==right.valve&&left.cardpoint == right.cardpoint)
    {
        return left.cardsuit < right.cardsuit;
    }
    else if(left.valve==right.valve)
    {
        return left.cardpoint < right.cardpoint;
    }
    else{
        return left.valve<right.valve;
    }
}
//重载运算符<（先比点数，后比花色）
inline uint qHash(const Card& card)
{
    return card.cardpoint*1000+card.valve * 100 + card.cardsuit*10+card.deck;
}

//重载使容器可以自动排序
enum CardsType{
    Type_tart,
    //common为非炸弹的牌
    Type_Pass,//没出牌
    Type_common_Single,//单牌
    Type_common_Double,//对子
    Type_common_Third,//三张
    Type_common_TfollowD,//三带二
    Type_common_TStraight,//钢板（三顺）
    Type_common_Straight,//顺子（五张）
    Type_Bomb,//包括同花顺、四鬼的炸弹牌

    Type_end
};
enum BombValve{
    Bomb_start=2,
    Bomb_No,
    Bomb_Four,
    Bomb_Five,
    Bomb_StraightFlush,//同花顺
    Bomb_Six,
    Bomb_Seven,
    Bomb_Eight,
    Bomb_FourGhost//四鬼

};

class Cards
{
public:
    Cards();
    enum SortType
    {
        NoSort,
        Asc,//逆序
        Desc//顺序
    };
    bool operator ==(const Cards& right);
    void Add(const Cards& cards);//初始化容器
    void Add(const Card& card);//继续添加单张卡牌
    void Add(const QVector<Cards>& cardsArray);//用容器添加卡牌

    void Remove(const Cards& cards);
    void Remove(const Card& card);
    void Remove(const QVector<Cards>& cardsArray);
//移除卡牌

    bool Contains(const Cards& cards) const;
    bool Contains(const Card& card) const;
//判断是否包含

    Cards& operator <<(const Cards& cards);
    Cards& operator <<(const Card& card);
    Cards& operator <<(const QVector<Cards>& cardsArray);
//三者重载<<为添加卡牌
    QVector<Card> ToCardList(SortType sortType=Asc) const;//排序（逆）。

    int Count();//判断有多少牌
    int PointCount(CardPoint point);//判断同一点数卡数量
    CardPoint MinPoint();//寻找最低点数
    CardPoint MaxPoint();//寻找最大点数

    Card TakeRandomCard();
//随机取出一张卡

    bool IsEmpty() const;
    //返回是否打完手牌
    void Clear();
    //清空手牌
private:
    QSet<Card> main_cards;
};

#endif // CARDS_H
