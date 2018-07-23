#include "logindialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    loginDialog *logindlg=new loginDialog;
    QPropertyAnimation *animation = new QPropertyAnimation(logindlg,"windowOpacity");
    animation->setDuration(1000);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();
    logindlg->exec();
    return a.exec();
}
