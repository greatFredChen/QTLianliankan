#include "maindialog.h"
#include "ui_maindialog.h"

MainDialog::MainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainDialog)
{
     ui->setupUi(this);
}
void MainDialog::closeEvent(QCloseEvent *e)
{
    int r=QMessageBox::warning(this,QString::fromLocal8Bit("���˵�"),QString::fromLocal8Bit("ȷ��Ҫ�˳���"),QMessageBox::Yes|QMessageBox::No);
    if(r==QMessageBox::Yes)
        exit(0);
    if(r==QMessageBox::No)
        e->ignore();
}
MainDialog::~MainDialog()
{
    delete ui;
}
void MainDialog::Tomenu()//����Ϸ���ڷ��ز˵�����
{
    this->show();
    QPropertyAnimation *animation = new QPropertyAnimation(this,"windowOpacity");
    animation->setDuration(1000);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();
    if(gamewidget)
    delete gamewidget;
}
void MainDialog::on_pushButton_clicked()//��ʼ��Ϸ
{
    gamewidget=new Widget;
    connect(gamewidget,SIGNAL(returntomenu()),this,SLOT(Tomenu()));
    connect(gamewidget,SIGNAL(exitdirectly()),this,SLOT(Toexit()));
    qDebug()<<"maindialog user"<<this->Login->username<<"\n";
    gamewidget->Login=this->Login;
    //������Ϸ���涯����
    QPropertyAnimation *animation = new QPropertyAnimation(gamewidget,"windowOpacity");
    animation->setDuration(1000);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();
    gamewidget->show();
    this->hide();
}
void MainDialog::Toexit()
{
    //ֱ���˳�
    delete gamewidget;
    exit(0);
}
void MainDialog::fromrankingtomenu()
{
    this->show();
    QPropertyAnimation *animation = new QPropertyAnimation(this,"windowOpacity");
    animation->setDuration(1000);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();
    if(Ranking)
    delete Ranking;
}
void MainDialog::on_pushButton_3_clicked()//�˳�
{
    this->close();
    exit(0);
}
void MainDialog::rankingexit()
{
    delete Ranking;
    exit(0);
}
void MainDialog::on_pushButton_2_clicked()//���а�
{
    Ranking=new rankDialog;
    connect(Ranking,SIGNAL(returntomenu()),this,SLOT(fromrankingtomenu()));
    connect(Ranking,SIGNAL(exitdirectly()),this,SLOT(rankingexit()));
    Ranking->curplayer=this->Login;
    qDebug()<<"rankdialog user:"<<Ranking->curplayer->username<<"\n";
    //���а񶯻�
    QPropertyAnimation *animation = new QPropertyAnimation(Ranking,"windowOpacity");
    animation->setDuration(1000);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();
    Ranking->show();
    this->hide();
}

void MainDialog::on_pushButton_4_clicked()//���ص�¼���ڣ�
{
    int r=QMessageBox::warning(this,QString::fromLocal8Bit("���˵�"),QString::fromLocal8Bit("ȷ��Ҫ���ص�½������"),QMessageBox::Yes|QMessageBox::No);
    if(r==QMessageBox::Yes){
       emit returntologin();
    }
}
