#include "winerboard.h"
#include "ui_winerboard.h"

WinerBoard::WinerBoard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WinerBoard)
{
    ui->setupUi(this);
    QPalette color;
    color.setColor(QPalette::WindowText, Qt::white);
    ui->label->setPalette(color);
    ui->label_2->setPalette(color);
    ui->label_3->setPalette(color);
    ui->label_4->setPalette(color);
    ui->Lastname->setPalette(color);
    ui->Firstname->setPalette(color);
    ui->Thirdname->setPalette(color);
    ui->Secondname->setPalette(color);
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
