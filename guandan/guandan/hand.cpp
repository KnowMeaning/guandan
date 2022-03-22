#include "hand.h"
#include<qdebug.h>
Hand::Hand()
{

}

Hand::Hand(CardsType type, CardPoint base, int extra)
{
    cardstype=type;
    BaseValve=base*10;
    Extra_Card=extra;
}

Hand::Hand(Cards cards)
{
    Analysis(cards);
    Judge();

}

void Hand::Analysis(Cards cards)
{

    QVector<Card> cardList=cards.ToCardList();//逆序取出卡牌
    int* cardrecord=new int[Card_End];
    memset(cardrecord,0,sizeof(int)*Card_End);
    cardnumber=0;
    ifSameSuit=0;
    main_card=0;
    anyknumber=0;
    QVector<Card>::const_iterator it=cardList.constBegin();
    for(;it!=cardList.constEnd();it++){
        int i=it->cardpoint;
        if(it->maincard==1){
            main_card=it->cardpoint+1;
            if(it->cardsuit==Heart){
                anyknumber++;
                cardnumber++;
                continue;
            }
        }
        if(it->cardpoint==Card_BG||it->cardpoint==Card_SG){
            Card card;
            card.deck=it->deck;
            card.valve=it->valve;
            card.cardsuit=it->cardsuit;
            card.maincard=it->maincard;
            card.cardpoint=it->cardpoint;
            Goust.push_back(card);
        }
        cardrecord[i]++;
        cardnumber++;
    }
    OneCard.clear();
    TwoCard.clear();
    ThreeCard.clear();
    Bomb.clear();
    for(int i=0;i<13;i++){
        if(cardrecord[i]==1)
        {
            OneCard.push_back((CardPoint)i);
        }
        else if(cardrecord[i]==2)
        {
            TwoCard.push_back((CardPoint)i);
        }
        else if(cardrecord[i]==3)
        {
            ThreeCard.push_back((CardPoint)i);
        }
        else if(cardrecord[i]>=4)
        {
            Bomb.push_back((CardPoint)i);
        }
    }

        if(OneCard.size()==5-anyknumber&&TwoCard.size()==0&&ThreeCard.size()==0&&Bomb.size()==0){
            ifSameSuit=1;
            QVector<Card>::const_iterator it=cardList.constBegin();
            CardSuit k=it->cardsuit;
            for(;it!=cardList.constEnd();it++){
                if(it->cardsuit==Heart&&it->maincard==1)continue;
                if(k!=it->cardsuit)ifSameSuit=0;
            }
        }

}

void Hand::Judge()
{
    cardstype=Type_tart;
    BaseValve=0;
    Extra_Card=0;
    bombvalve=Bomb_No;
    if(anyknumber==0){
        if(OneCard.size()==0&&TwoCard.size()==0&&ThreeCard.size()==0&&Bomb.size()==0){
            if(Goust.size()==4){
                cardstype=Type_Bomb;
                bombvalve=Bomb_FourGhost;
            }
            else if(Goust.size()==1){
                cardstype=Type_common_Single;
                BaseValve=Goust[0].valve;
            }
            else if(Goust.size()>1){

            }
            else cardstype=Type_Pass;
        }
        if(OneCard.size()==1&&TwoCard.size()==0&&ThreeCard.size()==0&&Bomb.size()==0&&Goust.size()==0){
            cardstype=Type_common_Single;
            if(OneCard[0]==main_card-1)BaseValve=125;
            else BaseValve=OneCard[0]*10;
        }
        if(OneCard.size()==0&&TwoCard.size()==1&&ThreeCard.size()==0&&Bomb.size()==0&&Goust.size()==0){
            if(TwoCard[0]==Card_BG||TwoCard[0]==Card_SG){
                return;
            }
            else{cardstype=Type_common_Double;
                if(TwoCard[0]==main_card-1)BaseValve=125;
                else BaseValve=TwoCard[0]*10;
                }
        }
        if(OneCard.size()==0&&TwoCard.size()==0&&ThreeCard.size()==1&&Bomb.size()==0&&Goust.size()==0){
            cardstype=Type_common_Third;
            if(ThreeCard[0]==main_card-1)BaseValve=125;
            else BaseValve=ThreeCard[0]*10;
        }
        if(OneCard.size()==0&&TwoCard.size()==1&&ThreeCard.size()==1&&Bomb.size()==0&&Goust.size()==0){
            cardstype=Type_common_TfollowD;
            if(ThreeCard[0]==main_card-1)BaseValve=125;
            else BaseValve=ThreeCard[0]*10;
            Extra_Card=2;
        }
        if(OneCard.size()==5&&TwoCard.size()==0&&ThreeCard.size()==0&&Bomb.size()==0&&Goust.size()==0){
            for(int a=0;a<5;a++){
                int k=a;
                for(int b=a+1;b<5;b++){
                    if(OneCard[k]<OneCard[b])k=b;
                }
                CardPoint t;
                t=OneCard[a];
                OneCard[a]=OneCard[k];
                OneCard[k]=t;
        }
        if(OneCard[0]==(OneCard[1]+1)&&OneCard[1]==(OneCard[2]+1)&&OneCard[2]==(OneCard[3]+1)&&OneCard[3]==(OneCard[4]+1)&&OneCard[0]<Card_SG){
            if(ifSameSuit==0){
                BaseValve=OneCard[0]*10;
                cardstype=Type_common_Straight;
            }
            else{
                BaseValve=OneCard[0]*10;
                cardstype=Type_Bomb;
                bombvalve=Bomb_StraightFlush;
            }
        }
        else if(OneCard[0]==Card_A&&OneCard[1]==Card_5&&OneCard[2]==Card_4&&OneCard[3]==Card_3&&OneCard[4]==Card_2){
            if(ifSameSuit==0){
                BaseValve=OneCard[1]*10;
                cardstype=Type_common_Straight;
            }
            else{
                BaseValve=OneCard[1]*10;
                cardstype=Type_Bomb;
                bombvalve=Bomb_StraightFlush;
            }
            }}
        if(OneCard.size()==0&&TwoCard.size()==3&&ThreeCard.size()==0&&Bomb.size()==0&&Goust.size()==0){
            for(int a=0;a<3;a++){
                int k=a;
                for(int b=a+1;b<3;b++){
                    if(TwoCard[k]<TwoCard[b])k=b;
                }
                CardPoint t;
                t=TwoCard[a];
                TwoCard[a]=TwoCard[k];
                TwoCard[k]=t;
        }
        if(TwoCard[0]==(TwoCard[1]+1)&&TwoCard[1]==(TwoCard[2]+1)&&TwoCard[0]<Card_SG){
            BaseValve=TwoCard[0]*10;
            cardstype=Type_common_TStraight;
           }
        else if(TwoCard[0]==Card_A&&TwoCard[1]==Card_3&&TwoCard[2]==Card_2){
            BaseValve=TwoCard[1]*10;
            cardstype=Type_common_TStraight;
        }
        }
        if(OneCard.size()==0&&TwoCard.size()==0&&ThreeCard.size()==0&&Bomb.size()==1&&Goust.size()==0){
            if(Bomb[0]==main_card-1)BaseValve=125;
            else BaseValve=Bomb[0]*10;
            cardstype=Type_Bomb;
            if(cardnumber>=6){
                cardnumber++;
            }
            bombvalve=(BombValve)cardnumber;
            }
        }
    else if(anyknumber==1){
        if(OneCard.size()==0&&TwoCard.size()==0&&ThreeCard.size()==0&&Bomb.size()==0&&Goust.size()==0){//单张
            cardstype=Type_common_Single;
            BaseValve=125;
        }
        if(OneCard.size()==1&&TwoCard.size()==0&&ThreeCard.size()==0&&Bomb.size()==0&&Goust.size()==0){//对子
            cardstype=Type_common_Double;
            if(OneCard[0]==main_card-1)BaseValve=125;
            else BaseValve=OneCard[0]*10;
        }
        if(OneCard.size()==0&&TwoCard.size()==1&&ThreeCard.size()==0&&Bomb.size()==0&&Goust.size()==0){//三张
            cardstype=Type_common_Third;
            if(TwoCard[0]==main_card-1)BaseValve=125;
            else BaseValve=TwoCard[0]*10;
        }
        if(OneCard.size()==0&&TwoCard.size()==0&&ThreeCard.size()==1&&Bomb.size()==0&&Goust.size()==0){//炸弹
            cardstype=Type_Bomb;
            bombvalve=(BombValve)4;
            if(ThreeCard[0]==main_card-1)BaseValve=125;
            else BaseValve=ThreeCard[0]*10;
        }
        if(OneCard.size()==0&&TwoCard.size()==0&&ThreeCard.size()==0&&Bomb.size()==1&&Goust.size()==0){//炸弹
            cardstype=Type_Bomb;
            if(Bomb[0]==main_card-1)BaseValve=125;
            else BaseValve=Bomb[0]*10;
            if(cardnumber>=6){
                cardnumber++;
            }
            bombvalve=(BombValve)cardnumber;
        }
        if(OneCard.size()==4&&TwoCard.size()==0&&ThreeCard.size()==0&&Bomb.size()==0&&Goust.size()==0){//顺子
            int x=2;
            for(int a=0;a<4;a++){
                int k=a;
                for(int b=a+1;b<4;b++){
                    if(OneCard[k]<OneCard[b])k=b;
                }
                CardPoint t;
                t=OneCard[a];
                OneCard[a]=OneCard[k];
                OneCard[k]=t;
                if(a>0){
                    if(OneCard[a-1]-OneCard[a]==2){
                        x--;
                    }
                    else if(OneCard[a-1]-OneCard[a]>2||OneCard[a-1]-OneCard[a]<1){
                        x=0;
                    }
                }
            }
            if(x==2){
                if(ifSameSuit==0){
                    BaseValve=OneCard[0]*10+10;
                    cardstype=Type_common_Straight;
                }
                else{
                    BaseValve=OneCard[0]*10+10;
                    cardstype=Type_Bomb;
                    bombvalve=Bomb_StraightFlush;
                }
            }
            else if(x==1){
                if(ifSameSuit==0){
                    BaseValve=OneCard[0]*10;
                    cardstype=Type_common_Straight;
                }
                else{
                    BaseValve=OneCard[0]*10;
                    cardstype=Type_Bomb;
                    bombvalve=Bomb_StraightFlush;
                }
            }
            else if(OneCard[0]==Card_A&&OneCard[1]==Card_4&&OneCard[2]==Card_3&&OneCard[3]==Card_2){
                if(ifSameSuit==0){
                    BaseValve=Card_5*10;
                    cardstype=Type_common_Straight;
                }
                else{
                    BaseValve=Card_5*10;
                    cardstype=Type_Bomb;
                    bombvalve=Bomb_StraightFlush;
                }
            }
        }
        if(OneCard.size()==1&&TwoCard.size()==0&&ThreeCard.size()==1&&Bomb.size()==0&&Goust.size()==0){//三带二1
            cardstype=Type_common_TfollowD;
            if(ThreeCard[0]==main_card-1)BaseValve=125;
            else BaseValve=ThreeCard[0]*10;
        }
        if(OneCard.size()==0&&TwoCard.size()==2&&ThreeCard.size()==0&&Bomb.size()==0&&Goust.size()==0){//三带二2
            cardstype=Type_common_TfollowD;
            if(TwoCard[1]==main_card-1||TwoCard[0]==main_card-1)BaseValve=125;
            else BaseValve=TwoCard[1]*10;
        }
        if(OneCard.size()==1&&TwoCard.size()==2&&ThreeCard.size()==0&&Bomb.size()==0&&Goust.size()==0){//三连对
            CardPoint k[3];
            k[0]=OneCard[0];
            k[1]=TwoCard[0];
            k[2]=TwoCard[1];
            for(int a=0;a<3;a++){
                int x=a;
                for(int b=a+1;b<3;b++){
                    if(k[x]<k[b])x=b;
                }
                CardPoint t;
                t=k[a];
                k[a]=k[x];
                k[x]=t;
            }
            if(k[0]==(k[1]+1)&&k[1]==(k[2]+1)&&k[0]<Card_SG){
                BaseValve=k[0]*10;
                cardstype=Type_common_TStraight;
               }
            else if(k[0]==Card_A&&k[1]==Card_3&&k[2]==Card_2){
                BaseValve=k[1]*10;
                cardstype=Type_common_TStraight;
        }
    }
    }
    else if(anyknumber==2){
        if(OneCard.size()==0&&TwoCard.size()==0&&ThreeCard.size()==0&&Bomb.size()==0&&Goust.size()==0){//对子
            cardstype=Type_common_Double;
            BaseValve=125;
        }
        if(OneCard.size()==1&&TwoCard.size()==0&&ThreeCard.size()==0&&Bomb.size()==0&&Goust.size()==0){//三张
            cardstype=Type_common_Third;
            if(OneCard[0]==main_card-1)BaseValve=125;
            else BaseValve=OneCard[0]*10;
        }
        if(OneCard.size()==0&&TwoCard.size()==1&&ThreeCard.size()==0&&Bomb.size()==0&&Goust.size()==0){//炸弹1
            cardstype=Type_Bomb;
            bombvalve=(BombValve)4;
            if(TwoCard[0]==main_card-1)BaseValve=125;
            else BaseValve=TwoCard[0]*10;
        }
        if(OneCard.size()==0&&TwoCard.size()==0&&ThreeCard.size()==1&&Bomb.size()==0&&Goust.size()==0){//炸弹2
            cardstype=Type_Bomb;
            bombvalve=(BombValve)5;
            if(ThreeCard[0]==main_card-1)BaseValve=125;
            else BaseValve=ThreeCard[0]*10;
        }
        if(OneCard.size()==0&&TwoCard.size()==0&&ThreeCard.size()==0&&Bomb.size()==1&&Goust.size()==0){//炸弹3
            cardstype=Type_Bomb;
            if(Bomb[0]==main_card-1)BaseValve=125;
            else BaseValve=Bomb[0]*10;
                cardnumber++;
            bombvalve=(BombValve)cardnumber;
        }
        if(OneCard.size()==0&&TwoCard.size()==2&&ThreeCard.size()==0&&Bomb.size()==0&&Goust.size()==0){//三顺1
            if(TwoCard[1]==Card_A&&(TwoCard[0]==Card_2||TwoCard[0]==Card_3)){
                cardstype=Type_common_TStraight;
                BaseValve=Card_3*10;
            }
            else if(TwoCard[1]-TwoCard[0]==1){
                cardstype=Type_common_TStraight;
                BaseValve=TwoCard[1]*10+10;
            }
            else if(TwoCard[1]-TwoCard[0]==1){
                cardstype=Type_common_TStraight;
                BaseValve=TwoCard[1]*10;
            }
        }
        if(OneCard.size()==2&&TwoCard.size()==1&&ThreeCard.size()==0&&Bomb.size()==0&&Goust.size()==0){//三顺2
            CardPoint k[3];
            k[0]=OneCard[0];
            k[1]=TwoCard[0];
            k[2]=OneCard[1];
            for(int a=0;a<3;a++){
                int x=a;
                for(int b=a+1;b<3;b++){
                    if(k[x]<k[b])x=b;
                }
                CardPoint t;
                t=k[a];
                k[a]=k[x];
                k[x]=t;
            }
            if(k[0]==(k[1]+1)&&k[1]==(k[2]+1)&&k[0]<Card_SG){
                BaseValve=k[0]*10;
                cardstype=Type_common_TStraight;
               }
            else if(k[0]==Card_A&&k[1]==Card_3&&k[2]==Card_2){
                BaseValve=k[1]*10;
                cardstype=Type_common_TStraight;
            }
        }
        if(OneCard.size()==1&&TwoCard.size()==1&&ThreeCard.size()==0&&Bomb.size()==0&&Goust.size()==0){//三带二1
            cardstype=Type_common_TfollowD;
            if(TwoCard[0]==main_card-1)BaseValve=125;
            else BaseValve=TwoCard[0]*10;
        }
        if(OneCard.size()==0&&TwoCard.size()==0&&ThreeCard.size()==1&&Bomb.size()==0&&Goust.size()==0){//三带二2
            cardstype=Type_common_TfollowD;
            if(ThreeCard[0]==main_card-1)BaseValve=125;
            else BaseValve=ThreeCard[0]*10;
        }
        if(OneCard.size()==3&&TwoCard.size()==0&&ThreeCard.size()==0&&Bomb.size()==0&&Goust.size()==0){//顺子
            if(OneCard[2]==Card_A&&OneCard[0]<=Card_5&&OneCard[1]<=Card_5){
                if(ifSameSuit==0){
                    BaseValve=Card_5*10;
                    cardstype=Type_common_Straight;
                }
                else{
                    BaseValve=Card_5*10;
                    cardstype=Type_Bomb;
                    bombvalve=Bomb_StraightFlush;
                }
            }
            else if(OneCard[2]-OneCard[0]<=4){
                if(ifSameSuit==0){
                    BaseValve=OneCard[0]*10+40;
                    cardstype=Type_common_Straight;
                }
                else{
                    BaseValve=Card_5*10+40;
                    cardstype=Type_Bomb;
                    bombvalve=Bomb_StraightFlush;
                }
            }

        }


    }
}
QVector<CardPoint> Hand::getvector(int a)
{
    switch(a){
       case 1:
        return OneCard;
       case 2:
        return TwoCard;
       case 3:
        return ThreeCard;
       case 4:
        return Bomb;
    }
}

QVector<Card> Hand::getgoust()
{
    return Goust;
}

CardsType Hand::getcardstype()
{
    return cardstype;
}

int Hand::getbasevalve()
{
    return BaseValve;
}

BombValve Hand::getbombvalve()
{
    return bombvalve;
}

int Hand::getextra()
{
    return Extra_Card;
}

bool Hand::if_beat(Hand other)
{
    if(other.getcardstype()==Type_Pass)return 1;
    else if(bombvalve>other.getbombvalve())return 1;
    else if(bombvalve<other.getbombvalve())return 0;
    else if(cardstype!=other.getcardstype())return 0;
    else if(BaseValve>other.getbasevalve())return 1;
    else if(BaseValve<other.getbasevalve())return 0;
    else return 0;
}

bool Hand::Hand::operator ==(const Hand &hand)
{
    return (BaseValve==hand.BaseValve&&
    Extra_Card==hand.Extra_Card&&
    cardstype==hand.cardstype&&
    bombvalve==hand.bombvalve);

}
