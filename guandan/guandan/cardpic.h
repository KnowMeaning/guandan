#ifndef CARDPIC_H
#define CARDPIC_H

#include <QWidget>
#include<qpixmap.h>
#include<player.h>
#include<QMouseEvent>
class CardPic : public QWidget
{
    Q_OBJECT
public:
    explicit CardPic(QWidget* parent = nullptr);
    void setpic(QPixmap front,QPixmap back);
    void setcard(Card card);
    Card getlink_card();
    QPixmap getpic();
    void setfrontside(bool FrontSide);
    bool getfrontside();
    void setselected(bool selected);
    bool getselected();
signals:
    void SendSelected(Qt::MouseButton);
public slots:
protected:
    virtual void paintEvent(QPaintEvent* event);
    virtual void mousePressEvent(QMouseEvent* event);
private:
    QPixmap front_pic;
    QPixmap back_pic;//牌面图片和牌底图片
    Card link_card;//
    bool if_selected;//是否选中
    bool frontSide;//展示面,0为背面，1为正面
};

#endif // CARDPIC_H
