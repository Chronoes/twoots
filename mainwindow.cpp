#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    twoots = new TwitterAPI(this);
    connect(twoots, SIGNAL(timelineReceived(QString)), ui->textEdit, SLOT(setPlainText(QString)));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_timeline_clicked() {
    twoots->get_timeline();
}

void MainWindow::on_auth_clicked() {
    twoots->authenticate();
}
