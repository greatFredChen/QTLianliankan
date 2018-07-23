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
    int r=QMessageBox::warning(this,QString::fromLocal8Bit("��½����"),QString::fromLocal8Bit("ȷ��Ҫ�˳���"),QMessageBox::Yes|QMessageBox::No);
    if(r==QMessageBox::Yes)
        exit(0);
    if(r==QMessageBox::No)
        e->ignore();
}
loginDialog::~loginDialog()
{
    delete ui;
}
void loginDialog::encrypt(char *pwd)//ʹ��ָ�룬��˱���Ҳ��Ķ���
{
    for(int i=0;i<strlen(pwd);i++)
        pwd[i]^=15;
}
void loginDialog::on_pushButton_2_clicked()//�˳�
{
    this->close();
}
bool loginDialog::CheckUser(Loginfo *tmpuser)//�ж��Ƿ���ڸ��û���
{
    char name[100],pwd[100];
    int sscore;
    //ȷ��user��
    //����QFile��ȡ��
    QDir dir;QString path=dir.currentPath()+"/text/userinfo.txt";
    path=path.replace(QString("/"),QString("\\"));
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug()<<"can not open userinfo.txt"<<"\n";
        QMessageBox::warning(this,QString::fromLocal8Bit("��½"),QString::fromLocal8Bit("�޷����ļ�����"),QMessageBox::Ok);
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
void loginDialog::on_pushButton_clicked()//ȷ����ť����ʱ����ע���ˣ�
{
    if(ui->accountline->text().isEmpty()||ui->passwordline->text().isEmpty())
    {
        QMessageBox::warning(this,QString::fromLocal8Bit("��½"),QString::fromLocal8Bit("�˺Ż�����Ϊ�գ�"),QMessageBox::Ok);
        ui->accountline->clear();
        ui->passwordline->clear();
    }
    else{
    QString straccount=ui->accountline->text();
    QString strpassword=ui->passwordline->text();
    strcpy(user->username,straccount.toLocal8Bit().data());//����Usernameһ�����ܹ���ָ�룡������Ϊ��������֮������ָ�룬�ᵼ�����룡����
    strcpy(user->password,strpassword.toLocal8Bit().data());//����������ָ�룡����
    encrypt(user->password);
    //��ʼ��֤�˻�����
    if(!CheckUser(user))
    {
        QMessageBox::warning(this,QString::fromLocal8Bit("��½"),QString::fromLocal8Bit("�˺Ż��������"),QMessageBox::Ok);
        ui->accountline->clear();
        ui->passwordline->clear();
        strcpy(user->username,"Not login");
    }
    else
    {
        ui->accountline->clear();
        ui->passwordline->clear();
        QMessageBox::warning(this,QString::fromLocal8Bit("��½"),QString::fromLocal8Bit("����ɹ���"),QMessageBox::Ok);
        qDebug()<<"logindialog->user:"<<this->user->username<<"\n";
        maindialog->Login=this->user;//���Σ�
        qDebug()<<"maindialog->user:"<<maindialog->Login->username<<"\n";
        this->hide();
        //��½������
        QPropertyAnimation *animation = new QPropertyAnimation(maindialog,"windowOpacity");
        animation->setDuration(1000);
        animation->setStartValue(0);
        animation->setEndValue(1);
        animation->start();
        maindialog->show();
    }
   }
}
void loginDialog::tologin()//���ص�½���棡
{
    maindialog->reject();
    QPropertyAnimation *animation = new QPropertyAnimation(this,"windowOpacity");
    animation->setDuration(1000);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();
    this->show();
}
