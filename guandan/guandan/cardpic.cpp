#include "cardpic.h"
#include "cardpic.h"
#include<qpainter.h>
#include<QDebug>
CardPic::CardPic(QWidget* parent) : QWidget(parent)
{
    frontSide=0;
    if_selected=0;
}

void CardPic::setpic(QPixmap front, QPixmap back)
{
    front_pic=front;
    back_pic=back;
    resize(back.size());
    update();
}

void CardPic::setcard(Card card)
{
    link_card=card;
}

Card CardPic::getlink_card()
{
    return link_card;
}

QPixmap CardPic::getpic()
{
    return front_pic;
}

void CardPic::setfrontside(bool FrontSide)
{
    if (frontSide!=FrontSide)
    {
        frontSide=FrontSide;
        update();
    }
}

bool CardPic::getfrontside()
{
    return frontSide;
}

void CardPic::setselected(bool selected)
{
    if_selected=selected;
}

bool CardPic::getselected()
{
    return if_selected;
}

void CardPic::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    if(frontSide)
    {
        painter.drawPixmap(rect(),front_pic);
    }
    else
    {
        painter.drawPixmap(rect(),back_pic);
    }
}
void CardPic::mousePressEvent(QMouseEvent* event)
{
    emit SendSelected(event->button());
    QWidget::mousePressEvent(event);
}
