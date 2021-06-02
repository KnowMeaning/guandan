#include "user.h"
#include<QDebug>
User::User(QObject* parent)
{
    type=PUser;
}

void User::SearchStraight()
{
    for(int i=0;i<StraightCards.count();i++){
        outstringcards(StraightCards[i]);
    }
    Hand hand(oucards);
    QVector<Card> Suit_Diamond;QVector<Card> Suit_Club;QVector<Card> Suit_Heart;QVector<Card> Suit_Spade;
    QVector<Card> CARD=oucards.ToCardList(Cards::Desc);//由大到小；
    QVector<Card>::ConstIterator itc=CARD.constBegin();
    for(;itc!=CARD.constEnd();itc++){
        Card itcard;
        itcard.deck=itc->deck;
        itcard.valve=itc->valve;
        itcard.cardsuit=itc->cardsuit;
        itcard.maincard=itc->maincard;
        itcard.cardpoint=itc->cardpoint;
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


}
