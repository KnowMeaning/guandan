#ifndef WINERBOARD_H
#define WINERBOARD_H

#include <QWidget>

namespace Ui {
class WinerBoard;
}

class WinerBoard : public QWidget
{
    Q_OBJECT

public:
    explicit WinerBoard(QWidget *parent = nullptr);
    ~WinerBoard();
    void setname(QString name,int a);
private:
    Ui::WinerBoard *ui;
};

#endif // WINERBOARD_H
