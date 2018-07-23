#include "loginfo.h"
#include<QDebug>
#pragma once
Loginfo::Loginfo()
{
    strcpy(username,"Not login");
    strcpy(password,"Not Input");
    userscore=0;
}
Loginfo::Loginfo(char name[], char pwd[], int score)
{
    strcpy(username,name);
    strcpy(password,pwd);
    userscore=score;
}
Loginfo* Loginfo::operator =(Loginfo *user1)
{
    strcpy(this->username,user1->username);
    strcpy(this->password,user1->password);
    this->userscore=user1->userscore;
    return this;
}
bool Loginfo::operator !=(Loginfo *user1)
{
    return(strcmp(this->username,user1->username));
}
void Loginfo::print()//ʤ��֮��ѷ�����ӡ��txt��
{
    qDebug()<<username<<"\n";
    char name[100],pwd[100];int score;
    QDir dir;QString path=dir.currentPath()+"/text/userinfo.txt";
    path=path.replace(QString("/"),QString("\\"));
    QFile file(path);
    if(!file.open(QIODevice::ReadWrite|QIODevice::Text))//����Ϊ��дģʽ!
    {
        std::cout<<"can not open userinfo.txt in write mode!"<<"\n";
        return;
    }
    QTextStream inoutfile(&file);//���������������
    //�ⲿ�Ƚ��з����Ƚϣ�Ȼ������Ƿ�д�룿
    //��ʼд�룡
    while(!inoutfile.atEnd())
   {
        inoutfile>>name>>pwd;
        if(strcmp(name,username)==0)//�������û���ʼд�룡��
        {
            if(userscore>=10000)
            inoutfile.seek(inoutfile.pos()+1);
            else if(userscore<10000&&userscore>=1000)
                inoutfile.seek(inoutfile.pos()+2);
            else if(userscore<1000)
                inoutfile.seek(inoutfile.pos()+3);
            inoutfile<<userscore<<"\n";
            return;
        }
        else
            inoutfile>>score;
   }
    file.close();
}
