#include"gamepanel.h"
#include<qpainter.h>
#include<QDebug>
#include<QtDebug>
#include<qpainter.h>
#include<QHBoxLayout>
#include<qpixmap.h>
#include<QTime>
#include<QCoreApplication>
#include<qthread.h>
#include<QMessageBox>
GamePanel::GamePanel(QWidget *parent) : QWidget(parent)
{
    qRegisterMetaType<Hand>("Hand");
    qRegisterMetaType<Card>("Card");
    qRegisterMetaType<Cards>("Cards");
    main_markBoard=new MarkBoard(this);
    main_markBoard->show();
    main_winerBoard=new WinerBoard(this);
    main_winerBoard->show();

    main_cardsize=QSize(80,105);
    init();
    NowMoveStep=0;
    pickCardTimer=new QTimer(this);
    pickCardTimer->setInterval(8);
    connect(pickCardTimer,&QTimer::timeout,this,&GamePanel::StartPickingCard);
}
void GamePanel::paintEvent(QPaintEvent* event)//设置背景
{
    static QPixmap bk(":/res/table.png");
    QPainter painter(this);
    painter.drawPixmap(rect(),bk);
}
void GamePanel::resizeEvent(QResizeEvent* event)//设置了界面的分布
{
    main_markBoard->setGeometry(rect().right()-130,0,130,80);
    main_winerBoard->setGeometry(rect().left(),0,130,80);
    main_baseCardPos=QPoint((width()-main_cardsize.width())/2,height()/2-100);
    main_baseCard->move(main_baseCardPos);
    main_baseCard->hide();
    main_movingCard->move(main_baseCardPos);
    main_movingCard->hide();

    QMap<Player*,PlayerContext>::Iterator it;

    //左机器人
    it=playerContextMap.find(left_robot);
    it->cardsRect=QRect(10,180,100,height()-200);
    it->playHandRect=QRect(180,180,100,100);

    //右机器人
    it=playerContextMap.find(right_robot);
    it->cardsRect=QRect(rect().right()-110,180,100,height()-200);
    it->playHandRect=QRect(rect().right()-280,180,100,100);

    //friend
    it=playerContextMap.find(friend_robot);
    it->cardsRect=QRect(250,10,width()-500,100);
    it->playHandRect=QRect(150,130,width()-300,100);

    //我
    it=playerContextMap.find(user);
    it->cardsRect=QRect(250,rect().bottom()-120,width()-500,100);
    it->playHandRect=QRect(150,rect().bottom()-280,width()-300,100);

    //放置按钮区
    QRect rectUserTool(it->playHandRect.left(),it->playHandRect.bottom(),it->playHandRect.width(),it->cardsRect.top()-it->playHandRect.bottom());
    userTool->setGeometry(rectUserTool);
    //
    for(it=playerContextMap.begin();it!=playerContextMap.end();it++)
    {
        QRect playCardsRect=it->playHandRect;
        QLabel* infoLabel=it->info;
        QPoint pt(playCardsRect.left()+(playCardsRect.width()-infoLabel->width())/2,playCardsRect.top()+(playCardsRect.height()-infoLabel->height())/2);
        infoLabel->move(pt);
    }

}

void GamePanel::init()
{
    mark1=0;mark2=0;
    Atime1=0;Atime2=0;
    main_markBoard->setmark(0,0);
    initCardPicMap();//牌设置牌与牌面link
    initcontrol();//按钮设置
    initplayers();//设置玩家与玩家位置的联系
    initconnect();
    main_baseCard=new CardPic(this);
    main_movingCard=new CardPic(this);
    main_baseCard->setpic(main_cardbackpic,main_cardbackpic);
    main_movingCard->setpic(main_cardbackpic,main_cardbackpic);
    main_baseCard->hide();
    main_movingCard->hide();
    qsrand((quint32)time(0));
    int i=qrand()%4;
    switch(i){
        case 0:nowplayer=user;break;
        case 1:nowplayer=right_robot;break;
        case 2:nowplayer=friend_robot;break;
        case 3:nowplayer=left_robot;break;
    }

}

void GamePanel::initall_cards()
{
    all_cards.Clear();
    if(first==nullptr||first==friend_robot||first==user){
        for(uint a=0;a<2;a++){
            for(int suit=Suit_Start+1,i=0;suit<Suit_End;suit++,i++)
                {
                    for(int pt=Card_3;pt<=Card_A;pt++)
                    {
                        Card card;
                        card.deck=a;
                        card.cardpoint=(CardPoint)pt;
                        card.cardsuit=(CardSuit)suit;
                        if(pt==mark1){
                            card.maincard=(if_maincard)1;
                            card.valve=125;
                        }
                        else{
                            card.maincard=(if_maincard)0;
                            card.valve=card.cardpoint*10;
                        }
                        all_cards.Add(card);
                    }
                    Card card;
                    card.deck=a;
                    card.cardpoint=Card_2;
                    card.cardsuit=(CardSuit)suit;
                    if(mark1==0){
                        card.maincard=(if_maincard)1;
                        card.valve=125;
                    }
                    else{
                        card.maincard=(if_maincard)0;
                        card.valve=card.cardpoint*10;
                    }
                    all_cards.Add(card);
            }
            for(int i=0;i<2;i++){
                Card card;
                card.maincard=(if_maincard)0;
                card.deck=a;
                card.cardpoint=(CardPoint)(i+int(Card_SG));
                card.valve=card.cardpoint*10;
                card.cardsuit=Suit_Start;
                all_cards.Add(card);
                }
    }
    }
    else{
        for(uint a=0;a<2;a++){
            for(int suit=Suit_Start+1,i=0;suit<Suit_End;suit++,i++)
                {
                    for (int pt=Card_3;pt<=Card_A;pt++)
                    {
                        Card card;
                        card.deck=a;
                        card.cardpoint=(CardPoint)pt;
                        card.cardsuit=(CardSuit)suit;
                        if(pt==mark2){
                            card.maincard=(if_maincard)1;
                            card.valve=125;
                        }
                        else{
                            card.maincard=(if_maincard)0;
                            card.valve=card.cardpoint*10;
                        }
                        all_cards.Add(card);
                    }
                    Card card;
                    card.deck=a;
                    card.cardpoint=Card_2;
                    card.cardsuit=(CardSuit)suit;
                    if(mark2==0){
                        card.maincard=(if_maincard)1;
                        card.valve=125;
                    }
                    else{
                        card.maincard=(if_maincard)0;
                        card.valve=card.cardpoint*10;
                    }
                    all_cards.Add(card);
            }
            for(int i=0;i<2;i++){
                Card card;
                card.maincard=(if_maincard)0;
                card.deck=a;
                card.cardpoint=(CardPoint)(i+int(Card_SG));
                card.cardsuit=Suit_Start;
                card.valve=card.cardpoint*10;
                all_cards.Add(card);
                }
    }
    }
}

void GamePanel::initCardPicMap()
{
    QPixmap cardsPic(":/res/card.png");
    main_cardbackpic=cardsPic.copy(2*main_cardsize.width(),4*main_cardsize.height(),main_cardsize.width(),main_cardsize.height());
//背面
    all_cards.Clear();
    for(uint a=0;a<2;a++){
        for(int if_main=0;if_main<2;if_main++){
        for(int suit=Suit_Start+1,i=0;suit<Suit_End;suit++,i++){
            int j=0;
            for(int pt=Card_3;pt<=Card_A;pt++,j++)
            {
            Card card;
            card.deck=a;
            card.cardpoint=(CardPoint)pt;
            card.cardsuit=(CardSuit)suit;
            card.maincard=(if_maincard)if_main;
            if(if_main)card.valve=125;
            else card.valve=card.cardpoint*10;
            QPixmap pic=cardsPic.copy(j*main_cardsize.width(),i*main_cardsize.height(),main_cardbackpic.width(),main_cardbackpic.height());
            CardPic* cardPic=new CardPic(this);
            cardPic->hide();
            cardPic->setpic(pic,main_cardbackpic);
            cardPic->setcard(card);
            cardpiclink.insert(card,cardPic);
            connect(cardPic,&CardPic::SendSelected,this,&GamePanel::selectcard);
            }
            Card card;
            card.deck=a;
            card.cardpoint=Card_2;
            card.cardsuit=(CardSuit)suit;
            card.maincard=(if_maincard)if_main;
            if(if_main)card.valve=125;
            else card.valve=card.cardpoint*10;
            QPixmap pic=cardsPic.copy(j*main_cardsize.width(),i*main_cardsize.height(),main_cardbackpic.width(),main_cardbackpic.height());
            CardPic* cardPic=new CardPic(this);
            cardPic->hide();
            cardPic->setpic(pic,main_cardbackpic);
            cardPic->setcard(card);
            cardpiclink.insert(card,cardPic);
            connect(cardPic,&CardPic::SendSelected,this,&GamePanel::selectcard);
        }
    }

    // 大小王较特殊，分别处理
        for(int i=0;i<2;i++){
            Card card;
            card.maincard=(if_maincard)0;
            card.deck=a;
            card.cardpoint=(CardPoint)(Card_SG+i);
            card.cardsuit=Suit_Start;
            card.valve=card.cardpoint*10;
            QPixmap pic=cardsPic.copy(i*main_cardsize.width(),4 * main_cardsize.height(),main_cardbackpic.width(),main_cardbackpic.height());
            CardPic* cardPic=new CardPic(this);
            cardPic->hide();
            cardPic->setpic(pic,main_cardbackpic);
            cardPic->setcard(card);
            cardpiclink.insert(card,cardPic);
            connect(cardPic,&CardPic::SendSelected,this,&GamePanel::selectcard);
        }

    }

}

void GamePanel::initcontrol()//按钮设置及连接
{
    userTool=new QFrame(this);
    QHBoxLayout* horLayout=new QHBoxLayout(userTool);
    horLayout->setSpacing(9);
    horLayout->addItem(new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Minimum));
//按钮框架
    startbutton=new QPushButton(userTool);
    startbutton->setObjectName("button");
    startbutton->setText(tr("开始游戏"));
    startbutton->show();
    startbutton->setFixedSize(89,32);
    QFont font=startbutton->font();
    font.setBold(true);
    font.setPixelSize(14);
    startbutton->setFont(font);
    horLayout->addWidget(startbutton);
    connect(startbutton,&QPushButton::clicked,this,&GamePanel::startbuttonclick);
//开始按钮
    continuebutton=new QPushButton(userTool);
    continuebutton->setObjectName("button");
    continuebutton->setText(tr("继续游戏"));
    continuebutton->hide();
    continuebutton->setFixedSize(89,32);
    font=continuebutton->font();
    font.setBold(true);
    font.setPixelSize(14);
    continuebutton->setFont(font);
    horLayout->addWidget(continuebutton);
    connect(continuebutton,&QPushButton::clicked,this,&GamePanel::continuebuttonclick);
//第二局按钮
    tributebutton=new QPushButton(userTool);
    tributebutton->setObjectName("button");
    tributebutton->setText(tr("还贡"));
    tributebutton->hide();
    tributebutton->setFixedSize(89,32);
    font=tributebutton->font();
    font.setBold(true);
    font.setPixelSize(14);
    tributebutton->setFont(font);
    horLayout->addWidget(tributebutton);
    connect(tributebutton,&QPushButton::clicked,this,&GamePanel::tributebuttonclick);
//还贡按钮
    passbutton=new QPushButton(userTool);
    passbutton->setObjectName("button");
    passbutton->setText(tr("不要"));
    passbutton->hide();
    passbutton->setFixedSize(89,32);
    font=passbutton->font();
    font.setBold(true);
    font.setPixelSize(14);
    passbutton->setFont(font);
    horLayout->addWidget(passbutton);
    connect(passbutton,&QPushButton::clicked,this,&GamePanel::passbuttonclick);
//跳过按钮
    handbutton=new QPushButton(userTool);
    handbutton->setObjectName("button");
    handbutton->setText(tr("出牌"));
    handbutton->hide();
    handbutton->setFixedSize(89,32);
    font=handbutton->font();
    font.setBold(true);
    font.setPixelSize(14);
    handbutton->setFont(font);
    horLayout->addWidget(handbutton);
    connect(handbutton,&QPushButton::clicked,this,&GamePanel::handbuttonclick);
    //出牌按钮
    adjustbutton=new QPushButton(userTool);
    adjustbutton->setObjectName("button");
    adjustbutton->setText(tr("调整"));
    adjustbutton->hide();
    adjustbutton->setFixedSize(89,32);
    font=adjustbutton->font();
    font.setBold(true);
    font.setPixelSize(14);
    adjustbutton->setFont(font);
    horLayout->addWidget(adjustbutton);
    connect(adjustbutton,&QPushButton::clicked,this,&GamePanel::adjustbuttonclick);
    //调整按钮；
    backbutton=new QPushButton(userTool);
    backbutton->setObjectName("button");
    backbutton->setText(tr("调出"));
    backbutton->hide();
    backbutton->setFixedSize(89,32);
    font=backbutton->font();
    font.setBold(true);
    font.setPixelSize(14);
    backbutton->setFont(font);
    horLayout->addWidget(backbutton);
    connect(backbutton,&QPushButton::clicked,this,&GamePanel::backbuttonclick);

    horLayout->addItem(new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Minimum));
}

void GamePanel::initplayers()//玩家设置，将玩家与用户框连接
{
    first=nullptr;second=nullptr;third=nullptr;last=nullptr;
    punchplayer=nullptr;nowplayer=nullptr;
    left_robot=new robot(this);right_robot=new robot(this);friend_robot=new robot(this);user=new User(this);

    left_robot->SetType(antirobot);right_robot->SetType(antirobot);friend_robot->SetType(friendrobot);

    left_robot->SetName(tr("左机器人"));right_robot->SetName(tr("右机器人"));friend_robot->SetName(tr("友机器人"));user->SetName(tr("我"));

        PlayerContext context;

        context.cardsAlign=Vertical;
        context.isFrontSide=true;
        playerContextMap.insert(left_robot,context);
    //左机器人
        context.cardsAlign=Vertical;
        context.isFrontSide=true;
        playerContextMap.insert(right_robot,context);
    //右机器人
        context.cardsAlign=Horizontal;
        context.isFrontSide=true;
        playerContextMap.insert(friend_robot,context);
    //friend
        context.cardsAlign=Horizontal;
        context.isFrontSide=true;
        playerContextMap.insert(user,context);
    //玩家
        QMap<Player*,PlayerContext>::Iterator it=playerContextMap.begin();
        for(;it!=playerContextMap.end();it++)
        {
            it->info=new QLabel(this);
            it->info->resize(100,50);
            it->info->setObjectName("info");
            it->info->hide();
        }

        left_robot->SetPrevPlayer(friend_robot);
        left_robot->SetNextPlayer(user);
        left_robot->setfriend(right_robot);
        right_robot->SetPrevPlayer(user);
        right_robot->SetNextPlayer(friend_robot);
        right_robot->setfriend(left_robot);
        user->SetPrevPlayer(left_robot);
        user->SetNextPlayer(right_robot);
        user->setfriend(friend_robot);
        friend_robot->SetPrevPlayer(right_robot);
        friend_robot->SetNextPlayer(left_robot);
        friend_robot->setfriend(user);
}

void GamePanel::initconnect()
{
    connect(left_robot,&robot::Send_PickCards,this,&GamePanel::OnPlayerPickCards);
    connect(right_robot,&robot::Send_PickCards,this,&GamePanel::OnPlayerPickCards);
    connect(friend_robot,&robot::Send_PickCards,this,&GamePanel::OnPlayerPickCards);
    connect(user,&User::Send_PickCards,this,&GamePanel::OnPlayerPickCards);

    connect(left_robot,&robot::Send_PlayHand,this,&GamePanel::OnPlayerHandCards);
    connect(right_robot,&robot::Send_PlayHand,this,&GamePanel::OnPlayerHandCards);
    connect(friend_robot,&robot::Send_PlayHand,this,&GamePanel::OnPlayerHandCards);
    connect(user,&User::Send_PlayHand,this,&GamePanel::OnPlayerHandCards);

    connect(left_robot,&robot::Send_EndHand,this,&GamePanel::startplayhand);
    connect(right_robot,&robot::Send_EndHand,this,&GamePanel::startplayhand);
    connect(friend_robot,&robot::Send_EndHand,this,&GamePanel::startplayhand);

    connect(left_robot,&robot::Send_TributeHand,this,&GamePanel::OnPlayerTributeCards);
    connect(right_robot,&robot::Send_TributeHand,this,&GamePanel::OnPlayerTributeCards);
    connect(friend_robot,&robot::Send_TributeHand,this,&GamePanel::OnPlayerTributeCards);
    connect(user,&User::Send_TributeHand,this,&GamePanel::OnPlayerTributeCards);

}
void GamePanel::OnPlayerPickCards(Player* player, const Cards& cards)//发牌环节获得牌并整理排序
{
    UpdatePlayerCards(player);
}

void GamePanel::OnPlayerHandCards(Player *player, const Cards &cards)
{
    if(!cards.IsEmpty())
         {
             punchplayer=player;
             punchcards=cards;
             if(player->getcardssize()==0){
                    handending(player);
             }
        }
        HideLastCards(player);

        //记录上一次打的牌
        QMap<Player*,PlayerContext>::Iterator itContext=playerContextMap.find(player);
        itContext->lastCards=cards;

        //打空牌，显示“不要”
        if(cards.IsEmpty())
        {
            itContext->info->setText(tr("不要"));
            itContext->info->show();
        }

        UpdatePlayerCards(player);
}

void GamePanel::OnPlayerTributeCards(Player *player, const Cards &cards, Player *Tribute)
{
    UpdatePlayerCards(player);
    Tribute->PickCards(cards);
    if(Tribute==last){
        tributebutton->hide();
        user->SearchStraight();
        left_robot->SearchStraight();
        right_robot->SearchStraight();
        friend_robot->SearchStraight();
        UpdatePlayerCards(user);
        UpdatePlayerCards(left_robot);
        UpdatePlayerCards(right_robot);
        UpdatePlayerCards(friend_robot);
        startplayhand();
    }
}

void GamePanel::HideLastCards(Player *player)
{
    QMap<Player*,PlayerContext>::Iterator it=playerContextMap.find(player);
    if(it!=playerContextMap.end())
    {
        if(it->lastCards.IsEmpty())	//上一次打的空牌，即pass
        {
            it->info->hide();
        }
        else
        {
            QVector<Card>lastCardList=it->lastCards.ToCardList();
            QVector<Card>::ConstIterator itLast=lastCardList.constBegin();
            for(;itLast!=lastCardList.constEnd();itLast++)
            {
               cardpiclink[*itLast]->hide();
            }
        }
    }
}

void GamePanel::UpdatePlayerCards(Player* player)//显示打出的牌的剩下的手牌
{
    Cards restCards=player->getcard();
    QVector<Card> restCardList=restCards.ToCardList(Cards::Desc);
    QVector<Cards> reststrightcardList=player->getstringhcards();
    QVector<Cards> restTStrightcardList=player->getTStrightcards();
    const int cardSpacing=20;		//牌间隔
    //显示剩下的牌
    QRect cardsRect=playerContextMap[player].cardsRect;
    QVector<Card>::ConstIterator itRest=restCardList.constBegin();
    int i=0;
    for(;itRest!=restCardList.constEnd();itRest++,i++)
    {
        CardPic* cardPic=cardpiclink[*itRest];

        cardPic->setfrontside(playerContextMap[player].isFrontSide);
        cardPic->show();
        cardPic->raise();
        if(playerContextMap[player].cardsAlign==Horizontal)
        {
            int leftBase=cardsRect.left()+(cardsRect.width()-(restCardList.size()+reststrightcardList.size()*5+restTStrightcardList.size()*6-1)*cardSpacing-cardPic->width())/2;
            int top=cardsRect.top()+(cardsRect.height()-cardPic->height())/2;
            if(cardPic->getselected())top-=10;

            cardPic->move(leftBase+i*cardSpacing,top);
        }
        else
        {
            int left=cardsRect.left()+(cardsRect.width()-cardPic->width())/2;
            if(cardPic->getselected())left+=10;
            int topBase=cardsRect.top()+(cardsRect.height()-(restCardList.size()+reststrightcardList.size()*5+restTStrightcardList.size()*6-1)*cardSpacing-cardPic->height())/2;
            cardPic->move(left,topBase+i*cardSpacing);
        }
        cardPic=nullptr;
    }
    QVector<Cards>::ConstIterator Rest=reststrightcardList.constBegin();
    for(;Rest!=reststrightcardList.constEnd();Rest++)
    {
        QVector<Card> strightCardList=Rest->ToCardList(Cards::Desc);
        QVector<Card>::ConstIterator stright=strightCardList.constBegin();
        for(;stright!=strightCardList.constEnd();stright++,i++)
        {
            CardPic* cardPic=cardpiclink[*stright];
            cardPic->setfrontside(playerContextMap[player].isFrontSide);
            cardPic->show();
            cardPic->raise();
            if(playerContextMap[player].cardsAlign==Horizontal)
            {
                int leftBase=cardsRect.left()+(cardsRect.width()-(restCardList.size()+reststrightcardList.size()*5+restTStrightcardList.size()*6-1)*cardSpacing-cardPic->width())/2;
                int top=cardsRect.top()+(cardsRect.height()-cardPic->height())/2;
                if(cardPic->getselected())top-=10;

               cardPic->move(leftBase+i*cardSpacing,top);
           }
            else
            {
                int left=cardsRect.left()+(cardsRect.width()-cardPic->width())/2;
                if(cardPic->getselected())left+=10;
                int topBase=cardsRect.top()+(cardsRect.height()-(restCardList.size()+reststrightcardList.size()*5+restTStrightcardList.size()*6-1)*cardSpacing-cardPic->height())/2;
                cardPic->move(left,topBase+i*cardSpacing);
            }
       }
    }
    QVector<Cards>::ConstIterator TSrest=restTStrightcardList.constBegin();
    for(;TSrest!=restTStrightcardList.constEnd();TSrest++)
    {
        QVector<Card> TSstrightCardList=TSrest->ToCardList(Cards::Desc);
        QVector<Card>::ConstIterator TSstright=TSstrightCardList.constBegin();
        for(;TSstright!=TSstrightCardList.constEnd();TSstright++,i++)
        {
            CardPic* cardPic=cardpiclink[*TSstright];
            cardPic->setfrontside(playerContextMap[player].isFrontSide);
            cardPic->show();
            cardPic->raise();
            if(playerContextMap[player].cardsAlign==Horizontal)
            {
                int leftBase=cardsRect.left()+(cardsRect.width()-(restCardList.size()+reststrightcardList.size()*5+restTStrightcardList.size()*6-1)*cardSpacing-cardPic->width())/2;
                int top=cardsRect.top()+(cardsRect.height()-cardPic->height())/2;
                if(cardPic->getselected())top-=10;

               cardPic->move(leftBase+i*cardSpacing,top);
           }
            else
            {
                int left=cardsRect.left()+(cardsRect.width()-cardPic->width())/2;
                if(cardPic->getselected())left+=10;
                int topBase=cardsRect.top()+(cardsRect.height()-(restCardList.size()+reststrightcardList.size()*5+restTStrightcardList.size()*6-1)*cardSpacing-cardPic->height())/2;
                cardPic->move(left,topBase+i*cardSpacing);
            }
       }
    }
    // 显示上一次打出去的牌
    QRect playCardsRect=playerContextMap[player].playHandRect;
    if(!playerContextMap[player].lastCards.IsEmpty())		//不是空牌
    {
        int playSpacing=24;
        QVector<Card> lastCardList=playerContextMap[player].lastCards.ToCardList();
        QVector<Card>::ConstIterator itPlayed=lastCardList.constBegin();
        for(int i=0;itPlayed!=lastCardList.constEnd();itPlayed++,i++)
        {
            CardPic* cardPic=cardpiclink[*itPlayed];
            cardPic->setfrontside(true);
            cardPic->raise();

            if(playerContextMap[player].cardsAlign==Horizontal)
            {
                int leftBase=playCardsRect.left()+(playCardsRect.width()-(lastCardList.size()-1)*playSpacing-cardPic->width())/2;
                int top=playCardsRect.top()+(playCardsRect.height()-cardPic->height())/2;
                cardPic->move(leftBase+i*playSpacing,top);
            }
            else
            {
                int left=playCardsRect.left()+(playCardsRect.width()-cardPic->width())/2;
                int topBase=playCardsRect.top();
                cardPic->move(left,topBase+i*playSpacing);
            }
        }
    }
}

void GamePanel::selectcard(Qt::MouseButton mouseButton)
{
    if(status!=PlayingHandStatus&&status!=TributeCardStatus)return;
        CardPic* cardPic=(CardPic*)sender();

        if(mouseButton==Qt::LeftButton)
        {
            cardPic->setselected(!cardPic->getselected());
            UpdatePlayerCards(user);

            QSet<CardPic*>::Iterator it=selectedCards.find(cardPic);
            if(it==selectedCards.end())		//选中牌
           {
                selectedCards.insert(cardPic);
            }
            else	//取消选中牌
            {
                selectedCards.erase(it);
            }
        }
        else if(mouseButton==Qt::RightButton)	//右击出牌
        {
            handbuttonclick();
        }
}

void GamePanel::startplayhand()
{
    if(endplayer>3)return ;
    status=PlayingHandStatus;
    main_baseCard->hide();
    main_movingCard->hide();
    setnowplayer(nowplayer->GetNextPlayer());
    HideLastCards(nowplayer);

    while(nowplayer->getcardssize()==0){

            if(punchplayer==nowplayer){
                punchplayer=nullptr;
                punchcards.Clear();
                nowplayer=nowplayer->getfriend();
                while(nowplayer->getcardssize()==0){
                    nowplayer=nowplayer->GetNextPlayer();
                }
                break;
            }
            setnowplayer(nowplayer->GetNextPlayer());
            HideLastCards(nowplayer);
    }
    if(nowplayer==user){
        if(user->getcardssize()==0){
            handbutton->hide();
            passbutton->hide();
            adjustbutton->hide();
            backbutton->hide();
        }
        else{
        handbutton->show();
        adjustbutton->show();
        backbutton->show();
        if(punchplayer==user||punchplayer==nullptr){
            passbutton->hide();
        }
        else passbutton->show();
        }
    }
    else{
        passbutton->hide();
        handbutton->hide();
        adjustbutton->hide();
        backbutton->hide();
    }
    nowplayer->StartForPlayHand(punchplayer,punchcards);

}

void GamePanel::startEnding()
{
    updatemarkboard();
    continuebutton->show();
    passbutton->hide();
    adjustbutton->hide();
    backbutton->hide();
    tributebutton->hide();
    handbutton->hide();
    startbutton->hide();
}

void GamePanel::StartTribute()
{
    status=TributeCardStatus;
    if(first->getfriend()==second){
        QVector<Card> cardList=last->getcard().ToCardList(Cards::Desc);
        QVector<Card>::const_iterator it=cardList.constBegin();
        int kingnumber=0;
        for(;it!=cardList.constEnd();it++){
            if(it->cardpoint==Card_BG)kingnumber++;
            else break;
        }
        QVector<Card> cardList2=third->getcard().ToCardList(Cards::Desc);
        QVector<Card>::const_iterator it2=cardList2.constBegin();
        for(;it2!=cardList2.constEnd();it2++){
            if(it2->cardpoint==Card_BG)kingnumber++;
            else break;
        }
        if(kingnumber<2){
            int a=0,b=0;
            while(cardList[a].maincard>0){
                a++;
            }
            last->RemoveCard(cardList[a]);//last的卡牌

            while(cardList2[b].maincard>0){
                b++;
            }
            third->RemoveCard(cardList2[b]);//third的卡牌
            if(cardList[a].cardpoint>cardList2[b].cardpoint){
                first->PickCard(cardList[a]);
                second->PickCard(cardList2[b]);
                nowplayer=last->GetPrevPlayer();
                if(second==user){
                    tributebutton->show();
                    Player* t;
                    t=last;
                    last=third;
                    third=t;
                    first->StartForTribute(third);
                    second->StartForTribute(last);
                }
                else if(first==user){
                    second->StartForTribute(third);
                    tributebutton->show();
                    first->StartForTribute(last);
                }
                else
                {
                    second->StartForTribute(third);
                    first->StartForTribute(last);
                }
            }
            else if(cardList[a].cardpoint<cardList2[b].cardpoint){
                first->PickCard(cardList2[b]);
                second->PickCard(cardList[a]);
                nowplayer=third->GetPrevPlayer();
                if(second==user){
                    tributebutton->show();
                    first->StartForTribute(third);
                    second->StartForTribute(last);
                }
                else if(first==user){
                    tributebutton->show();
                    Player* t;
                    t=last;
                    last=third;
                    third=t;
                    second->StartForTribute(third);
                    first->StartForTribute(last);

                }
                else
                {
                    first->StartForTribute(third);
                    second->StartForTribute(last);
                }

            }
            else{
                last->GetNextPlayer()->PickCard(cardList[a]);
                third->GetNextPlayer()->PickCard(cardList2[b]);
                nowplayer=first;
                if(last->GetNextPlayer()==user){
                    tributebutton->show();
                    Player* t;
                    t=last;
                    last=third;
                    third=t;
                    last->GetNextPlayer()->StartForTribute(third);
                    third->GetNextPlayer()->StartForTribute(last);
                }
                else if(third->GetNextPlayer()==user){
                    tributebutton->show();
                    last->GetNextPlayer()->StartForTribute(third);
                    third->GetNextPlayer()->StartForTribute(last);
                }
                else{
                    last->GetNextPlayer()->StartForTribute(third);
                    third->GetNextPlayer()->StartForTribute(last);
                }


            }

        }
        else{
            nowplayer=first->GetPrevPlayer();//抗贡由上游出牌
            user->SearchStraight();
            left_robot->SearchStraight();
            right_robot->SearchStraight();
            friend_robot->SearchStraight();
            UpdatePlayerCards(user);
            UpdatePlayerCards(left_robot);
            UpdatePlayerCards(right_robot);
            UpdatePlayerCards(friend_robot);
            startplayhand();
        }
    }
    else{
        QVector<Card> cardList=last->getcard().ToCardList(Cards::Desc);
        QVector<Card>::const_iterator it=cardList.constBegin();
        int kingnumber=0;
        for(;it!=cardList.constEnd();it++){
            if(it->cardpoint==Card_BG)kingnumber++;
        }
        if(kingnumber<2){
            it=cardList.constBegin();
            while(it->maincard>0){
                it++;
            }
            Card a;a.deck=it->deck;a.valve=it->valve;a.cardsuit=it->cardsuit;a.maincard=it->maincard;a.cardpoint=it->cardpoint;
            last->RemoveCard(a);
            first->PickCard(a);//贡牌；
            if(first==user){
                tributebutton->show();
            }
            nowplayer=last->GetPrevPlayer();
            first->StartForTribute(last);

        }
        else{
            nowplayer=first->GetPrevPlayer();//抗贡由上游出牌
            user->SearchStraight();
            left_robot->SearchStraight();
            right_robot->SearchStraight();
            friend_robot->SearchStraight();
            UpdatePlayerCards(user);
            UpdatePlayerCards(left_robot);
            UpdatePlayerCards(right_robot);
            UpdatePlayerCards(friend_robot);
            startplayhand();
        }
    }
}
void GamePanel::setnowplayer(Player *player)
{
    nowplayer=player;
}

void GamePanel::passbuttonclick()
{
    if(nowplayer!=user)return;//不是玩家时跳过

    if(punchplayer==user||punchplayer==nullptr)return;//上一张自己出的不出现

    user->HandCard(Cards());//出空卡

    QSet<CardPic*>::ConstIterator it=selectedCards.constBegin();
    for(;it!=selectedCards.constEnd();it++)
    {
        (*it)->setselected(false);
    }
    selectedCards.clear();

    UpdatePlayerCards(user);
    startplayhand();

}

void GamePanel::handbuttonclick()
{
    if (selectedCards.isEmpty()) return;//没牌跳过
        Cards playCards;
        QSet<CardPic*>::const_iterator it=selectedCards.constBegin();
       for(;it!=selectedCards.constEnd();it++)
       {
            playCards.Add((*it)->getlink_card());
        }//提取选中的牌
       Hand hand(playCards);
       CardsType ht=hand.getcardstype();
       if(ht==Type_tart)		//未知牌型，不允许出
        {
            return;
        }
        //管不住其他人的牌
        if(punchplayer!=user&&punchplayer!=nullptr)
        {
            if(!hand.if_beat(Hand(punchcards)))
            {
                return;
            }
        }

        user->HandCard(playCards);
        selectedCards.clear();
        startplayhand();
}

void GamePanel::startbuttonclick()//初始化并打开发牌计时器
{
    status=PickingCardStatus;
    startbutton->hide();
    QMap<Card,CardPic*>::const_iterator it=cardpiclink.constBegin();
    for(;it!=cardpiclink.constEnd();it++)
    {
        it.value()->setselected(false);
        it.value()->setfrontside(true);
        it.value()->hide();
    }

    selectedCards.clear();
    playerContextMap[left_robot].lastCards.Clear();
    playerContextMap[right_robot].lastCards.Clear();
    playerContextMap[friend_robot].lastCards.Clear();
    playerContextMap[user].lastCards.Clear();

    playerContextMap[left_robot].info->hide();
    playerContextMap[right_robot].info->hide();
    playerContextMap[friend_robot].info->hide();
    playerContextMap[user].info->hide();

    playerContextMap[left_robot].isFrontSide=true;
    playerContextMap[right_robot].isFrontSide=true;
    playerContextMap[friend_robot].isFrontSide=true;
    playerContextMap[user].isFrontSide=true;

    left_robot->clearcard();
    right_robot->clearcard();
    left_robot->clearcard();
    friend_robot->clearcard();



    main_baseCard->show();
    handbutton->hide();
    passbutton->hide();
    initall_cards();
    endplayer=1;
    main_winerBoard->setname("",0);

    pickCardTimer->start();

}

void GamePanel::continuebuttonclick()
{
    continuebutton->hide();

    status=PickingCardStatus;
    QMap<Card,CardPic*>::const_iterator it=cardpiclink.constBegin();
    for(;it!=cardpiclink.constEnd();it++)
    {
        it.value()->setselected(false);
        it.value()->setfrontside(true);
        it.value()->hide();
    }

    selectedCards.clear();
    playerContextMap[left_robot].lastCards.Clear();
    playerContextMap[right_robot].lastCards.Clear();
    playerContextMap[friend_robot].lastCards.Clear();
    playerContextMap[user].lastCards.Clear();

    playerContextMap[left_robot].info->hide();
    playerContextMap[right_robot].info->hide();
    playerContextMap[friend_robot].info->hide();
    playerContextMap[user].info->hide();

    playerContextMap[left_robot].isFrontSide=true;
    playerContextMap[right_robot].isFrontSide=true;
    playerContextMap[friend_robot].isFrontSide=true;
    playerContextMap[user].isFrontSide=true;

    left_robot->clearcard();
    right_robot->clearcard();
    user->clearcard();
    friend_robot->clearcard();
    punchplayer=nullptr;
    punchcards.Clear();

    main_baseCard->show();
    handbutton->hide();
    passbutton->hide();
    initall_cards();
    main_winerBoard->setname("",0);
    endplayer=1;
    pickCardTimer->start();

}

void GamePanel::tributebuttonclick()
{
    Cards tributeCards;
    QSet<CardPic*>::const_iterator it=selectedCards.constBegin();
   for(;it!=selectedCards.constEnd();it++)
    {
        tributeCards.Add((*it)->getlink_card());

    }
   Hand tributehand(tributeCards);
   if(tributehand.getcardstype()!=Type_common_Single||tributehand.getbasevalve()>Card_10*10)return ;
   it=selectedCards.constBegin();
   for(;it!=selectedCards.constEnd();it++)
   {
       (*it)->setselected(false);
   }
   selectedCards.clear();
   user->TributeCard(tributeCards);

}

void GamePanel::backbuttonclick()
{
    if (selectedCards.isEmpty())return;
    Cards playCards;
    QSet<CardPic*>::const_iterator it=selectedCards.constBegin();
   for(;it!=selectedCards.constEnd();it++)
    {
        playCards.Add((*it)->getlink_card());
    }
   Hand hand(playCards);
   if(hand.getcardstype()!=Type_common_Straight&&hand.getbombvalve()!=Bomb_StraightFlush&&hand.getcardstype()!=Type_common_TStraight)return ;
   user->outstringcards(playCards);
   UpdatePlayerCards(user);
}

void GamePanel::adjustbuttonclick()
{
    if (selectedCards.isEmpty())return;
    Cards playCards;
    QSet<CardPic*>::const_iterator it=selectedCards.constBegin();
   for(;it!=selectedCards.constEnd();it++)
    {
        playCards.Add((*it)->getlink_card());
    }
   Hand hand(playCards);
   if(hand.getcardstype()!=Type_common_Straight&&hand.getbombvalve()!=Bomb_StraightFlush&&hand.getcardstype()!=Type_common_TStraight)return ;
   user->addstringcards(playCards);
   UpdatePlayerCards(user);
}

void GamePanel::updatemarkboard()
{
    if(first->getfriend()==second){
        if(first==right_robot||first==left_robot){
            upmark(2,3);
        }
        else{
            upmark(1,3);
        }
    }
    else if(first->getfriend()==third){
        if(first==right_robot||first==left_robot){
            upmark(2,2);
        }
        else{
            upmark(1,2);
        }
    }
    else if(first->getfriend()==last){
        if(first==right_robot||first==left_robot){
            upmark(2,1);
        }
        else{
            upmark(1,1);
        }
    }
    if(mark1==12){
        Atime1++;
    }
    if(mark2==12){
        Atime2++;
    }
    if(Atime1>3)mark1=0;
    if(Atime2>3)mark2=0;
    main_markBoard->setmark(mark1,mark2);
}

void GamePanel::upmark(int mark,int a)
{
    if(mark==1){
        if(mark1==12&&a>1){
            //胜利
        }
        else if((mark1+a)>=12){
            mark1=12;
        }
        else{
            mark1=mark1+a;
        }
    }
    else if(mark==2){
        if(mark2==12&&a>1){
            //胜利
        }
        else if((mark2+a)>=12){
            mark2=12;
        }
        else{
            mark2=mark2+a;
        }
    }
    return ;
}

void GamePanel::handending(Player *player)
{
    main_winerBoard->setname(player->GetName(),endplayer);
    switch(endplayer){
    case 1:first=player;break;
    case 2:second=player;break;
    case 3:third=player;break;
    }
    endplayer++;
    if(endplayer==4){
        Player* lastplayer=player->GetNextPlayer();
        while(lastplayer->getcardssize()==0){
            lastplayer=lastplayer->GetNextPlayer();
        }
        main_winerBoard->setname(lastplayer->GetName(),endplayer);
        last=lastplayer;
        startEnding();
    }

}

void GamePanel::StartPickingCard()//发牌动画，并将随机牌发到玩家手中触发pickcard
{
    Player* NowPlayer=nowplayer;
    if(NowMoveStep>=100)	//牌已移动到末端
        {
            Card card=all_cards.TakeRandomCard();
            NowPlayer->PickCard(card);
            ShowPickingCardStep(NowPlayer,NowMoveStep);
            setnowplayer(NowPlayer->GetNextPlayer());
            NowMoveStep=0;
            if(all_cards.Count()==0)	//摸牌结束
            {

                pickCardTimer->stop();
                if(first!=nullptr)StartTribute();
                else{
                    user->SearchStraight();
                    left_robot->SearchStraight();
                    right_robot->SearchStraight();
                    friend_robot->SearchStraight();
                    UpdatePlayerCards(user);
                    UpdatePlayerCards(left_robot);
                    UpdatePlayerCards(right_robot);
                    UpdatePlayerCards(friend_robot);
                    startplayhand();
                   }
            }
    }
    else{
        ShowPickingCardStep(NowPlayer,NowMoveStep);
        NowMoveStep+=14;
}
}
void GamePanel::ShowPickingCardStep(Player* player, int step)//展示发牌阶段（动画）
{
    QRect cardsRect=playerContextMap[player].cardsRect;

    if(player==left_robot)
    {
        int unit=(main_baseCardPos.x()-cardsRect.right())/100;
        main_movingCard->move(main_baseCardPos.x()-step*unit,main_baseCardPos.y());
    }
    else if(player==right_robot)
   {
        int unit=(cardsRect.left()-main_baseCardPos.x())/100;
        main_movingCard->move(main_baseCardPos.x()+step*unit,main_baseCardPos.y());
    }
    else if(player==friend_robot){
        int unit=(main_baseCardPos.y()-cardsRect.bottom())/50;
        main_movingCard->move(main_baseCardPos.x(),main_baseCardPos.y()-step*unit);
    }
    else if(player==user)
    {
        int unit=(cardsRect.top()-main_baseCardPos.y())/100;
        main_movingCard->move(main_baseCardPos.x(),main_baseCardPos.y()+step*unit);
    }

    if(step==0)
    {
        main_movingCard->show();
    }

    if(step>=100)
    {
        main_movingCard->hide();
    }

    update();
}
