#include "sounddialog.h"
#include "ui_sounddialog.h"

sounddialog::sounddialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sounddialog)
{
    ui->setupUi(this);
    connect(ui->horizontalSlider,SIGNAL(valueChanged(int)),this,SIGNAL(changevolume(int)));
    connect(this,SIGNAL(changevolume(int)),this,SLOT(setlcdnumber(int)));
}
void sounddialog::closeEvent(QCloseEvent *e)
{
    emit setplaying();
}
void sounddialog::setlcdnumber(int i)//显示数字！
{
    ui->lcdNumber->display(i);
    if(!i)
        ui->label_2->setStyleSheet("border-image: url(:/images/nosound.png);");
    else
        ui->label_2->setStyleSheet("border-image: url(:/images/halfsound.png);");
}
sounddialog::~sounddialog()
{
    delete ui;
}

void sounddialog::on_pushButton_toggled(bool checked)
{
    if(!checked)//处于播放状态！
        emit playmusic();
    else
        emit stopmusic();
}
void sounddialog::setpause()
{
    ui->pushButton->setChecked(true);
}
