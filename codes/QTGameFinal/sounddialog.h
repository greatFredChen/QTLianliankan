#ifndef SOUNDDIALOG_H
#define SOUNDDIALOG_H

#include <QDialog>
#include<QLCDNumber>
#include<QCloseEvent>
namespace Ui {
class sounddialog;
}

class sounddialog : public QDialog
{
    Q_OBJECT

public:
    explicit sounddialog(QWidget *parent = 0);
    ~sounddialog();
signals:
    void changevolume(int);//���������ı���źţ�
    void playmusic();
    void stopmusic();
    void setplaying();
private slots:
    void setlcdnumber(int);
    void on_pushButton_toggled(bool checked);
    void setPlaymode();
private:
    Ui::sounddialog *ui;
protected:
    virtual void closeEvent(QCloseEvent *e);
};

#endif // SOUNDDIALOG_H
