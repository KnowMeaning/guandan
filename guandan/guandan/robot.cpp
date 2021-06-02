#include "robot.h"
#include<qdebug.h>
#include <QVector>
robot::robot(QObject* parent)
{
    type=Unknow;

}

void robot::ThinkForPlayHand()
{
        Hand hand(punchCards);
        CardsType p_type=hand.getcardstype();
        int p_valve=hand.getbasevalve();
        Cards handcards;
        handcards.Clear();
        Hand ouhand(oucards);
        QVector<Card> cardList = oucards.ToCardList();//逆序取出自己卡牌
        int* cardrecord = new int[Card_End];
        memset(cardrecord, 0, sizeof(int) * Card_End);
        QVector<Card>::const_iterator it = cardList.constBegin();
        for (; it != cardList.constEnd(); it++){
            int i= it->cardpoint;
            cardrecord[i]++;
        }
        if(punchPlayer==this||punchPlayer==nullptr){//开牌出最小的,先出顺子
           if(StraightCards.size()>0&&Hand(StraightCards[StraightCards.size()-1]).getcardstype()!=Type_Bomb){
                QVector<Card> list=StraightCards[0].ToCardList();
                Cards cards;
                for(int i=0;i<list.size();i++){
                    cards.Add(list[i]);
                }
                HandCard(cards);
            }
            else if(TStraightCards.size()>0){
               QVector<Card> list=TStraightCards[0].ToCardList();
                Cards cards;
                for(int i=0;i<list.size();i++){
                    cards.Add(list[i]);
                }
                HandCard(cards);
            }
            else if((ouhand.getvector(1).size()+ouhand.getvector(2).size()+ouhand.getvector(3).size()+ouhand.getvector(4).size()==1)&&ouhand.getgoust().size()==0){
                Cards cards;
                for(int i=0;i<cardList.size();i++){
                    cards.Add(cardList[i]);
                }
               HandCard(cards);
            }
            else if(oucards.Count()==0&&StraightCards.size()>0){
                QVector<Card> list=StraightCards[0].ToCardList();
                Cards cards;
                for(int i=0;i<list.size();i++){
                    cards.Add(list[i]);
                }
                HandCard(cards);
            }
            else if(ouhand.getvector(1).size()==0&&ouhand.getvector(2).size()==0&&ouhand.getvector(3).size()==0&&ouhand.getvector(4).size()>0&&ouhand.getgoust().size()==0){
               for(int i=0;i<cardList.size();i++){
                        if(cardList[i].cardpoint==ouhand.getvector(4)[0]){
                            handcards.Add(cardList[i]);
                        }
                    }
                    HandCard(handcards);
            }//只剩下炸了出炸
            else if(ouhand.getvector(1).size()==0&&ouhand.getvector(2).size()==0&&ouhand.getvector(3).size()==0&&ouhand.getvector(4).size()==0&&ouhand.getgoust().size()==4){
                Cards cards;
                for(int i=0;i<cardList.size();i++){
                    cards.Add(cardList[i]);
                }
               HandCard(cards);
            }
            else{
                int i=0;
                while(cardrecord[cardList[i].cardpoint]>=4){
                    i++;
                    if(i==cardList.size())break;
                }//不优先出炸
                for(int k=i;k<cardrecord[cardList[i].cardpoint]+i;k++){
                    if(cardList[k].cardpoint==Card_SG||cardList[k].cardpoint==Card_BG){
                       handcards.Add(cardList[k]);
                       break;
                    }
                    else{
                        handcards.Add(cardList[k]);
                    }
                }
                HandCard(handcards);

            }
        }
        else if(punchPlayer==friendplayer){//队友不管
            HandCard(Cards());
        }
        else {
            Cards cards;
            for(int i=0;i<cardList.size();i++){
                cards.Add(cardList[i]);
            }
            if(Hand(cards).if_beat(hand)){
                HandCard(cards);
            }
            else if(p_type==Type_common_Third){
                int i=0;
                while(cardrecord[cardList[i].cardpoint]!=3||cardList[i].valve<=p_valve){
                    i++;if(i==cardList.size())break;
                }
                if(i!=cardList.size()){
                    for(int k=i;k<cardrecord[cardList[i].cardpoint]+i;k++){
                            handcards.Add(cardList[k]);
                    }
                    HandCard(handcards);
                }
                else{
                    //判断是否要出炸
                    if((ouhand.getvector(4).size()+StraightCards.size())>=(TStraightCards.size()+ouhand.getvector(1).size()+ouhand.getvector(2).size()+ouhand.getvector(3).size())){
                        int j;
                        for(j=0;j<StraightCards.size();j++){
                            QVector<Card> list=StraightCards[j].ToCardList();
                            Cards cards;
                            for(int i=0;i<list.size();i++){
                                cards.Add(list[i]);
                            }
                            if(Hand(cards).getcardstype()==Type_Bomb){
                                HandCard(cards);
                                j=-1;
                                break;
                            }
                        }
                        if(j==StraightCards.size()&&ouhand.getvector(4).size()>0){
                            for(int i=0;i<cardList.size();i++){
                                if(ouhand.getvector(4)[0]==cardList[i].cardpoint){
                                    handcards.Add(cardList[i]);
                                }
                            }
                            HandCard(handcards);
                        }
                        else if(j==StraightCards.size()&&ouhand.getvector(4).size()==0)HandCard(Cards());
                    }
                    else HandCard(Cards());
                }

            }
            else if(p_type==Type_common_Double){
                 int i=0;
                 while(cardrecord[cardList[i].cardpoint]!=2||cardList[i].valve<=p_valve){
                     i++;if(i==cardList.size())break;
                 }
                 if(i!=cardList.size()){
                    if(cardList[i].cardpoint==Card_SG||cardList[i].cardpoint==Card_BG){
                        HandCard(Cards());
                    }
                    else{
                        for(int k=i;k<cardrecord[cardList[i].cardpoint]+i;k++){
                            handcards.Add(cardList[k]);
                        }
                        HandCard(handcards);
                    }
                 }
                 else {//判断是否要出炸
                     if((ouhand.getvector(4).size()+StraightCards.size())>=(TStraightCards.size()+ouhand.getvector(1).size()+ouhand.getvector(2).size()+ouhand.getvector(3).size())){
                         int j;
                         for(j=0;j<StraightCards.size();j++){
                             QVector<Card> list=StraightCards[j].ToCardList();
                             Cards cards;
                             for(int i=0;i<list.size();i++){
                                 cards.Add(list[i]);
                             }
                             if(Hand(cards).getcardstype()==Type_Bomb){
                                 HandCard(cards);
                                 j=-1;
                                 break;
                             }
                         }
                         if(j==StraightCards.size()&&ouhand.getvector(4).size()>0){
                             for(int i=0;i<cardList.size();i++){
                                 if(ouhand.getvector(4)[0]==cardList[i].cardpoint){
                                     handcards.Add(cardList[i]);
                                 }
                             }
                             HandCard(handcards);
                         }
                         else if(j==StraightCards.size()&&ouhand.getvector(4).size()==0)HandCard(Cards());
                     }
                     else HandCard(Cards());
                 }
            }
            else if(p_type==Type_common_Single){
                 int i=0;
                 while(cardrecord[cardList[i].cardpoint]!=1||cardList[i].valve<=p_valve){
                     i++;if(i==cardList.size())break;
                     if((cardList[i].cardpoint==Card_SG||cardList[i].cardpoint==Card_BG)&&cardList[i].valve>p_valve)break;
                 }
                 if(i!=cardList.size()){
                    handcards.Add(cardList[i]);
                    HandCard(handcards);
                 }
                 else{//判断是否要出炸
                     if((ouhand.getvector(4).size()+StraightCards.size())>=(TStraightCards.size()+ouhand.getvector(1).size()+ouhand.getvector(2).size()+ouhand.getvector(3).size())){
                         int j;
                         for(j=0;j<StraightCards.size();j++){
                             QVector<Card> list=StraightCards[j].ToCardList();
                             Cards cards;
                             for(int i=0;i<list.size();i++){
                                 cards.Add(list[i]);
                             }
                             if(Hand(cards).getcardstype()==Type_Bomb){
                                 HandCard(cards);
                                 j=-1;
                                 break;
                             }
                         }
                         if(j==StraightCards.size()&&ouhand.getvector(4).size()>0){
                             for(int i=0;i<cardList.size();i++){
                                 if(ouhand.getvector(4)[0]==cardList[i].cardpoint){
                                     handcards.Add(cardList[i]);
                                 }
                             }
                             HandCard(handcards);
                         }
                         else if(j==StraightCards.size()&&ouhand.getvector(4).size()==0)HandCard(Cards());
                     }
                     else HandCard(Cards());
                 }
            }
            else if(p_type==Type_common_TfollowD){
                 int i=0;
                 while(cardrecord[cardList[i].cardpoint]!=3||cardList[i].valve<=p_valve){
                     i++;if(i==cardList.size())break;
                 }
                 if(i!=cardList.size()){
                    for(int k=i;k<cardrecord[cardList[i].cardpoint]+i;k++){
                         handcards.Add(cardList[k]);
                    }
                    if(ouhand.getvector(2).size()>0&&ouhand.getvector(2)[0]!=cardList[i].cardpoint){
                        for(int i=0;i<cardList.size();i++){
                            if(ouhand.getvector(2)[0]==cardList[i].cardpoint){
                                if(cardList[i].maincard==1&&cardList[i].cardsuit==Heart)continue;
                                handcards.Add(cardList[i]);
                            }
                        }
                        HandCard(handcards);
                    }
                    else{
                        HandCard(Cards());
                    }
                 }
                 else{//判断是否要出炸
                     if((ouhand.getvector(4).size()+StraightCards.size())>=(TStraightCards.size()+ouhand.getvector(1).size()+ouhand.getvector(2).size()+ouhand.getvector(3).size())){
                         int j;
                         for(j=0;j<StraightCards.size();j++){
                             QVector<Card> list=StraightCards[j].ToCardList();
                             Cards cards;
                             for(int i=0;i<list.size();i++){
                                 cards.Add(list[i]);
                             }
                             if(Hand(cards).getcardstype()==Type_Bomb){
                                 HandCard(cards);
                                 j=-1;
                                 break;
                             }
                         }
                         if(j==StraightCards.size()&&ouhand.getvector(4).size()>0){
                             for(int i=0;i<cardList.size();i++){
                                 if(ouhand.getvector(4)[0]==cardList[i].cardpoint){
                                     handcards.Add(cardList[i]);
                                 }
                             }
                             HandCard(handcards);
                         }
                         else if(j==StraightCards.size()&&ouhand.getvector(4).size()==0)HandCard(Cards());
                     }
                     else HandCard(Cards());
                 }

            }
            else if(p_type==Type_Bomb){
                 int j;
                 for(j=0;j<StraightCards.size();j++){
                     QVector<Card> list=StraightCards[j].ToCardList();
                     Cards cards;
                     cards.Clear();
                     for(int i=0;i<list.size();i++){
                         cards.Add(list[i]);
                     }
                     if(Hand(cards).getcardstype()==Type_Bomb){
                         if(Hand(cards).if_beat(hand)){
                             HandCard(cards);
                             j=-1;
                             break;
                         }
                     }
                 }
                 if(j==StraightCards.size()){
                     int i;
                     for(i=0;i<ouhand.getvector(4).size();i++){
                         Cards cards;
                         for(int k=0;k<cardList.size();k++){
                             if(cardList[k].cardpoint==ouhand.getvector(4)[i]){
                                 cards.Add(cardList[k]);
                             }
                         }
                         if(Hand(cards).if_beat(hand)){
                             HandCard(cards);
                             break;
                         }
                     }
                     if(i==ouhand.getvector(4).size())HandCard(Cards());
                 }

            }
            else if(p_type==Type_common_Straight){
                Cards cards;
                int i;
                for(i=StraightCards.size()-1;i>=0;i--){
                    QVector<Card> list=StraightCards[i].ToCardList();
                    cards.Clear();
                    for(int i=0;i<list.size();i++){
                        cards.Add(list[i]);
                    }
                    if(Hand(cards).getcardstype()==Type_Bomb){
                        continue;
                    }
                    else if(Hand(cards).if_beat(hand)){
                        HandCard(cards);
                        break;
                    }
                }
                if(i<0){//判断是否要出炸
                    if((ouhand.getvector(4).size()+StraightCards.size())>=(TStraightCards.size()+ouhand.getvector(1).size()+ouhand.getvector(2).size()+ouhand.getvector(3).size())){
                        int j;
                        for(j=0;j<StraightCards.size();j++){
                            QVector<Card> list=StraightCards[j].ToCardList();
                            Cards cards;
                            for(int i=0;i<list.size();i++){
                                cards.Add(list[i]);
                            }
                            if(Hand(cards).getcardstype()==Type_Bomb){
                                HandCard(cards);
                                j=-1;
                                break;
                            }
                        }
                        if(j==StraightCards.size()&&ouhand.getvector(4).size()>0){
                            for(int i=0;i<cardList.size();i++){
                                if(ouhand.getvector(4)[0]==cardList[i].cardpoint){
                                    handcards.Add(cardList[i]);
                                }
                            }
                            HandCard(handcards);
                        }
                        else if(j==StraightCards.size()&&ouhand.getvector(4).size()==0)HandCard(Cards());
                    }
                    else HandCard(Cards());
                }
            }
            else if(p_type==Type_common_TStraight){
                 Cards cards;
                 int i;
                 for(i=TStraightCards.size()-1;i>=0;i--){
                     QVector<Card> list=TStraightCards[i].ToCardList();
                     cards.Clear();
                     for(int i=0;i<list.size();i++){
                         cards.Add(list[i]);
                     }
                     if(Hand(cards).getcardstype()==Type_Bomb){
                         continue;
                     }
                     else if(Hand(cards).if_beat(hand)){
                         HandCard(cards);
                         break;
                     }
                 }
                 if(i<0){
                     //判断是否要出炸
                     if((ouhand.getvector(4).size()+StraightCards.size())>=(TStraightCards.size()+ouhand.getvector(1).size()+ouhand.getvector(2).size()+ouhand.getvector(3).size())){
                         int j;
                         for(j=0;j<StraightCards.size();j++){
                             QVector<Card> list=StraightCards[j].ToCardList();
                             Cards cards;
                             for(int i=0;i<list.size();i++){
                                 cards.Add(list[i]);
                             }
                             if(Hand(cards).getcardstype()==Type_Bomb){
                                 HandCard(cards);
                                 j=-1;
                                 break;
                             }
                         }
                         if(j==StraightCards.size()&&ouhand.getvector(4).size()>0){
                             for(int i=0;i<cardList.size();i++){
                                 if(ouhand.getvector(4)[0]==cardList[i].cardpoint){
                                     handcards.Add(cardList[i]);
                                 }
                             }
                             HandCard(handcards);
                         }
                         else if(j==StraightCards.size()&&ouhand.getvector(4).size()==0)HandCard(Cards());
                     }
                     else HandCard(Cards());
                 }
            }
            else{
                HandCard(Cards());
            }
        }

    emit Send_EndHand();
}

void robot::ThinkForTribute()
{
    SearchStraight();
    QVector<Card> CARD=oucards.ToCardList(Cards::Desc);//由大到小；
    int* cardrecord=new int[Card_End];
    memset(cardrecord,0,sizeof(int)*Card_End);
    QVector<Card>::const_iterator it=CARD.constBegin();
    for (;it!=CARD.constEnd();it++){
        int i=it->cardpoint;
        cardrecord[i]++;
    }
    Card itcard;
    int i;
    for(i=Card_2;i<=Card_10;i++){
        if(cardrecord[i]==1){
            for(it=CARD.constEnd();it!=CARD.constBegin();it--){
                itcard.deck=it->deck;
                itcard.valve=it->valve;
                itcard.cardsuit=it->cardsuit;
                itcard.maincard=it->maincard;
                itcard.cardpoint=it->cardpoint;
                if(itcard.cardpoint==i){
                    break;
                }
            }
            break;
        }
    }
    if(i<=Card_10){
        TributeCard(itcard);
    }
    else{
        TributeCard(CARD[CARD.size()-1]);
    }

}

void robot::SearchStraight()
{
    Hand handcard(oucards);
    for(int i=0;i<StraightCards.count();i++){
        outstringcards(StraightCards[i]);
    }
    QVector<Card> Suit_Diamond;QVector<Card> Suit_Club;QVector<Card> Suit_Heart;QVector<Card> Suit_Spade;
    QVector<Card> CARD=oucards.ToCardList(Cards::Desc);//由大到小；
    QVector<Card>::ConstIterator itc=CARD.constBegin();
    for(;itc!=CARD.constEnd();itc++){
        Card itcard;
        int x=0;
        itcard.deck=itc->deck;
        itcard.valve=itc->valve;
        itcard.cardsuit=itc->cardsuit;
        itcard.maincard=itc->maincard;
        itcard.cardpoint=itc->cardpoint;
        for(int i=0;i<handcard.getvector(4).size();i++){
            if(itcard.cardpoint==handcard.getvector(4)[i]){
                x=1;break;
            }
        }
        if(x)continue;//寻找同花顺时不把炸弹拆掉；
        switch(itc->cardsuit){
        case Diamond:Suit_Diamond.push_back(itcard);break;
        case Club:Suit_Club.push_back(itcard);break;
        case Heart:Suit_Heart.push_back(itcard);break;
        case Spade:Suit_Spade.push_back(itcard);break;
        default:break;
        }
    }
    Cards stright;
    for(int i=0;i<Suit_Diamond.count();i++){
        stright.Clear();
        int k=0;
        int num=Suit_Diamond[i].cardpoint;
        int savenumber[5];
        savenumber[k]=i;
        k++;
        stright.Add(Suit_Diamond[i]);
        for(int j=i+1;j<Suit_Diamond.count();j++){
            if(Suit_Diamond[j].cardpoint+1==num){
                num--;
                savenumber[k]=j;
                k++;
                stright.Add(Suit_Diamond[j]);
            }
            if(k==5)break;
        }
        if(k==5){
            addstringcards(stright);
            i--;
            for(;k>0;k--){
                Suit_Diamond.remove(savenumber[k-1]);
            }
        }
    }
    for(int i=0;i<Suit_Club.count();i++){
        stright.Clear();
        int k=0;
        int num=Suit_Club[i].cardpoint;
        int savenumber[5];
        savenumber[k]=i;
        k++;
        stright.Add(Suit_Club[i]);
        for(int j=i+1;j<Suit_Club.count();j++){
            if(Suit_Club[j].cardpoint+1==num){
                num--;
                savenumber[k]=j;
                k++;
                stright.Add(Suit_Club[j]);
            }
            if(k==5)break;
        }
        if(k==5){
            addstringcards(stright);
            i--;
            for(;k>0;k--){
                Suit_Club.remove(savenumber[k-1]);
            }
        }
    }
    for(int i=0;i<Suit_Heart.count();i++){
        stright.Clear();
        int k=0;
        int num=Suit_Heart[i].cardpoint;
        int savenumber[5];
        savenumber[k]=i;
        k++;
        stright.Add(Suit_Heart[i]);
        for(int j=i+1;j<Suit_Heart.count();j++){
            if(Suit_Heart[j].cardpoint+1==num){
                num--;
                savenumber[k]=j;
                k++;
                stright.Add(Suit_Heart[j]);
            }
            if(k==5)break;
        }
        if(k==5){
            addstringcards(stright);
            i--;
            for(;k>0;k--){
                Suit_Heart.remove(savenumber[k-1]);
            }
        }
    }
    for(int i=0;i<Suit_Spade.count();i++){
        stright.Clear();
        int k=0;
        int num=Suit_Spade[i].cardpoint;
        int savenumber[5];
        savenumber[k]=i;
        k++;
        stright.Add(Suit_Spade[i]);
        for(int j=i+1;j<Suit_Spade.count();j++){
            if(Suit_Spade[j].cardpoint+1==num){
                num--;
                savenumber[k]=j;
                k++;
                stright.Add(Suit_Spade[j]);
            }
            if(k==5)break;
        }
        if(k==5){
            addstringcards(stright);
            i--;
            for(;k>0;k--){
                Suit_Spade.remove(savenumber[k-1]);
            }
        }
    }
    //先找同花顺
    CARD=oucards.ToCardList(Cards::Desc);
    int* cardrecord=new int[Card_End];
    memset(cardrecord,0,sizeof(int)*Card_End);
    QVector<Card>::const_iterator it=CARD.constBegin();
    for (;it!=CARD.constEnd();it++){
        int i=it->cardpoint;
        cardrecord[i]++;
    }
    for(int i=Card_2;i<Card_SG;i++){
        if(cardrecord[i]==2&&cardrecord[i+1]==2&&cardrecord[i+2]==2){
            cardrecord[i]-=2;cardrecord[i+1]-=2;cardrecord[i+2]-=2;
            Cards TStiaght;
            TStiaght.Clear();
            for(it=CARD.constBegin();it!=CARD.constEnd();it++){
                Card itcard;
                itcard.deck=it->deck;
                itcard.valve=it->valve;
                itcard.cardsuit=it->cardsuit;
                itcard.maincard=it->maincard;
                itcard.cardpoint=it->cardpoint;
                if(itcard.cardpoint==i||itcard.cardpoint==i+1||itcard.cardpoint==i+2){
                    TStiaght.Add(itcard);
                }
                addstringcards(TStiaght);
            }
            TStiaght.Clear();
            i+=2;
        }
        if(cardrecord[i]==1&&cardrecord[i+1]==1&&cardrecord[i+2]==1&&cardrecord[i+3]==1&&cardrecord[i+4]==1){
            cardrecord[i]-=1;cardrecord[i+1]-=1;cardrecord[i+2]-=1;cardrecord[i+3]-=1;cardrecord[i+4]-=1;
            Cards straight;
            straight.Clear();
            for(it=CARD.constBegin();it!=CARD.constEnd();it++){
                Card itcard;
                itcard.deck=it->deck;
                itcard.valve=it->valve;
                itcard.cardsuit=it->cardsuit;
                itcard.maincard=it->maincard;
                itcard.cardpoint=it->cardpoint;
                if(itcard.cardpoint==i||itcard.cardpoint==i+1||itcard.cardpoint==i+2||itcard.cardpoint==i+3||itcard.cardpoint==i+4){
                    straight.Add(itcard);
                }
                addstringcards(straight);
            }
            straight.Clear();
            i+=5;
        }
    }
    //找出三对和顺子；
    for(int i=Card_2;i<Card_SG;i++){
        Cards straight;
        straight.Clear();
        if(cardrecord[i]==2&&cardrecord[i+1]==1&&cardrecord[i+2]==1&&cardrecord[i+3]==1&&cardrecord[i+4]==1){
            cardrecord[i]-=1;cardrecord[i+1]-=1;cardrecord[i+2]-=1;cardrecord[i+3]-=1;cardrecord[i+4]-=1;
            for(it=CARD.constBegin();it!=CARD.constEnd();it++){
                Card itcard;
                itcard.deck=it->deck;
                itcard.valve=it->valve;
                itcard.cardsuit=it->cardsuit;
                itcard.maincard=it->maincard;
                itcard.cardpoint=it->cardpoint;
                if(itcard.cardpoint==i){
                    straight.Add(itcard);
                    it++;
                }
                if(itcard.cardpoint==i+1||itcard.cardpoint==i+2||itcard.cardpoint==i+3||itcard.cardpoint==i+4){
                    straight.Add(itcard);
                }
            }
            straight.Clear();
            addstringcards(straight);
        }
        if(cardrecord[i]==1&&cardrecord[i+1]==2&&cardrecord[i+2]==1&&cardrecord[i+3]==1&&cardrecord[i+4]==1){
            cardrecord[i]-=1;cardrecord[i+1]-=1;cardrecord[i+2]-=1;cardrecord[i+3]-=1;cardrecord[i+4]-=1;
            for(it=CARD.constBegin();it!=CARD.constEnd();it++){
                Card itcard;
                itcard.deck=it->deck;
                itcard.valve=it->valve;
                itcard.cardsuit=it->cardsuit;
                itcard.maincard=it->maincard;
                itcard.cardpoint=it->cardpoint;
                if(itcard.cardpoint==i+1){
                    straight.Add(itcard);
                    it++;
                }
                if(itcard.cardpoint==i||itcard.cardpoint==i+2||itcard.cardpoint==i+3||itcard.cardpoint==i+4){
                    straight.Add(itcard);
                }
            }
            straight.Clear();
            addstringcards(straight);
        }
        if(cardrecord[i]==1&&cardrecord[i+1]==1&&cardrecord[i+2]==2&&cardrecord[i+3]==1&&cardrecord[i+4]==1){
            cardrecord[i]-=1;cardrecord[i+1]-=1;cardrecord[i+2]-=1;cardrecord[i+3]-=1;cardrecord[i+4]-=1;
            for(it=CARD.constBegin();it!=CARD.constEnd();it++){
                Card itcard;
                itcard.deck=it->deck;
                itcard.valve=it->valve;
                itcard.cardsuit=it->cardsuit;
                itcard.maincard=it->maincard;
                itcard.cardpoint=it->cardpoint;
                if(itcard.cardpoint==i+2){
                    straight.Add(itcard);
                    it++;
                }
                if(itcard.cardpoint==i||itcard.cardpoint==i+1||itcard.cardpoint==i+3||itcard.cardpoint==i+4){
                    straight.Add(itcard);
                }
            }
            straight.Clear();
            addstringcards(straight);
        }
        if(cardrecord[i]==1&&cardrecord[i+1]==1&&cardrecord[i+2]==1&&cardrecord[i+3]==2&&cardrecord[i+4]==1){
            cardrecord[i]-=1;cardrecord[i+1]-=1;cardrecord[i+2]-=1;cardrecord[i+3]-=1;cardrecord[i+4]-=1;
            for(it=CARD.constBegin();it!=CARD.constEnd();it++){
                Card itcard;
                itcard.deck=it->deck;
                itcard.valve=it->valve;
                itcard.cardsuit=it->cardsuit;
                itcard.maincard=it->maincard;
                itcard.cardpoint=it->cardpoint;
                if(itcard.cardpoint==i+3){
                    straight.Add(itcard);
                    it++;
                }
                if(itcard.cardpoint==i||itcard.cardpoint==i+2||itcard.cardpoint==i+1||itcard.cardpoint==i+4){
                    straight.Add(itcard);
                }
            }
            straight.Clear();
            addstringcards(straight);
        }
        if(cardrecord[i]==1&&cardrecord[i+1]==1&&cardrecord[i+2]==1&&cardrecord[i+3]==1&&cardrecord[i+4]==2){
            cardrecord[i]-=1;cardrecord[i+1]-=1;cardrecord[i+2]-=1;cardrecord[i+3]-=1;cardrecord[i+4]-=1;
            for(it=CARD.constBegin();it!=CARD.constEnd();it++){
                Card itcard;
                itcard.deck=it->deck;
                itcard.valve=it->valve;
                itcard.cardsuit=it->cardsuit;
                itcard.maincard=it->maincard;
                itcard.cardpoint=it->cardpoint;
                if(itcard.cardpoint==i+4){
                    straight.Add(itcard);
                    it++;
                }
                if(itcard.cardpoint==i||itcard.cardpoint==i+2||itcard.cardpoint==i+3||itcard.cardpoint==i+1){
                    straight.Add(itcard);
                }
            }
            straight.Clear();
            addstringcards(straight);
        }
    }

}
