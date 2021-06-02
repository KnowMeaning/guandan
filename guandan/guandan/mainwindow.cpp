#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDialog>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    main_gamePanel=new GamePanel(this);
    setFixedSize(1000,800);
    setWindowTitle(tr("淮安掼蛋"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    main_gamePanel->setGeometry(rect());
}
