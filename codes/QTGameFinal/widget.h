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
//������߽߱���ұ߽߱� �����߽�
const int marginleft=40;
const int marginheight=100;

//����ѡ����ʽ�Լ��ͷ���ʽ��
const QString selectstyle="border:2px solid red;";
const QString releasestyle="";//�ͷ���ʽӦΪ�յ���ʽ����ʾʲô��û������

//�ӳ�ʱ��
const int delaydraw=300;//�ӳ�0.3s������ʾ��
//˼·����ÿһ��ͼƬ�����ó�һ��Сbutton
struct picbutton : public QPushButton
{
    //�̳���� -_-|| ����QPushButton��ֵ��parent������������긳��ʼֵ����
public:
    int picx,picy;
    picbutton(QWidget *parent=Q_NULLPTR):
        QPushButton(parent),picx(-3),picy(-3)
    {}
};//ע���ˣ���������������button��stylesheet��ʱ��ͼƬ����һ��Ҫ�ô�Ӣ��+���֣������������ģ���Ȼ������ʧ�ܣ�������

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void StartGame(GameDiffculty gamedif);//��Ϸ��̨�еĳ�ʼ����Ϸ��

    void block_repaint();//����֮�����������
    void setgametimer();
    Loginfo *Login=new Loginfo;
private:
    Ui::Widget *ui;
    GameModel *gamemodel;//��Ϸ�������ݼ�ģ��
    QTimer *qtimer;//��ʱ��
    picbutton *imagebutton[MAX_col*MAX_row];//ͼƬָ�����飡 ��ÿ������ͼƬ��ÿ��Ԫ�أ�����һ��ָ�룬��������������
    picbutton *beforepic,*afterpic;//�Ⱥ�����������ť����֤��ǰ�������������ͬ��
    bool islinking;//��ʾ����״̬��
    QMediaPlayer *musicplayer;//���ֲ��ţ�
    int tim;//ʱ�䣡
    QMenuBar *mp_bar;
    QMenu *GameMenu;
    QAction *actionEasy;
    QAction *actionNormal;
    QAction *actionHard;
    sounddialog *Sounddlg=new sounddialog;
    //��maindialog��Ϊ������תվ��
    int iconsize;//ͼƬ��С��������Ļ��С���䶯����
    int screenWidth;//��ȡ��Ļ�ֱ����õ�...
    int screenHeight;
//˽�вۺ�����
private slots:
    void on_picbutton_clicked();//ͼƬ����¼�
    void time_withprogressbar();//��ʱ�������������Լ���ʾ��
    void linkeffect();//ʵ������Ч������
    void selectdifficulty();//ѡ���Ѷȣ�

    void on_pushButton_toggled(bool checked);//��ʼ/��ͣ��ť��

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();
    void setplayervolume(int);
    void openmusicplayer();
    void closemusicplayer();
    void setplaying();
    void showscore();

signals:
    void returntomenu();//���ز˵��źţ�
    void exitdirectly();//ֱ���˳��ź�
    void pleaseshowscore();//չʾ��������
    void setsounddlg();
protected:
    virtual void paintEvent(QPaintEvent *event); // ��дpaintevent�¼�!!
    virtual void closeEvent(QCloseEvent *e);
};

#endif // WIDGET_H
