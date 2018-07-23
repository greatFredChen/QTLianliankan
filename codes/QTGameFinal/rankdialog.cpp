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
    int r=QMessageBox::warning(this,QString::fromLocal8Bit("排行榜"),QString::fromLocal8Bit("确定要直接退出吗?"),QMessageBox::Yes|QMessageBox::No);
    if(r==QMessageBox::Yes)
    emit exitdirectly();
    else
        e->ignore();
}
void rankDialog::on_pushButton_clicked()//返回！
{
    //this->reject();
    emit returntomenu();
}

void rankDialog::on_pushButton_2_clicked()//展示！！
{
    if(!hasshow){
    ui->tableView->setShowGrid(true);
    m_model=new QStandardItemModel();
    m_model->setColumnCount(2);//两列！
    m_model->setRowCount(10);//只显示前10名！
    m_model->setHeaderData(0,Qt::Horizontal,QString::fromLocal8Bit("用户名"));//表头！
    m_model->setHeaderData(1,Qt::Horizontal,QString::fromLocal8Bit("分数"));
   //读入txt信息到数组中并达成排序-_-||！
    Readplayerinfo();
    ui->tableView->setModel(m_model);//把模板放上去！！
    ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);//表头信息居中
    ui->tableView->verticalHeader()->setDefaultAlignment(Qt::AlignCenter);//列头居中！
    ui->tableView->resizeColumnsToContents();//根据内容自动调整所有列的列宽！！若括号里有参数，则是调整某一列的列宽！
    ui->tableView->horizontalHeader()->setFixedHeight(45);
    ui->tableView->verticalHeader()->setFixedWidth(50);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//随着窗口大小改变!
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止编辑！
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);//单击选中整行！！
    hasshow=true;//已经展示！
    }
}
void rankDialog::Readplayerinfo()//读取玩家信息进入数组中！
{
    QDir dir;QString path=dir.currentPath()+"/text/userinfo.txt";
    path=path.replace(QString("/"),QString("\\"));
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))//以只读模式打开！！
    {
        qDebug()<<"cannot open userinfo.txt!"<<"\n";
        return;
    }
    //开始读取！
    QTextStream infile(&file);
    infile.setCodec("UTF-8");
    infile.setIntegerBase(10);
    int i=0;
    while(!infile.atEnd())
    {
        infile>>userlist[i].username>>userlist[i].password>>userlist[i].userscore;//读进数组里！
        qDebug()<<"userlist:"<<userlist[i].username<<"\n";
        i++;
    }
    //手写排序！这里采用选择排序！
    for(int j=0;j<i-1;j++)
    {
        int m=j;
        for(int k=j+1;k<i;k++)
            if(sortrule(userlist[k],userlist[m]))
                m=k;
        if(m!=j)
        {
            //交换！
            Loginfo temp=userlist[j];
            userlist[j]=userlist[m];
            userlist[m]=temp;
        }
    }
    //排序完成！
    file.close();
    //开始把模板放上去！
    QStandardItem *item=0;
    for(int i=0;i<10;i++)
    {
        bool flag=false;//判断是否要变色！是否为当前玩家！
        qDebug()<<curplayer->username<<" "<<userlist[i].username<<"\n";
        if(!strcmp(curplayer->username,userlist[i].username)){
            flag=true;
        }
        std::string strname;strname+=userlist[i].username;
        QString sname=QString::fromLocal8Bit(strname.data());
        QString sscore=QString::number(userlist[i].userscore,10);//10进制转换！
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
            m_model->item(i,j)->setTextAlignment(Qt::AlignCenter);//设置文本居中！！
            m_model->item(i,j)->setForeground(QBrush(Qt::white));//设置前景色（文本颜色）为白色！！
            //注意：QBrush上色方法有两个！1.使用纯色的时候可以使用Qt::color。2。如果要使用混合色，则使用QColor方法+RGB调色法来获得混合颜色！！
        }
    }
}
