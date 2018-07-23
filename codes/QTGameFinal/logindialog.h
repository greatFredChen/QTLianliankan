#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include"maindialog.h"
#include<fstream>
#include<iostream>
#include<QFile>
#include<QTextStream>
#include"loginfo.h"
#include<QDebug>
#include<QMessageBox>
#include<QCloseEvent>
#include<QPropertyAnimation>
using namespace std;

namespace Ui {
class loginDialog;
}

class loginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit loginDialog(QWidget *parent = 0);
    ~loginDialog();
    void encrypt(char *pwd);
    bool CheckUser(Loginfo *tmpuser);
    Loginfo *user=new Loginfo;
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();
    void tologin();
private:
    Ui::loginDialog *ui;
    MainDialog *maindialog=new MainDialog;
protected:
    virtual void closeEvent(QCloseEvent *e);
};

#endif // LOGINDIALOG_H
