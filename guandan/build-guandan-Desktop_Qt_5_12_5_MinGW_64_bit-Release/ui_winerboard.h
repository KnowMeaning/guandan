/********************************************************************************
** Form generated from reading UI file 'winerboard.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINERBOARD_H
#define UI_WINERBOARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WinerBoard
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *label_4;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label;
    QLabel *Firstname;
    QLabel *Secondname;
    QLabel *Thirdname;
    QLabel *Lastname;

    void setupUi(QWidget *WinerBoard)
    {
        if (WinerBoard->objectName().isEmpty())
            WinerBoard->setObjectName(QString::fromUtf8("WinerBoard"));
        WinerBoard->resize(130, 80);
        gridLayoutWidget = new QWidget(WinerBoard);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(0, 0, 131, 83));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(gridLayoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        label_3 = new QLabel(gridLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        label = new QLabel(gridLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        Firstname = new QLabel(gridLayoutWidget);
        Firstname->setObjectName(QString::fromUtf8("Firstname"));

        gridLayout->addWidget(Firstname, 0, 1, 1, 1);

        Secondname = new QLabel(gridLayoutWidget);
        Secondname->setObjectName(QString::fromUtf8("Secondname"));

        gridLayout->addWidget(Secondname, 1, 1, 1, 1);

        Thirdname = new QLabel(gridLayoutWidget);
        Thirdname->setObjectName(QString::fromUtf8("Thirdname"));

        gridLayout->addWidget(Thirdname, 2, 1, 1, 1);

        Lastname = new QLabel(gridLayoutWidget);
        Lastname->setObjectName(QString::fromUtf8("Lastname"));

        gridLayout->addWidget(Lastname, 3, 1, 1, 1);


        retranslateUi(WinerBoard);

        QMetaObject::connectSlotsByName(WinerBoard);
    } // setupUi

    void retranslateUi(QWidget *WinerBoard)
    {
        WinerBoard->setWindowTitle(QApplication::translate("WinerBoard", "Form", nullptr));
        label_4->setText(QApplication::translate("WinerBoard", "\346\234\253\346\270\270\357\274\232", nullptr));
        label_2->setText(QApplication::translate("WinerBoard", "\346\254\241\346\270\270\357\274\232", nullptr));
        label_3->setText(QApplication::translate("WinerBoard", "\346\254\241\346\234\253\357\274\232", nullptr));
        label->setText(QApplication::translate("WinerBoard", "\345\244\264\346\270\270\357\274\232", nullptr));
        Firstname->setText(QString());
        Secondname->setText(QString());
        Thirdname->setText(QString());
        Lastname->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class WinerBoard: public Ui_WinerBoard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINERBOARD_H
