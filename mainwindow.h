#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "twitterapi.h"
#include "twitterrequests.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

private slots:
    void on_timeline_clicked();

    void on_auth_clicked();

private:
    Ui::MainWindow* ui;
    TwitterAPI* twoots;
    TwitterRequests* requestor;
};

#endif // MAINWINDOW_H
