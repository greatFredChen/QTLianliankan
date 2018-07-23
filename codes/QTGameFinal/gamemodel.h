//本系列文件用于搭建游戏运行基本环境以及变量！！
#pragma once
#ifndef GAMEMODEL_H
#define GAMEMODEL_H
#include<iostream>
#include<vector>
#include<time.h>
#include<QDebug>
//首先定义所需的各种数据类型以及结构！
//最大行数和列数！
const int MAX_row=20;
const int MAX_col=20;
//定义最大可显示图片！
const int MAX_icon=20;
//定义点
typedef struct Point
{
    int x,y;//一定要int！
    Point(){x=-3;y=-3;}
    Point(int px,int py):x(px),y(py)
    {}
    //重载=
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

//显示游戏状态!
enum GameStatus
{
    Playing,Pause,Win,Lose//对应游戏中，游戏暂停（配合暂停按钮），赢得游戏，输掉游戏（需要配合图片是否为空，利用索引！以及时间条）
};
//枚举游戏难度
enum GameDiffculty
{
  Easy,Normal,Hard//简单、中等、困难难度
};
//游戏难度对应不同的方块数!
const int easynum=MAX_row*MAX_col*0.36;//共144个！
const int normalnum=MAX_col*MAX_row*0.64;//共256个!
const int hardnum=MAX_row*MAX_col;//共400个！





//以下是游戏类！
class GameModel
{
public:
    //成员函数
    GameModel();//构造函数
    ~GameModel();//析构函数
    void startGame();//游戏初始化
    void startGame(GameDiffculty gamedif);//重载函数，不同难度下的游戏
    GameStatus getgamestatus();//获取游戏当前状态！
    void setgamestatus(GameStatus gamesta);//设置游戏状态！
    int canbelinked(Point p1,Point p2);//判定消除算法，返回为int，0为不能消除，1为直线，2为一折线，3为二折线！可调用下列三个函数...
    int canbelinked2(Point p1,Point p2);//这是给判定死局用的！
    bool canlinkdirectly(Point p1,Point p2);//判定直接连接消除
    bool canlinkonecorner(Point p1,Point p2);//一折线消除（可以调用直线消除！）
    bool canlinktwocorner(Point p1,Point p2);//二折线消除（可以调用一折线和直线消除！）
    int *getMap();//用于获取map！
    bool isblocked();//判断是否进入死局！
    bool isWin();//判断是否赢得游戏！
    void block_rearrange();
    void setgamemap(int cur,int i);
    //定义画线数组，存储画线的点 vector<struct>
    std::vector<Point>painting;
    int grades;//分数！   分数结算使用txt存储，然后消去方块数*10+剩余时间*5为最终分数！ 时间<=180s!
private:
    //数据成员
    int *gameMap;//游戏地图，使用一维数组表示，采用MAX_ROW*x+y表示坐标(x,y)!!请注意，当gameMap[mr*x+y]=0时，代表该点没有图片，为1时，为pic1,2时为pic2....
    Point tpone;//一个拐点时的点
    Point tp1,tp2;//两个拐点时的点，以上三个点结合P1 P2用于绘图！
    GameStatus gamestatus;
    GameDiffculty gamedifficulty;//创建游戏难度和状态对象（枚举类型）
    //最后还要考虑写入分数，同一名用户，排行榜只显示一个最高分！！这个txt处理相对来说比较麻烦！
};

#endif // GAMEMODEL_H
