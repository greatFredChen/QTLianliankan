#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QString>
#include<QPushButton>
#include<QMediaPlayer>
#include<QTimer>
#include<QTime>
#include"gamemodel.h"
#include<QLCDNumber>
#include<QPixmap>
#include<QIcon>
#include<QSize>
#include<QSound>
#include<QProgressBar>
#include<QMessageBox>
#include<QPainter>
#include<QMenuBar>
#include<QAction>
#include"loginfo.h"
#include<QCloseEvent>
#include"sounddialog.h"
#include<QDesktopWidget>
#include<QRect>
#include<QPropertyAnimation>
//设置左边边界和右边边界 顶部边界
const int marginleft=40;
const int marginheight=100;

//设置选中样式以及释放样式！
const QString selectstyle="border:2px solid red;";
const QString releasestyle="";//释放样式应为空的样式表，表示什么都没发生！

//延迟时间
const int delaydraw=300;//延迟0.3s让线显示！
//思路：把每一个图片都设置成一个小button
struct picbutton : public QPushButton
{
    //继承组件 -_-|| 并对QPushButton赋值（parent），对组件坐标赋初始值！！
public:
    int picx,picy;
    picbutton(QWidget *parent=Q_NULLPTR):
        QPushButton(parent),picx(-3),picy(-3)
    {}
};//注意了！！！！后面设置button的stylesheet的时候图片名字一定要用纯英文+数字，不可以有中文，不然会设置失败！！！！

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void StartGame(GameDiffculty gamedif);//游戏舞台中的初始化游戏！

    void block_repaint();//死局之后的重新排序！
    void setgametimer();
    Loginfo *Login=new Loginfo;
private:
    Ui::Widget *ui;
    GameModel *gamemodel;//游戏基本数据及模型
    QTimer *qtimer;//计时器
    picbutton *imagebutton[MAX_col*MAX_row];//图片指针数组！ 即每个基本图片（每个元素）都是一个指针，方便后面操作！！
    picbutton *beforepic,*afterpic;//先后点击的两个按钮！保证和前面数组的类型相同！
    bool islinking;//表示链接状态！
    QMediaPlayer *musicplayer;//音乐播放！
    int tim;//时间！
    QMenuBar *mp_bar;
    QMenu *GameMenu;
    QAction *actionEasy;
    QAction *actionNormal;
    QAction *actionHard;
    sounddialog *Sounddlg=new sounddialog;
    //将maindialog作为数据中转站！
    int iconsize;//图片大小！根据屏幕大小灵活变动！！
    int screenWidth;//获取屏幕分辨率用的...
    int screenHeight;
//私有槽函数！
private slots:
    void on_picbutton_clicked();//图片点击事件
    void time_withprogressbar();//计时器联动进度条以及显示屏
    void linkeffect();//实现链接效果！！
    void selectdifficulty();//选择难度！

    void on_pushButton_toggled(bool checked);//开始/暂停按钮！

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();
    void setplayervolume(int);
    void openmusicplayer();
    void closemusicplayer();
    void setplaying();
    void showscore();

signals:
    void returntomenu();//返回菜单信号！
    void exitdirectly();//直接退出信号
    void pleaseshowscore();//展示分数请求！
    void setsounddlg();
protected:
    virtual void paintEvent(QPaintEvent *event); // 重写paintevent事件!!
    virtual void closeEvent(QCloseEvent *e);
};

#endif // WIDGET_H
