#include "markboard.h"
#include "ui_markboard.h"
#include<qstring.h>
MarkBoard::MarkBoard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MarkBoard)
{
    ui->setupUi(this);
}

MarkBoard::~MarkBoard()
{
    delete ui;
}

void MarkBoard::setmark(int users,int robots)
{
    QString user;
    QString robot;
    user=analysemark(users);
    robot=analysemark(robots);
    ui->Mark1->setText(user);
    ui->Mark2->setText(robot);
}

QString MarkBoard::analysemark(int a)
{
    switch (a) {
        case 0:return "2";
        case 1:return "3";
        case 2:return "4";
        case 3:return "5";
        case 4:return "6";
        case 5:return "7";
        case 6:return "8";
        case 7:return "9";
        case 8:return "10";
        case 9:return "J";
        case 10:return "Q";
        case 11:return "K";
        case 12:return "A";
    }
    return " ";
}


