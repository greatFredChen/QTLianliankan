//��ϵ���ļ����ڴ��Ϸ���л��������Լ���������
#pragma once
#ifndef GAMEMODEL_H
#define GAMEMODEL_H
#include<iostream>
#include<vector>
#include<time.h>
#include<QDebug>
//���ȶ�������ĸ������������Լ��ṹ��
//���������������
const int MAX_row=20;
const int MAX_col=20;
//����������ʾͼƬ��
const int MAX_icon=20;
//�����
typedef struct Point
{
    int x,y;//һ��Ҫint��
    Point(){x=-3;y=-3;}
    Point(int px,int py):x(px),y(py)
    {}
    //����=
    Point& operator =(Point &pp)
    {
        x=pp.x;
        y=pp.y;
        return *this;
    }
    bool operator ==(Point &pp)
    {
        return (x==pp.x&&y==pp.y);
    }
};

//��ʾ��Ϸ״̬!
enum GameStatus
{
    Playing,Pause,Win,Lose//��Ӧ��Ϸ�У���Ϸ��ͣ�������ͣ��ť����Ӯ����Ϸ�������Ϸ����Ҫ���ͼƬ�Ƿ�Ϊ�գ������������Լ�ʱ������
};
//ö����Ϸ�Ѷ�
enum GameDiffculty
{
  Easy,Normal,Hard//�򵥡��еȡ������Ѷ�
};
//��Ϸ�Ѷȶ�Ӧ��ͬ�ķ�����!
const int easynum=MAX_row*MAX_col*0.36;//��144����
const int normalnum=MAX_col*MAX_row*0.64;//��256��!
const int hardnum=MAX_row*MAX_col;//��400����





//��������Ϸ�࣡
class GameModel
{
public:
    //��Ա����
    GameModel();//���캯��
    ~GameModel();//��������
    void startGame();//��Ϸ��ʼ��
    void startGame(GameDiffculty gamedif);//���غ�������ͬ�Ѷ��µ���Ϸ
    GameStatus getgamestatus();//��ȡ��Ϸ��ǰ״̬��
    void setgamestatus(GameStatus gamesta);//������Ϸ״̬��
    int canbelinked(Point p1,Point p2);//�ж������㷨������Ϊint��0Ϊ����������1Ϊֱ�ߣ�2Ϊһ���ߣ�3Ϊ�����ߣ��ɵ���������������...
    int canbelinked2(Point p1,Point p2);//���Ǹ��ж������õģ�
    bool canlinkdirectly(Point p1,Point p2);//�ж�ֱ����������
    bool canlinkonecorner(Point p1,Point p2);//һ�������������Ե���ֱ����������
    bool canlinktwocorner(Point p1,Point p2);//���������������Ե���һ���ߺ�ֱ����������
    int *getMap();//���ڻ�ȡmap��
    bool isblocked();//�ж��Ƿ�������֣�
    bool isWin();//�ж��Ƿ�Ӯ����Ϸ��
    void block_rearrange();
    void setgamemap(int cur,int i);
    //���廭�����飬�洢���ߵĵ� vector<struct>
    std::vector<Point>painting;
    int grades;//������   ��������ʹ��txt�洢��Ȼ����ȥ������*10+ʣ��ʱ��*5Ϊ���շ����� ʱ��<=180s!
private:
    //���ݳ�Ա
    int *gameMap;//��Ϸ��ͼ��ʹ��һά�����ʾ������MAX_ROW*x+y��ʾ����(x,y)!!��ע�⣬��gameMap[mr*x+y]=0ʱ������õ�û��ͼƬ��Ϊ1ʱ��Ϊpic1,2ʱΪpic2....
    Point tpone;//һ���յ�ʱ�ĵ�
    Point tp1,tp2;//�����յ�ʱ�ĵ㣬������������P1 P2���ڻ�ͼ��
    GameStatus gamestatus;
    GameDiffculty gamedifficulty;//������Ϸ�ѶȺ�״̬����ö�����ͣ�
    //���Ҫ����д�������ͬһ���û������а�ֻ��ʾһ����߷֣������txt���������˵�Ƚ��鷳��
};

#endif // GAMEMODEL_H
