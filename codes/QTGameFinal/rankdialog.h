#ifndef RANKDIALOG_H
#define RANKDIALOG_H

#include <QDialog>
#include<QCloseEvent>
#include<QStandardItemModel>
#include<QTableView>
#include<algorithm>
#include"loginfo.h"
#include<QMessageBox>
#include<QFile>
#include<QTextStream>
#include<QVariant>
#include<QDir>
#include<QPropertyAnimation>
namespace Ui {
class rankDialog;
}

class rankDialog : public QDialog
{
    Q_OBJECT

public:
    explicit rankDialog(QWidget *parent = 0);
    ~rankDialog();
    bool sortrule(Loginfo user1,Loginfo user2);
    void Readplayerinfo();
    Loginfo *curplayer=new Loginfo;//显示当前玩家!
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

signals:
    void returntomenu();
    void exitdirectly();
private:
    Ui::rankDialog *ui;
    QStandardItemModel *m_model;
    Loginfo userlist[100];//最多提前分配100个待排序玩家！！
    bool hasshow;
protected:
    virtual void closeEvent(QCloseEvent *e);
};

#endif // RANKDIALOG_H
