#ifndef LOGINFO_H
#define LOGINFO_H
#include<iostream>
#include<fstream>
#include<string.h>
#include<QFile>
#include<QTextStream>
#include<QUrl>
#include<QDir>
using namespace std;

class Loginfo
{
public:
    Loginfo();
    Loginfo(char name[],char pwd[],int score);//��txt�ļ���ʼ��!
    Loginfo* operator=(Loginfo *user1);
    bool operator !=(Loginfo *user1);
    void print();//ʤ��֮���ӡ��txt��
    char username[100];
    char password[100];
    int userscore;
};

#endif // LOGINFO_H
