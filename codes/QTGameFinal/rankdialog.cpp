#include "rankdialog.h"
#include "ui_rankdialog.h"
#include<QDebug>
rankDialog::rankDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::rankDialog)
{
    ui->setupUi(this);
    hasshow=false;
}
rankDialog::~rankDialog()
{
    delete ui;
    if(hasshow)
    delete m_model;
    hasshow=false;
}
bool rankDialog::sortrule(Loginfo user1,Loginfo user2)
{
    if(user1.userscore!=user2.userscore)
        return user1.userscore>user2.userscore;
    else
    {
        if(strcmp(user1.username,user2.username)>0)
            return true;
        else
            return false;
    }
}
void rankDialog::closeEvent(QCloseEvent *e)
{
    int r=QMessageBox::warning(this,QString::fromLocal8Bit("���а�"),QString::fromLocal8Bit("ȷ��Ҫֱ���˳���?"),QMessageBox::Yes|QMessageBox::No);
    if(r==QMessageBox::Yes)
    emit exitdirectly();
    else
        e->ignore();
}
void rankDialog::on_pushButton_clicked()//���أ�
{
    //this->reject();
    emit returntomenu();
}

void rankDialog::on_pushButton_2_clicked()//չʾ����
{
    if(!hasshow){
    ui->tableView->setShowGrid(true);
    m_model=new QStandardItemModel();
    m_model->setColumnCount(2);//���У�
    m_model->setRowCount(10);//ֻ��ʾǰ10����
    m_model->setHeaderData(0,Qt::Horizontal,QString::fromLocal8Bit("�û���"));//��ͷ��
    m_model->setHeaderData(1,Qt::Horizontal,QString::fromLocal8Bit("����"));
   //����txt��Ϣ�������в��������-_-||��
    Readplayerinfo();
    ui->tableView->setModel(m_model);//��ģ�����ȥ����
    ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);//��ͷ��Ϣ����
    ui->tableView->verticalHeader()->setDefaultAlignment(Qt::AlignCenter);//��ͷ���У�
    ui->tableView->resizeColumnsToContents();//���������Զ����������е��п������������в��������ǵ���ĳһ�е��п�
    ui->tableView->horizontalHeader()->setFixedHeight(45);
    ui->tableView->verticalHeader()->setFixedWidth(50);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//���Ŵ��ڴ�С�ı�!
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);//��ֹ�༭��
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);//����ѡ�����У���
    hasshow=true;//�Ѿ�չʾ��
    }
}
void rankDialog::Readplayerinfo()//��ȡ�����Ϣ���������У�
{
    QDir dir;QString path=dir.currentPath()+"/text/userinfo.txt";
    path=path.replace(QString("/"),QString("\\"));
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))//��ֻ��ģʽ�򿪣���
    {
        qDebug()<<"cannot open userinfo.txt!"<<"\n";
        return;
    }
    //��ʼ��ȡ��
    QTextStream infile(&file);
    infile.setCodec("UTF-8");
    infile.setIntegerBase(10);
    int i=0;
    while(!infile.atEnd())
    {
        infile>>userlist[i].username>>userlist[i].password>>userlist[i].userscore;//���������
        qDebug()<<"userlist:"<<userlist[i].username<<"\n";
        i++;
    }
    //��д�����������ѡ������
    for(int j=0;j<i-1;j++)
    {
        int m=j;
        for(int k=j+1;k<i;k++)
            if(sortrule(userlist[k],userlist[m]))
                m=k;
        if(m!=j)
        {
            //������
            Loginfo temp=userlist[j];
            userlist[j]=userlist[m];
            userlist[m]=temp;
        }
    }
    //������ɣ�
    file.close();
    //��ʼ��ģ�����ȥ��
    QStandardItem *item=0;
    for(int i=0;i<10;i++)
    {
        bool flag=false;//�ж��Ƿ�Ҫ��ɫ���Ƿ�Ϊ��ǰ��ң�
        qDebug()<<curplayer->username<<" "<<userlist[i].username<<"\n";
        if(!strcmp(curplayer->username,userlist[i].username)){
            flag=true;
        }
        std::string strname;strname+=userlist[i].username;
        QString sname=QString::fromLocal8Bit(strname.data());
        QString sscore=QString::number(userlist[i].userscore,10);//10����ת����
        item=new QStandardItem(sname);

        m_model->setItem(i,0,item);
        item=new QStandardItem(sscore);
        m_model->setItem(i,1,item);
        for(int j=0;j<2;j++)
        {
            if(flag){
                qDebug()<<"quniyade"<<"\n";
                m_model->item(i,j)->setBackground(QBrush(QColor(0,255,255,204)));
            }
            else
                m_model->item(i,j)->setBackground(QBrush(QColor(255,239,213,64)));
            m_model->item(i,j)->setTextAlignment(Qt::AlignCenter);//�����ı����У���
            m_model->item(i,j)->setForeground(QBrush(Qt::white));//����ǰ��ɫ���ı���ɫ��Ϊ��ɫ����
            //ע�⣺QBrush��ɫ������������1.ʹ�ô�ɫ��ʱ�����ʹ��Qt::color��2�����Ҫʹ�û��ɫ����ʹ��QColor����+RGB��ɫ������û����ɫ����
        }
    }
}
