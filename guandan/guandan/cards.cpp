#include "cards.h"
#include<QTime>
Cards::Cards()
{

}

bool Cards::operator ==(const Cards &right)
{
    if(main_cards==right.main_cards)return 1;
    else return 0;
}
void Cards::Clear()
{
    main_cards.clear();
}
//清空手牌

bool Cards::IsEmpty() const
{
    return main_cards.isEmpty();
}
//返回是否打完手牌
void Cards::Add(const Cards& cards)
{
    main_cards=main_cards.unite(cards.main_cards);
}
//初始化容器
void Cards::Add(const Card& card)
{
    main_cards.insert(card);
}
//继续添加单张卡牌
void Cards::Add(const QVector<Cards>& cardsArray)
{
    for (int i=0;i<cardsArray.size();i++)
    {
        Add(cardsArray[i]);
    }
}
//用容器添加卡牌
Cards& Cards::operator <<(const Cards& cards)
{
    Add(cards);
    return *this;
}
//重载<<为添加卡牌
Cards& Cards::operator <<(const Card& card)
{
    Add(card);
    return *this;
}
//重载<<为添加卡牌
Cards& Cards::operator <<(const QVector<Cards>& cardsArray)
{
    Add(cardsArray);
    return *this;
}
//重载<<为添加卡牌
void Cards::Remove(const Cards& cards)
{
    main_cards.subtract(cards.main_cards);
}
//移除卡牌
void Cards::Remove(const Card& card)
{
    main_cards.remove(card);
}
//移除单张卡牌
void Cards::Remove(const QVector<Cards>& cardsArray)
{
    for(int i=0;i<cardsArray.size();i++)
    {
        Remove(cardsArray[i]);
    }
}

bool Cards::Contains(const Cards& cards) const
{
    return main_cards.contains(cards.main_cards);
}
//判断是否包含
bool Cards::Contains(const Card& card) const
{
    return main_cards.contains(card);
}

Card Cards::TakeRandomCard()
{
    QTime time;
    time=QTime::currentTime();
    qsrand(time.msec()+time.second()*1000);
//设置随机数种子
    int randomIndex=qrand()%main_cards.size();
    QSet<Card>::iterator it=main_cards.begin()+randomIndex;
    Card takeCard=*it;
    main_cards.erase(it);

    return takeCard;
}
//随机取出一张卡
int Cards::Count()
{
    return main_cards.size();
}
//判断有多少牌
int Cards::PointCount(CardPoint point)
{
    int count=0;
    for(QSet<Card>::ConstIterator it=main_cards.constBegin();it!=main_cards.constEnd();it++)
    {
        if(it->cardpoint==point)
        {
            count++;
        }
    }

    return count;
}
//判断同一点数卡数量
CardPoint Cards::MinPoint()
{
    Card min;
    if(main_cards.isEmpty())return Card_End;

    QSet<Card>::ConstIterator it=main_cards.constBegin();
    min.valve=it->valve;
    min.cardpoint=it->cardpoint;
    for(;it!=main_cards.constEnd();it++)
    {
        if(it->valve<min.valve)
        {
            min.valve=it->valve;
            min.cardpoint=it->cardpoint;
        }
    }

    return min.cardpoint;
}
//寻找最低点数
CardPoint Cards::MaxPoint()
{
    Card max;
    if(main_cards.isEmpty())return Card_Start;

    QSet<Card>::ConstIterator it=main_cards.constBegin();
    max.valve=it->valve;
    max.cardpoint=it->cardpoint;
    for(;it!=main_cards.constEnd();it++)
    {
        if(it->valve>max.cardpoint)
        {
            max.valve=it->valve;
            max.cardpoint=it->cardpoint;
        }
    }

    return max.cardpoint;
}
//寻找最大点数
QVector<Card> Cards::ToCardList(SortType sortType) const
{
    QVector<Card> cardList;
    for(QSet<Card>::const_iterator it=main_cards.constBegin();it!=main_cards.constEnd();it++)
    {
        cardList<<*it;
    }

    if(sortType==Asc)
    {
        qSort(cardList.begin(),cardList.end(),qLess<Card>());
    }
    else if(sortType==Desc)
    {
        qSort(cardList.begin(),cardList.end(),qGreater<Card>());
    }

    return cardList;
}
//排序。
