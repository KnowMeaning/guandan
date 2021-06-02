#ifndef GAMEPANEL_H
#define GAMEPANEL_H

#include <QWidget>
#include <QPushButton>
#include<QMap>
#include<qframe.h>
#include<cards.h>
#include<cardpic.h>
#include<player.h>
#include<markboard.h>
#include<robot.h>
#include<user.h>
#include<qlabel.h>
#include<qtimer.h>
#include<hand.h>
#include<winerboard.h>
enum GameStatus{
    PickingCardStatus,//发牌阶段
    TributeCardStatus,//还贡阶段
    PlayingHandStatus,//出牌阶段
    Endingstatus
};
enum PlayerStatus{
    ThinkingForCallLordStatus,
    ThinkingForPlayHandStatus,
    ThinkingForTributeStatus
};

class GamePanel : public QWidget
{
    Q_OBJECT
public:
    explicit GamePanel(QWidget *parent = nullptr);

    void passbuttonclick();
    void handbuttonclick();
    void startbuttonclick();
    void continuebuttonclick();
    void tributebuttonclick();
    void backbuttonclick();
    void adjustbuttonclick();

    void updatemarkboard();
    void upmark(int mark,int a);

    void handending(Player* player);
    void StartPickingCard();
    void startplayhand();
    void startEnding();
    void StartTribute();//第二回合开始供牌环节

    void ShowPickingCardStep(Player *player,int step);

    void OnPlayerPickCards(Player *player,const Cards &cards);
    void OnPlayerHandCards(Player *player,const Cards &cards);
    void OnPlayerTributeCards(Player *player,const Cards &cards,Player *Tribute);

    void HideLastCards(Player* player);
    void UpdatePlayerCards(Player* player);
    void selectcard(Qt::MouseButton mouseButton);

signals:

public slots:
protected:
    enum CardsAlign
    {
        Horizontal,//上下两个
        Vertical//左右两个
    };
    struct PlayerContext
    {
        QRect cardsRect;//手牌区
        QRect playHandRect;//出牌区
        CardsAlign cardsAlign;//横置或竖置
        bool isFrontSide;//是否正面展示
        Cards lastCards;//出牌
        QLabel* info;//文字区（展示“不要”）
    };
    QMap<Player*, PlayerContext> playerContextMap;//让玩家和玩家操纵区link
    void paintEvent(QPaintEvent* event);
    void resizeEvent(QResizeEvent* event);
    void init();
    void initall_cards();
    void initCardPicMap();//初始化所有卡牌的卡面，连接卡图片和卡，放入容器
    void initcontrol();
    void initplayers();
    void initconnect();
    void setnowplayer(Player* player);
private:
    GameStatus status;
    int NowMoveStep;
    QSize main_cardsize;
    QPoint main_baseCardPos;
    CardPic* main_baseCard;//底牌
    CardPic* main_movingCard;//移动牌

    QPixmap main_cardbackpic;

    //每张牌对应一直卡

    QMap<Card,CardPic*> cardpiclink;

    QSet<CardPic*> selectedCards;//出牌前选中的牌

    QPushButton* adjustbutton;
    QPushButton* backbutton;
    QPushButton* tributebutton;
    QPushButton* passbutton;
    QPushButton* handbutton;
    QPushButton* startbutton;
    QPushButton* continuebutton;
    QFrame* userTool;

    MarkBoard* main_markBoard;
    WinerBoard* main_winerBoard;

    robot* left_robot;
    robot* right_robot;
    robot* friend_robot;
    User* user;

    Cards all_cards;
    Player* nowplayer;
    Player* punchplayer;
    Cards punchcards;

    QTimer* pickCardTimer;

    int mark1;
    int Atime1;
    int Atime2;
    int mark2;//1为玩家组分数，2为电脑组分数。

    int endplayer;
    Player* first;
    Player* second;
    Player* third;
    Player* last;
};

#endif // GAMEPANEL_H
