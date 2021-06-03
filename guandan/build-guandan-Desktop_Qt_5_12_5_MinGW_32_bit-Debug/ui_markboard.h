/********************************************************************************
** Form generated from reading UI file 'markboard.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MARKBOARD_H
#define UI_MARKBOARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MarkBoard
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *label_2;
    QLabel *Mark1;
    QLabel *Mark2;

    void setupUi(QWidget *MarkBoard)
    {
        if (MarkBoard->objectName().isEmpty())
            MarkBoard->setObjectName(QString::fromUtf8("MarkBoard"));
        MarkBoard->resize(130, 80);
        gridLayoutWidget = new QWidget(MarkBoard);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(0, 0, 131, 81));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(gridLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        QPalette palette;
        QBrush brush(QColor(255, 255, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        QBrush brush1(QColor(255, 255, 0, 128));
        brush1.setStyle(Qt::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Active, QPalette::PlaceholderText, brush1);
#endif
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush1);
#endif
        QBrush brush2(QColor(120, 120, 120, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush2);
        QBrush brush3(QColor(0, 0, 0, 128));
        brush3.setStyle(Qt::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush3);
#endif
        label->setPalette(palette);
        label->setFrameShadow(QFrame::Plain);
        label->setScaledContents(false);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        Mark1 = new QLabel(gridLayoutWidget);
        Mark1->setObjectName(QString::fromUtf8("Mark1"));

        gridLayout->addWidget(Mark1, 0, 1, 1, 1);

        Mark2 = new QLabel(gridLayoutWidget);
        Mark2->setObjectName(QString::fromUtf8("Mark2"));

        gridLayout->addWidget(Mark2, 2, 1, 1, 1);


        retranslateUi(MarkBoard);

        QMetaObject::connectSlotsByName(MarkBoard);
    } // setupUi

    void retranslateUi(QWidget *MarkBoard)
    {
        MarkBoard->setWindowTitle(QApplication::translate("MarkBoard", "Form", nullptr));
        label->setText(QApplication::translate("MarkBoard", "   \347\216\251\345\256\266\351\230\265\350\220\245\357\274\232", nullptr));
        label_2->setText(QApplication::translate("MarkBoard", "   \347\224\265\350\204\221\351\230\265\350\220\245\357\274\232", nullptr));
        Mark1->setText(QString());
        Mark2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MarkBoard: public Ui_MarkBoard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MARKBOARD_H
