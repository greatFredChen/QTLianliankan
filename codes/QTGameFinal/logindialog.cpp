#include "logindialog.h"
#include "ui_logindialog.h"

loginDialog::loginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginDialog)
{
    ui->setupUi(this);
    connect(maindialog,SIGNAL(returntologin()),this,SLOT(tologin()));
}
void loginDialog::closeEvent(QCloseEvent *e)
{
    int r=QMessageBox::warning(this,QString::fromLocal8Bit("登陆界面"),QString::fromLocal8Bit("确定要退出吗？"),QMessageBox::Yes|QMessageBox::No);
    if(r==QMessageBox::Yes)
        exit(0);
    if(r==QMessageBox::No)
        e->ignore();
}
loginDialog::~loginDialog()
{
    delete ui;
}
void loginDialog::encrypt(char *pwd)//使用指针，因此本体也会改动！
{
    for(int i=0;i<strlen(pwd);i++)
        pwd[i]^=15;
}
void loginDialog::on_pushButton_2_clicked()//退出
{
    this->close();
}
bool loginDialog::CheckUser(Loginfo *tmpuser)//判断是否存在该用户！
{
    char name[100],pwd[100];
    int sscore;
    //确认user！
    //先用QFile读取！
    QDir dir;QString path=dir.currentPath()+"/text/userinfo.txt";
    path=path.replace(QString("/"),QString("\\"));
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug()<<"can not open userinfo.txt"<<"\n";
        QMessageBox::warning(this,QString::fromLocal8Bit("登陆"),QString::fromLocal8Bit("无法打开文件！！"),QMessageBox::Ok);
        return false;
    }
    QTextStream infile(&file);
    while(!infile.atEnd())
    {
        infile>>name>>pwd>>sscore;
        if(strcmp(tmpuser->username,name)==0&&strcmp(tmpuser->password,pwd)==0){
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}
void loginDialog::on_pushButton_clicked()//确定按钮！暂时不搞注册了！
{
    if(ui->accountline->text().isEmpty()||ui->passwordline->text().isEmpty())
    {
        QMessageBox::warning(this,QString::fromLocal8Bit("登陆"),QString::fromLocal8Bit("账号或密码为空！"),QMessageBox::Ok);
        ui->accountline->clear();
        ui->passwordline->clear();
    }
    else{
    QString straccount=ui->accountline->text();
    QString strpassword=ui->passwordline->text();
    strcpy(user->username,straccount.toLocal8Bit().data());//这里Username一定不能够用指针！！！因为函数结束之后销毁指针，会导致乱码！！！
    strcpy(user->password,strpassword.toLocal8Bit().data());//不可以乱用指针！！！
    encrypt(user->password);
    //开始验证账户密码
    if(!CheckUser(user))
    {
        QMessageBox::warning(this,QString::fromLocal8Bit("登陆"),QString::fromLocal8Bit("账号或密码错误！"),QMessageBox::Ok);
        ui->accountline->clear();
        ui->passwordline->clear();
        strcpy(user->username,"Not login");
    }
    else
    {
        ui->accountline->clear();
        ui->passwordline->clear();
        QMessageBox::warning(this,QString::fromLocal8Bit("登陆"),QString::fromLocal8Bit("登入成功！"),QMessageBox::Ok);
        qDebug()<<"logindialog->user:"<<this->user->username<<"\n";
        maindialog->Login=this->user;//传参！
        qDebug()<<"maindialog->user:"<<maindialog->Login->username<<"\n";
        this->hide();
        //登陆动画！
        QPropertyAnimation *animation = new QPropertyAnimation(maindialog,"windowOpacity");
        animation->setDuration(1000);
        animation->setStartValue(0);
        animation->setEndValue(1);
        animation->start();
        maindialog->show();
    }
   }
}
void loginDialog::tologin()//返回登陆界面！
{
    maindialog->reject();
    QPropertyAnimation *animation = new QPropertyAnimation(this,"windowOpacity");
    animation->setDuration(1000);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();
    this->show();
}
