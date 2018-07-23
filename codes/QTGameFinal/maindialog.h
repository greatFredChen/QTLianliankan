#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>
#include"widget.h"
#include"rankdialog.h"
#include<QMessageBox>
#include<QCloseEvent>
#include<loginfo.h>
#include<QPropertyAnimation>
namespace Ui {
class MainDialog;
}

class MainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MainDialog(QWidget *parent = 0);
    ~MainDialog();
    Loginfo *Login=new Loginfo;
private slots:
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();
    void Tomenu();
    void on_pushButton_2_clicked();
    void fromrankingtomenu();
    void Toexit();
    void rankingexit();
    void on_pushButton_4_clicked();
signals:
    void returntologin();
protected:
    virtual void closeEvent(QCloseEvent *e);
private:
    Ui::MainDialog *ui;
    Widget *gamewidget;
    rankDialog *Ranking;
};

#endif // MAINDIALOG_H
