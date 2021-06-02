#include "winerboard.h"
#include "ui_winerboard.h"

WinerBoard::WinerBoard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WinerBoard)
{
    ui->setupUi(this);
}

WinerBoard::~WinerBoard()
{
    delete ui;
}

void WinerBoard::setname(QString name, int a)
{
    switch(a){
        case 0:ui->Secondname->setText("");
                ui->Thirdname->setText("");
                ui->Lastname->setText("");break;
        case 1:ui->Firstname->setText(name);break;
        case 2:ui->Secondname->setText(name);break;
        case 3:ui->Thirdname->setText(name);break;
        case 4:ui->Lastname->setText(name);break;
    }
}
