#ifndef MARKBOARD_H
#define MARKBOARD_H

#include <QWidget>

namespace Ui {
class MarkBoard;
}

class MarkBoard : public QWidget
{
    Q_OBJECT

public:
    explicit MarkBoard(QWidget *parent = nullptr);
    ~MarkBoard();
    void setmark(int users,int robots);
    QString analysemark(int a);
private:
    Ui::MarkBoard *ui;
};

#endif // MARKBOARD_H
