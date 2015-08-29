#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    twoots = new TwitterAPI(this);
    requestor = new TwitterRequests(twoots);
    connect(requestor, SIGNAL(timelineReceived(QString)), ui->textEdit, SLOT(setPlainText(QString)));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_timeline_clicked() {
    requestor->getHomeTimeline();
}

void MainWindow::on_auth_clicked() {
    twoots->authenticate();
}
